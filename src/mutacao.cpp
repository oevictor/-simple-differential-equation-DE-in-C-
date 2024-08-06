#include "mutacao.hpp"
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

// Defina a função random_value aqui
double random_value(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

/* DE/rand/1: Estratégia rand/1 do DE
vi = xr1 + F * (xr2 - xr3); // Atualização do vetor vi usando um vetor mutante

DE/rand/2: Estratégia rand/2 do DE
vi = xr1 + F * (xr2 - xr3) + F * (xr4 - xr5); // Atualização com dois vetores mutantes

DE/best/1: Estratégia best/1 do DE
vi = xbest + F * (xr1 - xr2); // Atualização usando o melhor vetor da população

DE/best/2: Estratégia best/2 do DE
vi = xbest + F * (xr1 - xr2) + F * (xr3 - xr4); // Atualização usando o melhor vetor e dois vetores mutantes -> tem que implementar essa
*/

// Para ajustar os limites de cada variavel
void aplicarLimites(std::vector<double>& individuo, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    for (size_t i = 0; i < individuo.size(); ++i) {
        if (individuo[i] < minLimites[i]) individuo[i] = minLimites[i];
        if (individuo[i] > maxLimites[i]) individuo[i] = maxLimites[i];
    }
}

void Mutacao::aplicarMutacaoRand1(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < tamanho; ++i) {
        std::uniform_int_distribution<> dis(0, tamanho - 1);
        int a, b, c;
        do { a = dis(gen); } while (a == i);
        do { b = dis(gen); } while (b == i || b == a);
        do { c = dis(gen); } while (c == i || c == a || c == b);

        std::vector<double> mutante(dimensoes);
        for (int j = 0; j < dimensoes; ++j) {
            mutante[j] = individuos[a][j] + F * (individuos[b][j] - individuos[c][j]);
            // Adiciona variação aleatória para aumentar a diversidade
            mutante[j] += 0.1 * (maxLimites[j] - minLimites[j]) * (dis(gen) / static_cast<double>(tamanho) - 0.5);
        }
        aplicarLimites(mutante, minLimites, maxLimites);
        individuos[i] = mutante;
    }
}

void Mutacao::aplicarMutacaoBest1(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites, const std::vector<double>& melhorIndividuo) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < tamanho; ++i) {
        std::uniform_int_distribution<> dis(0, tamanho - 1);
        int b, c;
        do { b = dis(gen); } while (b == i);
        do { c = dis(gen); } while (c == i || c == b);

        std::vector<double> mutante(dimensoes);
        for (int j = 0; j < dimensoes; ++j) {
            mutante[j] = melhorIndividuo[j] + F * (individuos[b][j] - individuos[c][j]);
        }
        aplicarLimites(mutante, minLimites, maxLimites); // Aplica os limites
        individuos[i] = mutante;
    }
}

void Mutacao::aplicarMutacaoRand2(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < tamanho; ++i) {
        std::uniform_int_distribution<> dis(0, tamanho - 1);
        int a, b, c, d, e;
        do { a = dis(gen); } while (a == i);
        do { b = dis(gen); } while (b == i || b == a);
        do { c = dis(gen); } while (c == i || c == a || c == b);
        do { d = dis(gen); } while (d == i || d == a || d == b || d == c);
        do { e = dis(gen); } while (e == i || e == a || e == b || e == c || e == d);

        std::vector<double> mutante(dimensoes);
        for (int j = 0; j < dimensoes; ++j) {
            mutante[j] = individuos[a][j] + F * (individuos[b][j] - individuos[c][j]) + F * (individuos[d][j] - individuos[e][j]);
        }
        aplicarLimites(mutante, minLimites, maxLimites); // Aplica os limites
        individuos[i] = mutante;
    }
}

// Recombinação (crossover)
void Mutacao::aplicarRecombinacaoBinomial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < tamanho; ++i) {
        std::vector<double> filho(dimensoes);
        std::uniform_real_distribution<> disReal(0.0, 1.0);
        int jrand = std::uniform_int_distribution<>(0, dimensoes - 1)(gen);
        for (int j = 0; j < dimensoes; ++j) {
            if (disReal(gen) <= CR || j == jrand) {
                filho[j] = individuos[i][j];
            } else {
                filho[j] = random_value(minLimites[j], maxLimites[j]); // Introduzir aleatoriedade
            }
        }
        aplicarLimites(filho, minLimites, maxLimites);
        individuos[i] = filho;
    }
}

void Mutacao::aplicarRecombinacaoExponencial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < tamanho; ++i) {
        std::vector<double> filho(dimensoes);
        std::uniform_real_distribution<> disReal(0.0, 1.0);
        int jrand = std::uniform_int_distribution<>(0, dimensoes - 1)(gen);
        int L = 0;
        for (int j = 0; j < dimensoes; ++j) {
            if (disReal(gen) <= CR || j == jrand) {
                filho[j] = individuos[i][j];
                L++;
            } else {
                break;
            }
        }
        for (int j = L; j < dimensoes; ++j) {
            filho[j] = individuos[i][j]; // Manter o valor original
        }
        aplicarLimites(filho, minLimites, maxLimites); // Aplica os limites
        individuos[i] = filho;
    }
}
