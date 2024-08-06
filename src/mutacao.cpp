#include "mutacao.hpp"
#include <cstdlib>
#include <ctime>


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

    srand(static_cast<unsigned int>(time(0))); 

    for (int i = 0; i < tamanho; ++i) {
        int a, b, c;
        do { a = rand() % tamanho; } while (a == i);
        do { b = rand() % tamanho; } while (b == i || b == a);
        do { c = rand() % tamanho; } while (c == i || c == a || c == b);

        std::vector<double> mutante(dimensoes);
        for (int j = 0; j < dimensoes; ++j) {
            mutante[j] = individuos[a][j] + F * (individuos[b][j] - individuos[c][j]);
        }
        aplicarLimites(mutante, minLimites, maxLimites); /* Aplica os limites */
        individuos[i] = mutante;
    }
}

void Mutacao::aplicarMutacaoBest1(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites, double melhorAptidao) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    srand(static_cast<unsigned int>(time(0))); 

    for (int i = 0; i < tamanho; ++i) {
        int b, c;
        do { b = rand() % tamanho; } while (b == i);
        do { c = rand() % tamanho; } while (c == i || c == b);

        std::vector<double> mutante(dimensoes);
        for (int j = 0; j < dimensoes; ++j) {
            mutante[j] = melhorAptidao + F * (individuos[b][j] - individuos[c][j]);
        }
        aplicarLimites(mutante, minLimites, maxLimites); /* Aplica os limites */
        individuos[i] = mutante;
    }
}

void Mutacao::aplicarMutacaoRand2(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    srand(static_cast<unsigned int>(time(0))); // Semente para gerador de números aleatórios

    for (int i = 0; i < tamanho; ++i) {
        int a, b, c, d, e;
        do { a = rand() % tamanho; } while (a == i);
        do { b = rand() % tamanho; } while (b == i || b == a);
        do { c = rand() % tamanho; } while (c == i || c == a || c == b);
        do { d = rand() % tamanho; } while (d == i || d == a || d == b || d == c);
        do { e = rand() % tamanho; } while (e == i || e == a || e == b || e == c || e == d);

        std::vector<double> mutante(dimensoes);
        for (int j = 0; j < dimensoes; ++j) {
            mutante[j] = individuos[a][j] + F * (individuos[b][j] - individuos[c][j]) + F * (individuos[d][j] - individuos[e][j]);
        }
        aplicarLimites(mutante, minLimites, maxLimites); /* Aplica os limites */
        individuos[i] = mutante;
    }
}

/*Recombinação == crosover*/
void Mutacao::aplicarRecombinacaoBinomial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    srand(static_cast<unsigned int>(time(0))); // Semente para gerador de números aleatórios

    for (int i = 0; i < tamanho; ++i) {
        std::vector<double> filho(dimensoes);
        int jrand = rand() % dimensoes;
        for (int j = 0; j < dimensoes; ++j) {
            if (rand() / static_cast<double>(RAND_MAX) <= CR || j == jrand) {
                filho[j] = individuos[i][j];
            } else {
                filho[j] = individuos[i][j]; // Manter o valor original
            }
        }
        aplicarLimites(filho, minLimites, maxLimites); /* Aplica os limites */
        individuos[i] = filho;
    }
}

void Mutacao::aplicarRecombinacaoExponencial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    srand(static_cast<unsigned int>(time(0))); // Semente para gerador de números aleatórios

    for (int i = 0; i < tamanho; ++i) {
        std::vector<double> filho(dimensoes);
        int jrand = rand() % dimensoes;
        int L = 0;
        for (int j = 0; j < dimensoes; ++j) {
            if (rand() / static_cast<double>(RAND_MAX) <= CR || j == jrand) {
                filho[j] = individuos[i][j];
                L++;
            } else {
                break;
            }
        }
        for (int j = L; j < dimensoes; ++j) {
            filho[j] = individuos[i][j]; // Manter o valor original
        }
        aplicarLimites(filho, minLimites, maxLimites); /* Aplica os limites */
        individuos[i] = filho;
    }
}
