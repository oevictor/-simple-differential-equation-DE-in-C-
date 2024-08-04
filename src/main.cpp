#include "populacao.hpp"
#include <iostream>
#include <vector>

int main() {
    int tamanho = 50000;
    double min = 1.0;
    double max = 50.0;
    double F = 0.75;
    double CR = 0.9;
    int maxGeracoes = 1000;
    double limiarMelhora = 1e-6;
    int maxGeracoesSemMelhora = 10;

    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {1, 4, 9, 16, 25};

    populacao pop(tamanho, min, max);
    pop.iniciarPopulacao();

    for (int g = 0; g < maxGeracoes; ++g) {
        pop.mutacao(F, "rand/1");
        pop.recombinacao(CR, "binomial");
        pop.selecao(x, y);

        if (pop.criterioParada(maxGeracoes, limiarMelhora, maxGeracoesSemMelhora)) {
            std::cout << "Convergência atingida na geração " << g + 1 << std::endl;
            break;
        }

        std::cout << "Geração " << g + 1 << ":" << std::endl;
        pop.mostrarPopulacao();
    }

    std::cout << "População Final:" << std::endl;
    pop.mostrarPopulacao();

    return 0;
}
