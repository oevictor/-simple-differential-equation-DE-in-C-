#ifndef POPULACAO_HPP
#define POPULACAO_HPP

#include "mutacao.hpp"
#include "selecao.hpp"
#include <vector>
#include <string>
#include <fstream>

class populacao {
private:
    int tamanho;
    std::vector<std::vector<double>> individuos;
    std::vector<double> minLimites;
    std::vector<double> maxLimites;
    double melhorAptidao;
    int geracoesSemMelhora;

public:
    // Construtor que inicializa a população
    populacao(int tamanho, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);
    // Obtém o tamanho da população
    int getTamanho();
    // Define o tamanho da população
    void setTamanho(int tamanho);
    // Inicializa a população com valores aleatórios
    void iniciarPopulacao();
    // Mostra os indivíduos da população
    std::vector<std::vector<double>> mostrarPopulacao();
    // Aplica a mutação aos indivíduos da população
    void mutacao(double F, const std::string& estrategia);
    // Aplica a recombinação aos indivíduos da população
    void recombinacao(double CR, const std::string& estrategia);
    // Aplica a seleção aos indivíduos da população
    void selecao(const std::vector<double>& x, const std::vector<double>& y, std::vector<std::vector<double>>& melhoresCandidatos);
    // Verifica se o critério de parada foi alcançado
    bool criterioParada(int maxGeracoes, double limiarMelhora, int maxGeracoesSemMelhora);
    // Obtém os indivíduos da população
    std::vector<std::vector<double>>& getIndividuos(); // Retorna uma referência não constante
    // Salva o melhor indivíduo em um arquivo
    void saveBestIndividual(const std::string& filename);
    // Salva a população inteira em um arquivo
    void savePopulation(const std::string& filename);
    // Verifica a diversidade da população
    bool criterioDiversidade(double limiarDiversidade);
    // Ajusta os parâmetros F e CR adaptativamente 
    void ajustarParametros(double& F, double& CR);

    // Métodos para acessar os membros privados
    double getMelhorAptidao() const;
    int getGeracoesSemMelhora() const;

    ~populacao() = default;
};

#endif // POPULACAO_HPP
