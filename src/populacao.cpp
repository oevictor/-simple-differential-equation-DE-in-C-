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
#include <cstdint>
#include <fstream>

// Gera um valor aleatório entre min e max
double random_value(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

// Construtor que inicializa a população com valores padrão.
populacao::populacao(int tamanho, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) 
    : tamanho(tamanho), minLimites(minLimites), maxLimites(maxLimites), melhorAptidao(std::numeric_limits<double>::max()), geracoesSemMelhora(0) {
    individuos.resize(tamanho, std::vector<double>(minLimites.size()));
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
//tentar inciar isso daqui com sobol_sequence
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
    Mutacao mutacao;
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

// Aplica a seleção aos indivíduos da população com elitismo
void populacao::selecao(const std::vector<double>& x, const std::vector<double>& y, std::vector<std::vector<double>>& melhoresCandidatos) {
    int numElites = 2; // Número de indivíduos elite a serem mantidos
    std::cout << "Aplicando seleção baseada nos dados de aptidão com elitismo." << std::endl;
    Selecao::aplicarSelecao(individuos, x, y, melhorAptidao, geracoesSemMelhora, melhoresCandidatos, numElites);
    std::cout << "Melhor aptidão atual: " << melhorAptidao << std::endl;
}

// Aplica a recombinação aos indivíduos da população
void populacao::recombinacao(double CR, const std::string& estrategia) {
    Mutacao mutacao;
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
bool populacao::criterioParada(int maxGeracoes, double limiarMelhora, int maxGeracoesSemMelhora) {
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
        const auto& bestIndividual = individuos[0]; 
        for (size_t i = 0; i < bestIndividual.size(); ++i) {
            file << bestIndividual[i];
            if (i < bestIndividual.size() - 1) file << ",";
        }
        file << "\n";
        file.close();
        std::cout << "Arquivo " << filename << " salvo." << std::endl;
    } else {
        std::cerr << "Não foi possível salvar o arquivo " << filename << std::endl;
    }
}

// Verifica se a diversidade da população é menor que um limite
bool populacao::criterioDiversidade(double limiarDiversidade) {
    double diversidade = 0.0;
    for (size_t i = 0; i < individuos.size(); ++i) {
        for (size_t j = i + 1; j < individuos.size(); ++j) {
            for (size_t k = 0; k < individuos[i].size(); ++k) {
                diversidade += std::abs(individuos[i][k] - individuos[j][k]);
            }
        }
    }
    diversidade /= (individuos.size() * (individuos.size() - 1) / 2);
    return diversidade < limiarDiversidade;
}

// Ajusta os parâmetros F e CR adaptativamente
void populacao::ajustarParametros(double& F, double& CR) {
    if (geracoesSemMelhora > 10) { 
        F = std::min(1.0, F + 0.1); 
        CR = std::max(0.0, CR - 0.1); 
    } else {
        F = std::max(0.4, F - 0.1); 
        CR = std::min(0.9, CR + 0.1); 
    }
}

// Salva a população inteira em um arquivo
void populacao::savePopulation(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& ind : individuos) {
            for (size_t i = 0; i < ind.size(); ++i) {
                file << ind[i];
                if (i < ind.size() - 1) file << ",";
            }
            file << "\n";
        }
        file.close();
        std::cout << "População salva no arquivo " << filename << std::endl;
    } else {
        std::cerr << "Não foi possível salvar a população no arquivo " << filename << std::endl;
    }
}
