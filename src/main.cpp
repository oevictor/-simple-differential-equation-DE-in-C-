#include "populacao.hpp"
#include <iostream>
#include <vector>
#include <chrono> // para medir o tempo de execução
#include <cmath>
#include <random>
#include <utility>

// Gera dados de teste
std::pair<std::vector<double>, std::vector<double>> generateTestData(int size, double a, double b, double c) {
    std::vector<double> x(size);
    std::vector<double> y(size);
    for (int i = 0; i < size; ++i) {
        x[i] = i;
        y[i] = a + b * x[i] + c * x[i] * x[i]; // Polinômio: y = a + bx + cx^2
    }
    return std::make_pair(x, y);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    int tamanho = 50; 
    std::vector<double> minLimites = {-10, -10, -10}; // Limites mínimos para cada variável
    std::vector<double> maxLimites = {10, 10, 10}; // Limites máximos para cada variável
    double F = 0.75;
    double CR = 0.9;
    int maxGeracoes = 10000; // Mais gerações para melhor convergência
    double limiarMelhora = 1e-6;
    int maxGeracoesSemMelhora = 1000;
    double limiarDiversidade = 0.7; // Limite para critério de diversidade

    int dataSize = 100;
    auto [x, y] = generateTestData(dataSize, -8, -2.0, 3.0);

    populacao pop(tamanho, minLimites, maxLimites);
    pop.iniciarPopulacao();

    std::vector<std::vector<double>> melhoresCandidatos;
    double melhorAptidao = std::numeric_limits<double>::max();
    int geracoesSemMelhora = 0;

    for (int g = 0; g < maxGeracoes; ++g) {
        pop.mutacao(F, "rand/1");
        pop.recombinacao(CR, "binomial");

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

        // Salva a população da geração atual
        std::string filename = "populacao_geracao_" + std::to_string(g + 1) + ".txt";
        pop.savePopulation(filename);

        std::cout << "Geração " << g + 1 << " completada." << std::endl;
    }

    std::cout << "População Final:" << std::endl;
    pop.mostrarPopulacao();

    auto finalPopulation = pop.getIndividuos();
    pop.saveBestIndividual("best_individual.txt");

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = stop - start;
    std::cout << "Tempo de execução: " << diff.count() << " s" << std::endl;

    return 0;
}
