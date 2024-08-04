#ifndef MUTACAO_HPP
#define MUTACAO_HPP

#include <vector>

class Mutacao {
public:
    // Aplica a mutação rand/1 na população
    static void aplicarMutacaoRand1(std::vector<std::vector<double>>& individuos, double F, double min, double max);

    // Aplica a mutação best/1 na população
    static void aplicarMutacaoBest1(std::vector<std::vector<double>>& individuos, double F, double min, double max, double melhorAptidao);

    // Aplica a mutação rand/2 na população
    static void aplicarMutacaoRand2(std::vector<std::vector<double>>& individuos, double F, double min, double max);

    // Aplica a recombinação binomial na população
    static void aplicarRecombinacaoBinomial(std::vector<std::vector<double>>& individuos, double CR);

    // Aplica a recombinação exponencial na população
    static void aplicarRecombinacaoExponencial(std::vector<std::vector<double>>& individuos, double CR);
    
    //Destrutor
    ~Mutacao() = default; 
};

#endif
