#include "mutacao.hpp"
#include <cstdlib>
#include <ctime>

/*DE schemes are
named. The general convention used above is DE/x/y/z, where
DE stands for “differential evolution,” x represents a string
denoting the base vector to be perturbed, y is the number
of difference vectors considered for perturbation of x, and z
stands for the type of crossover being used (exp: exponential;
bin: binomial).

Differential Evolution: A Survey of the

State-of-the-Art

Swagatam Das, Member, IEEE, and Ponnuthurai Nagaratnam Suganthan, Senior Member, IEEE
*/

void Mutacao::aplicarMutacaoRand1(std::vector<std::vector<double>>& individuos, double F, double min, double max) {
    int tamanho = individuos.size();
    int dimensoes = individuos[0].size();

    srand(static_cast<unsigned int>(time(0))); // Semente para gerador de números aleatórios

    for (int i = 0; i < tamanho; ++i) {
        int a, b, c;
        do { a = rand() % tamanho; } while (a == i); /*% retorna o modulo de uma operação, no caso um numero entre 0 e tamanho-1*/
        do { b = rand() % tamanho; } while (b == i || b == a); /*|| Siginifica "or"*/
        do { c = rand() % tamanho; } while (c == i || c == a || c == b);

        std::vector<double> mutante(dimensoes);
        for (int j = 0; j < dimensoes; ++j) {
            mutante[j] = individuos[a][j] + F * (individuos[b][j] - individuos[c][j]); /*realiza a operação classica de mutação*/
            if (mutante[j] < min) mutante[j] = min; /*Selecionando os menores valor da mutação*/
            if (mutante[j] > max) mutante[j] = max; /*Selecionando os maiores valor da mutação*/
        }
        individuos[i] = mutante;
    }
}

void Mutacao::aplicarMutacaoBest1(std::vector<std::vector<double>>& individuos, double F, double min, double max, double melhorAptidao) {
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
            if (mutante[j] < min) mutante[j] = min;
            if (mutante[j] > max) mutante[j] = max;
        }
        individuos[i] = mutante;
    }
}

void Mutacao::aplicarMutacaoRand2(std::vector<std::vector<double>>& individuos, double F, double min, double max) {
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
            if (mutante[j] < min) mutante[j] = min;
            if (mutante[j] > max) mutante[j] = max;
        }
        individuos[i] = mutante;
    }
}

void Mutacao::aplicarRecombinacaoBinomial(std::vector<std::vector<double>>& individuos, double CR) {
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
        individuos[i] = filho;
    }
}

void Mutacao::aplicarRecombinacaoExponencial(std::vector<std::vector<double>>& individuos, double CR) {
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
        individuos[i] = filho;
    }
}
