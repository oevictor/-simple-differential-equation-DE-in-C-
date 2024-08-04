#include "populacao.hpp"
#include <iostream>
#include <vector>
#include <chrono> // para medir o tempo de execução
#include <fstream> // para salvar o arquivo CSV
#include <cmath>
#include <random>
#include <utility>

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

void saveToCSV(const std::vector<std::vector<double>>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) file << ",";
            }
            file << "\n";
        }
        file.close();
        std::cout << "Arquivo " << filename << " salvo com sucesso." << std::endl;
    } else {
        std::cerr << "Não foi possível salvar o arquivo " << filename << std::endl;
    }
}

int main() {
    //colocar a dimensão aqui 
    auto start = std::chrono::high_resolution_clock::now();
    int tamanho = 50; // Population size
    std::vector<double> minLimites = {0, 0, 0}; // Limites mínimos para cada variável
    std::vector<double> maxLimites = {5, 5, 5}; // Limites máximos para cada variável
    double F = 0.75;
    double CR = 0.9;
    int maxGeracoes = 1000;
    double limiarMelhora = 1e-6;
    int maxGeracoesSemMelhora = 10;

    // Generate test data
    int dataSize = 100;
    auto [x, y] = generateTestData(dataSize, 1.0, 2.0, 3.0); // a=1, b=2, c=3

    populacao pop(tamanho, minLimites, maxLimites);
    pop.iniciarPopulacao();

    for (int g = 0; g < maxGeracoes; ++g) {
        pop.mutacao(F, "rand/1");
        pop.recombinacao(CR, "binomial");
        pop.selecao(x, y);

        if (pop.criterioParada(maxGeracoes, limiarMelhora, maxGeracoesSemMelhora)) {
            std::cout << "Convergência atingida na geração " << g + 1 << std::endl;
            break;
        }

        std::cout << "Geração " << g + 1 << ":" << std::endl;
        pop.mostrarPopulacao();
    }

    std::cout << "População Final:" << std::endl;
    pop.mostrarPopulacao();

    // Save the entire population to a file
    auto finalPopulation = pop.getIndividuos();
    saveToCSV(finalPopulation, "populacao_final.txt");

    // Save the best individual to a separate file
    pop.saveBestIndividual("best_individual.txt");

    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = stop - start;
    std::cout << "Tempo de execução: " << diff.count() << " s" << std::endl;

    return 0;
}
