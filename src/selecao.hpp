#ifndef SELECAO_HPP
#define SELECAO_HPP

#include <vector>

class Selecao {
public:
    // Calcula a aptidão de um indivíduo com base nos valores x e y fornecidos
    static double calcularAptidao(const std::vector<double>& individuo, const std::vector<double>& x, const std::vector<double>& y);

    // Aplica o processo de seleção à população
    static void aplicarSelecao(std::vector<std::vector<double>>& individuos, const std::vector<double>& x, const std::vector<double>& y, double& melhorAptidao, int& geracoesSemMelhora);
    ~Selecao() = default;
};

#endif
