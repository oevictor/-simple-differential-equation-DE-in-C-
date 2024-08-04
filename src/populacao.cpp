#include "populacao.hpp"
#include "mutacao.hpp"
#include "selecao.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <string>
#include <limits>
#include <random>
#include <utility>

// Gera um valor aleatório entre min e max
double random_value(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

// Construtor que inicializa a população com valores padrão.
/*O tamanho dos invividos, tambem deve ser uma escolha da função em python*/
populacao::populacao(int tamanho, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) 
    : tamanho(tamanho), minLimites(minLimites), maxLimites(maxLimites), melhorAptidao(std::numeric_limits<double>::max()), geracoesSemMelhora(0) {
    individuos.resize(tamanho, std::vector<double>(minLimites.size())); /*resize para aumentar o tamanho do conteiner */
}

// Retorna o tamanho da população
int populacao::getTamanho() {
    return tamanho;
}

// Define o tamanho da população
void populacao::setTamanho(int tamanho) {
    this->tamanho = tamanho;
    individuos.resize(tamanho);
}

// Inicializa a população com valores aleatórios
void populacao::iniciarPopulacao() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < tamanho; ++i) {
        for (std::vector<double>::size_type j = 0; j < individuos[i].size(); ++j) {
            individuos[i][j] = random_value(minLimites[j], maxLimites[j]);
        }
    }
    std::cout << "População inicializada com " << tamanho << " indivíduos." << std::endl;
}

// Mostra os indivíduos da população
void populacao::mostrarPopulacao() {
    for (int i = 0; i < tamanho; ++i) {
        std::cout << "Indivíduo " << i + 1 << ": ";
        for (std::vector<double>::size_type j = 0; j < individuos[i].size(); ++j) {
            std::cout << individuos[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Aplica a mutação aos indivíduos da população
void populacao::mutacao(double F, const std::string& estrategia) {
    Mutacao mutacao; // Create an instance of the Mutacao class
    std::cout << "Aplicando mutação com estratégia " << estrategia << " e fator F = " << F << std::endl;
    if (estrategia == "rand/1") {
        mutacao.aplicarMutacaoRand1(individuos, F, minLimites, maxLimites);
    } else if (estrategia == "best/1") {
        mutacao.aplicarMutacaoBest1(individuos, F, minLimites, maxLimites, melhorAptidao);
    } else if (estrategia == "rand/2") {
        mutacao.aplicarMutacaoRand2(individuos, F, minLimites, maxLimites);
    } else {
        std::cerr << "Estratégia de mutação desconhecida: " << estrategia << std::endl;
    }
}

// Aplica a seleção aos indivíduos da população
void populacao::selecao(const std::vector<double>& x, const std::vector<double>& y) {
    std::cout << "Aplicando seleção baseada nos dados de aptidão." << std::endl;
    Selecao selecao; // Create an instance of the Selecao class
    selecao.aplicarSelecao(individuos, x, y, melhorAptidao, geracoesSemMelhora);
    std::cout << "Melhor aptidão atual: " << melhorAptidao << std::endl;
}

// Aplica a recombinação aos indivíduos da população
void populacao::recombinacao(double CR, const std::string& estrategia) {
    Mutacao mutacao; // Create an instance of the Mutacao class
    std::cout << "Aplicando recombinação com estratégia " << estrategia << " e taxa CR = " << CR << std::endl;
    if (estrategia == "binomial") {
        mutacao.aplicarRecombinacaoBinomial(individuos, CR, minLimites, maxLimites);
    } else if (estrategia == "exponencial") {
        mutacao.aplicarRecombinacaoExponencial(individuos, CR, minLimites, maxLimites);
    } else {
        std::cerr << "Estratégia de recombinação desconhecida: " << estrategia << std::endl;
    }
}

// Verifica se o critério de parada foi alcançado
bool populacao::criterioParada(int /*maxGeracoes*/, double /*limiarMelhora*/, int maxGeracoesSemMelhora) {
    std::cout << "Verificando critério de parada." << std::endl;
    return (geracoesSemMelhora >= maxGeracoesSemMelhora);
}

// Retorna os indivíduos da população
std::vector<std::vector<double>> populacao::getIndividuos() {
    return individuos;
}

// Salva o melhor indivíduo em um arquivo
void populacao::saveBestIndividual(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        const auto& bestIndividual = individuos[0]; // Assuming the first individual is the best
        for (size_t i = 0; i < bestIndividual.size(); ++i) {
            file << bestIndividual[i];
            if (i < bestIndividual.size() - 1) file << ",";
        }
        file << "\n";
        file.close();
        std::cout << "arquivo " << filename << " salvo." << std::endl;
    } else {
        std::cerr << "Deu ruim " << filename << std::endl;
    }
}
