#include "selecao.hpp"
#include <cmath>
#include <algorithm>
#include <vector>

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
    return erro / x.size(); // Retorna o erro médio quadrático
}

// Aplica o processo de seleção à população
void Selecao::aplicarSelecao(std::vector<std::vector<double>>& individuos, const std::vector<double>& x, const std::vector<double>& y, double& melhorAptidao, int& geracoesSemMelhora) {
    std::vector<std::pair<double, std::vector<double>>> aptidoes;
    for (const auto& individuo : individuos) {
        double aptidao = calcularAptidao(individuo, x, y);
        aptidoes.push_back({aptidao, individuo});
    }

    std::sort(aptidoes.begin(), aptidoes.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    for (size_t i = 0; i < individuos.size(); ++i) {
        individuos[i] = aptidoes[i].second;
    }

    double novaMelhorAptidao = aptidoes[0].first;
    if (novaMelhorAptidao < melhorAptidao) {
        melhorAptidao = novaMelhorAptidao;
        geracoesSemMelhora = 0;
    } else {
        geracoesSemMelhora++;
    }
}
