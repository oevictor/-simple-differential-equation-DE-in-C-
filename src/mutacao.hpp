#ifndef MUTACAO_HPP
#define MUTACAO_HPP

#include <vector>

extern double random_value(double min, double max);

class Mutacao {
public:
    // Declarações das funções de mutação e recombinação

    void aplicarMutacaoRand1(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);
    void aplicarMutacaoBest1(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites, const std::vector<double>& melhorIndividuo); // Alterado aqui
    void aplicarMutacaoRand2(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);
    void aplicarRecombinacaoBinomial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);
    void aplicarRecombinacaoExponencial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);

    ~Mutacao() = default; 
};

#endif
