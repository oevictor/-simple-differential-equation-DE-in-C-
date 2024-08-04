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

// Gera um valor aleatório entre min e max
double random_value(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

// Construtor que inicializa a população com valores padrão.
/*O tamanho dos invividos, tambem deve ser uma escolha da função em python*/
populacao::populacao(int tamanho, double min, double max) : tamanho(tamanho), min(min), max(max), melhorAptidao(std::numeric_limits<double>::max()), geracoesSemMelhora(0) {
    individuos.resize(tamanho, std::vector<double>(20)); /*resize para aumentar o tamanho do conteiner */
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

// Retorna o valor mínimo de um gene
double populacao::getMin() {
    return min;
}

// Retorna o valor máximo de um gene
double populacao::getMax() {
    return max;
}

// Inicializa a população com valores aleatórios
void populacao::iniciarPopulacao() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < tamanho; ++i) {
        for (std::vector<double>::size_type j = 0; j < individuos[i].size(); ++j) {
            individuos[i][j] = random_value(min, max);
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
    std::cout << "Aplicando mutação com estratégia " << estrategia << " e fator F = " << F << std::endl;
    if (estrategia == "rand/1") {
        Mutacao::aplicarMutacaoRand1(individuos, F, min, max);
    } else if (estrategia == "best/1") {
        Mutacao::aplicarMutacaoBest1(individuos, F, min, max, melhorAptidao);
    } else if (estrategia == "rand/2") {
        Mutacao::aplicarMutacaoRand2(individuos, F, min, max);
    } else {
        std::cerr << "Estratégia de mutação desconhecida: " << estrategia << std::endl;
    }
}

// Aplica a seleção aos indivíduos da população
void populacao::selecao(const std::vector<double>& x, const std::vector<double>& y) {
    std::cout << "Aplicando seleção baseada nos dados de aptidão." << std::endl;
    Selecao::aplicarSelecao(individuos, x, y, melhorAptidao, geracoesSemMelhora);
    std::cout << "Melhor aptidão atual: " << melhorAptidao << std::endl;
}

// Aplica a recombinação aos indivíduos da população
/*tambem conhecido como croosver*/
void populacao::recombinacao(double CR, const std::string& estrategia) {
    std::cout << "Aplicando recombinação com estratégia " << estrategia << " e taxa CR = " << CR << std::endl;
    if (estrategia == "binomial") {
        Mutacao::aplicarRecombinacaoBinomial(individuos, CR);
    } else if (estrategia == "exponencial") {
        Mutacao::aplicarRecombinacaoExponencial(individuos, CR);
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
