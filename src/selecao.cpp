#include "selecao.hpp"
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

// Está selecionando muito mal os valores
// Calcula a aptidão de um indivíduo comparando os valores estimados de y com os valores reais de y
// Isso tem que ser uma função erro e deve ser minimizada e dada por um arquivo em python 

double Selecao::calcularAptidao(const std::vector<double>& individuo, const std::vector<double>& x, const std::vector<double>& y) {
    double erro = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double estimativa = 0.0;
        for (size_t j = 0; j < individuo.size(); ++j) {
            estimativa += individuo[j] * pow(x[i], j);
        }
        erro += pow(estimativa - y[i], 2);
    }
    return erro / x.size(); // Retorna o erro médio quadrático total dividido pelo número de elementos em x
}

// Função para realizar a seleção por torneio
std::vector<double> Selecao::tournamentSelection(const std::vector<std::pair<double, std::vector<double>>>& aptidoes, int tournamentSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, aptidoes.size() - 1);

    std::vector<std::pair<double, std::vector<double>>> tournament;
    for (int i = 0; i < tournamentSize; ++i) {
        int randomIndex = dis(gen);
        tournament.push_back(aptidoes[randomIndex]);
    }

    std::sort(tournament.begin(), tournament.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    return tournament[0].second; // Retorna o indivíduo com a melhor aptidão no torneio
}

// Aplica o processo de seleção à população
void Selecao::aplicarSelecao(std::vector<std::vector<double>>& individuos, const std::vector<double>& x, const std::vector<double>& y, double& melhorAptidao, int& geracoesSemMelhora, std::vector<std::vector<double>>& melhoresCandidatos) {
    std::vector<std::pair<double, std::vector<double>>> aptidoes;
    for (const auto& individuo : individuos) {
        double aptidao = calcularAptidao(individuo, x, y);
        aptidoes.push_back({aptidao, individuo});
    }

    std::vector<std::vector<double>> novaPopulacao;
    int tournamentSize = 3; // Tamanho do torneio
    for (size_t i = 0; i < individuos.size(); ++i) {
        novaPopulacao.push_back(tournamentSelection(aptidoes, tournamentSize));
    }

    individuos = novaPopulacao;

    double novaMelhorAptidao = aptidoes[0].first;
    if (novaMelhorAptidao < melhorAptidao) {
        melhorAptidao = novaMelhorAptidao;
        geracoesSemMelhora = 0;
    } else {
        geracoesSemMelhora++;
    }

    // Adiciona o melhor indivíduo da geração atual aos melhores candidatos
    melhoresCandidatos.push_back(aptidoes[0].second);
}
// Implementation of Sobol sequence generator using direction numbers
// Reference: https://en.wikipedia.org/wiki/Sobol_sequence
//Explicar dps o que é isso

std::vector<std::vector<double>> sobol_sequence(int N, int D) {
    std::vector<std::vector<double>> sequence(N, std::vector<double>(D));
    std::vector<std::vector<uint32_t>> directions(D, std::vector<uint32_t>(32, 0));
    
    // Initialize direction numbers for each dimension
    for (int d = 0; d < D; ++d) {
        for (int i = 0; i < 32; ++i) {
            directions[d][i] = 1 << (31 - i);
        }
    }

    // Generate Sobol sequence points
    std::vector<uint32_t> x(D, 0);
    for (int i = 0; i < N; ++i) {
        int j = 0;
        for (int k = i; (k & 1) == 1; k >>= 1) {
            ++j;
        }
        for (int d = 0; d < D; ++d) {
            x[d] ^= directions[d][j];
            sequence[i][d] = static_cast<double>(x[d]) / (1ULL << 32);
        }
    }

    return sequence;
}
