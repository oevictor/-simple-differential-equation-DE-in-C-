#include "populacao.hpp"
#include <iostream>
#include <vector>
#include <chrono> // para medir o tempo de execução
#include <cmath>
#include <random>
#include <utility>
#include "resultado.hpp"
#include "selecao.hpp" // Include the header file for selection

// Generate test data
std::pair<std::vector<double>, std::vector<double>> generateTestData(int size, double a, double b, double c) {
    std::vector<double> x(size);
    std::vector<double> y(size);
    for (int i = 0; i < size; ++i) {
        x[i] = i;
        y[i] = a + b * x[i] + c * x[i] * x[i]; // Polynomial: y = a + bx + cx^2
    }
    return std::make_pair(x, y);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    int tamanho = 1000; 
    std::vector<double> minLimites = {0, 0, 0}; // Limites mínimos para cada variável
    std::vector<double> maxLimites = {5, 5, 5}; // Limites máximos para cada variável
    double F = 0.6;
    double CR = 0.8;
    int maxGeracoes = 100; // Mais gerações para melhor convergência
    double limiarMelhora = 1e-6;
    int maxGeracoesSemMelhora = 1000;
    double limiarDiversidade = 0.01; // Limite para critério de diversidade

    int dataSize = 100;
    auto [x, y] = generateTestData(dataSize, 1.0, 2.0, 3.0);

    populacao pop(tamanho, minLimites, maxLimites);
    pop.iniciarPopulacao();

    std::vector<std::vector<double>> melhoresCandidatos;
    double melhorAptidao = std::numeric_limits<double>::max();
    int geracoesSemMelhora = 0;

    for (int g = 0; g < maxGeracoes; ++g) {
        pop.mutacao(F, "rand/1");
        pop.recombinacao(CR, "binomial");

        #pragma omp parallel for
        for (size_t i = 0; i < pop.getIndividuos().size(); ++i) {
            pop.selecao(x, y, melhoresCandidatos);
        }

        // Verifica se os critérios de parada foram alcançados
        if (pop.criterioParada(maxGeracoes, limiarMelhora, maxGeracoesSemMelhora) ||
            pop.criterioDiversidade(limiarDiversidade)) {
            std::cout << "Convergência atingida na geração " << g + 1 << std::endl;
            break;
        }

        // Ajusta os parâmetros F e CR adaptativamente
        pop.ajustarParametros(F, CR);

        std::cout << "Geração " << g + 1 << ":" << std::endl;
        pop.mostrarPopulacao();
    }

    std::cout << "População Final:" << std::endl;
    pop.mostrarPopulacao();

    auto finalPopulation = pop.getIndividuos();
    resultado res;
    res.saveToCSV(finalPopulation, "populacao_final.txt");

    pop.saveBestIndividual("best_individual.txt");
    res.saveToCSV(melhoresCandidatos, "melhores_candidatos.txt");

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = stop - start;
    std::cout << "Tempo de execução: " << diff.count() << " s" << std::endl;

    return 0;
}