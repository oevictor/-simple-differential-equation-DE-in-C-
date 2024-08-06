#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "populacao.hpp"
#include "mutacao.hpp"
#include "selecao.hpp"
#include <vector>
#include <cmath>
#include <limits>

// Função auxiliar para gerar dados de teste
std::pair<std::vector<double>, std::vector<double>> generateTestData(int size, double a, double b, double c) {
    std::vector<double> x(size);
    std::vector<double> y(size);
    for (int i = 0; i < size; ++i) {
        x[i] = i;
        y[i] = a + b * x[i] + c * x[i] * x[i]; // Polinômio: y = a + bx + cx^2
    }
    return std::make_pair(x, y);
}

// Testes para a classe populacao
TEST_CASE("Testando inicialização da população") {
    int tamanho = 10;
    std::vector<double> minLimites = {-10, -10, -10};
    std::vector<double> maxLimites = {10, 10, 10};
    populacao pop(tamanho, minLimites, maxLimites);
    pop.iniciarPopulacao();
    
    // Verificar se a população foi inicializada corretamente
    auto individuos = pop.getIndividuos();
    CHECK(individuos.size() == tamanho);
    for (const auto& individuo : individuos) {
        CHECK(individuo.size() == minLimites.size());
        for (size_t j = 0; j < individuo.size(); ++j) {
            CHECK(individuo[j] >= minLimites[j]);
            CHECK(individuo[j] <= maxLimites[j]);
        }
    }
}

// Testes para a classe Mutacao
TEST_CASE("Testando a aplicação da mutação rand/1") {
    int tamanho = 10;
    std::vector<double> minLimites = {-10, -10, -10};
    std::vector<double> maxLimites = {10, 10, 10};
    populacao pop(tamanho, minLimites, maxLimites);
    pop.iniciarPopulacao();

    Mutacao mutacao;
    double F = 0.5;
    auto& individuos = pop.getIndividuos(); // Armazena a referência em uma variável
    mutacao.aplicarMutacaoRand1(individuos, F, minLimites, maxLimites);

    // Verificar se a mutação foi aplicada corretamente
    CHECK(individuos.size() == tamanho);
    for (const auto& individuo : individuos) {
        CHECK(individuo.size() == minLimites.size());
        for (size_t j = 0; j < individuo.size(); ++j) {
            CHECK(individuo[j] >= minLimites[j]);
            CHECK(individuo[j] <= maxLimites[j]);
        }
    }
}

// // Testes para a classe Selecao
// TEST_CASE("Testando a aplicação da seleção com elitismo") {
//     int tamanho = 10;
//     std::vector<double> minLimites = {-10, -10, -10};
//     std::vector<double> maxLimites = {10, 10, 10};
//     populacao pop(tamanho, minLimites, maxLimites);
//     pop.iniciarPopulacao();

//     auto [x, y] = generateTestData(10, 1.0, 2.0, 3.0);

//     std::vector<std::vector<double>> melhoresCandidatos;
//     auto& individuos = pop.getIndividuos(); // Armazena a referência em uma variável
//     Selecao::aplicarSelecao(individuos, x, y, pop.getMelhorAptidao(), pop.getGeracoesSemMelhora(), melhoresCandidatos, 2);

//     // Verificar se a seleção foi aplicada corretamente
//     CHECK(individuos.size() == tamanho);
//     for (const auto& individuo : individuos) {
//         CHECK(individuo.size() == minLimites.size());
//     }
// }
