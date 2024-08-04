#ifndef POPULACAO_HPP
#define POPULACAO_HPP

#include "mutacao.hpp"
#include "selecao.hpp"
#include <vector>
#include <string>

class populacao {
private:
    int tamanho;
    std::vector<std::vector<double>> individuos;
    double min;
    double max;
    double melhorAptidao;
    int geracoesSemMelhora;

public:
    // Construtor que inicializa a população
    populacao(int tamanho, double min, double max);
    // Obtém o tamanho da população
    int getTamanho();
    // Define o tamanho da população
    void setTamanho(int tamanho);
    // Obtém o valor mínimo de um gene
    double getMin();
    // Obtém o valor máximo de um gene
    double getMax();
    // Inicializa a população com valores aleatórios
    void iniciarPopulacao();
    // Mostra os indivíduos da população
    void mostrarPopulacao();
    // Aplica a mutação aos indivíduos da população
    void mutacao(double F, const std::string& estrategia);
    // Aplica a recombinação aos indivíduos da população, croosver
    void recombinacao(double CR, const std::string& estrategia);
    // Aplica a seleção aos indivíduos da população
    void selecao(const std::vector<double>& x, const std::vector<double>& y);
    // Verifica se o critério de parada foi alcançado
    bool criterioParada(int maxGeracoes, double limiarMelhora, int maxGeracoesSemMelhora);
    // Obtém os indivíduos da população
    std::vector<std::vector<double>> getIndividuos();

    ~populacao() = default;
};

#endif
