#ifndef MUTACAO_HPP
#define MUTACAO_HPP

#include <vector>

class Mutacao {
public:


    void aplicarMutacaoRand1(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);
    // // Aplica a mutação best/1 na população
    void aplicarMutacaoBest1(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites, double melhorAptidao);
    // // Aplica a mutação rand/2 na população
    void aplicarMutacaoRand2(std::vector<std::vector<double>>& individuos, double F, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);
     // // Aplica a recombinação binomial na população
    void aplicarRecombinacaoBinomial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);
    // // Aplica a recombinação exponencial na população
    void aplicarRecombinacaoExponencial(std::vector<std::vector<double>>& individuos, double CR, const std::vector<double>& minLimites, const std::vector<double>& maxLimites);

   
    
    //Destrutor
    ~Mutacao() = default; 
};

#endif
