#include "selecao.hpp"
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include <cstdint>

// Sobol sequence generator using direction numbers
const uint32_t directions[32] = {
    1, 3, 5, 15, 17, 51, 85, 255, 257, 771, 1285, 3855, 4369, 13107,
    21845, 65535, 65537, 196611, 327685, 983055, 1114129, 3342387,
    5570645, 16777215, 16777217, 50331651, 83886085, 251658255,
    285212673, 855638017, 1427733389, 4294967295
};

uint32_t sobol(uint32_t i) {
    uint32_t x = 0;
    for (int j = 0; i; i >>= 1, j++) {
        if (i & 1) x ^= directions[j];
    }
    return x;
}

std::vector<std::vector<double>> Selecao::sobol_sequence(int N, int D) {
    std::vector<std::vector<double>> sequence(N, std::vector<double>(D));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            sequence[i][j] = static_cast<double>(sobol(i ^ (i >> 1))) / (1ULL << 32);
        }
    }
    return sequence;
}

// Calcula a aptidão de um indivíduo comparando os valores estimados de y com os valores reais de y
double Selecao::calcularAptidao(const std::vector<double>& individuo, const std::vector<double>& x, const std::vector<double>& y) {
    double erro = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double estimativa = 0.0;
        for (size_t j = 0; j < individuo.size(); ++j) {
            estimativa += individuo[j] * pow(x[i], j);
        }
        erro += pow(estimativa - y[i], 2);
    }
    return erro / x.size();
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

    return tournament[0].second;
}

// Os melhores indivíduos são selecionados com base em suas aptidões a elite
std::vector<std::vector<double>> Selecao::getBestIndividuals(const std::vector<std::vector<double>>& individuos, const std::vector<double>& x, const std::vector<double>& y, int numElites) {
    std::vector<std::pair<double, std::vector<double>>> aptidoes;
    for (const auto& individuo : individuos) {
        double aptidao = calcularAptidao(individuo, x, y);
        aptidoes.push_back({aptidao, individuo});
    }

    std::sort(aptidoes.begin(), aptidoes.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    std::vector<std::vector<double>> elites;
    for (int i = 0; i < numElites; ++i) {
        elites.push_back(aptidoes[i].second);
    }

    return elites;
}

// Aplica o processo de seleção à população com elitismo
void Selecao::aplicarSelecao(std::vector<std::vector<double>>& individuos, const std::vector<double>& x, const std::vector<double>& y, 
double& melhorAptidao, int& geracoesSemMelhora, std::vector<std::vector<double>>& melhoresCandidatos, int numElites) {
    // Encontra os melhores indivíduos (elites)
    std::vector<std::vector<double>> elites = getBestIndividuals(individuos, x, y, numElites);

    // Calcula as aptidões de todos os indivíduos
    std::vector<std::pair<double, std::vector<double>>> aptidoes;
    for (const auto& individuo : individuos) {
        double aptidao = calcularAptidao(individuo, x, y);
        aptidoes.push_back({aptidao, individuo});
    }

    // Cria a nova população usando seleção por torneio
    std::vector<std::vector<double>> novaPopulacao;
    int tournamentSize = 3;
    for (size_t i = 0; i < individuos.size() - numElites; ++i) { // Reserva espaço para elites
        novaPopulacao.push_back(tournamentSelection(aptidoes, tournamentSize));
    }

    // Adiciona os elites à nova população
    novaPopulacao.insert(novaPopulacao.end(), elites.begin(), elites.end());

    // Atualiza a população
    individuos = novaPopulacao;

    // Atualiza a melhor aptidão
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

