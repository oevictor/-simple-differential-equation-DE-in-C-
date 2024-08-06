#ifndef RESULTADO_HPP
#define RESULTADO_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class resultado {
public:
    // Salva os dados em um arquivo CSV
    static void saveToCSV(const std::vector<std::vector<double>>& data, const std::string& filename);

    // Carrega os dados de um arquivo CSV
    static std::vector<std::vector<double>> loadFromCSV(const std::string& filename);

    // Mostra os dados carregados
    static void mostrarDados(const std::vector<std::vector<double>>& data);
};

#endif // RESULTADO_HPP
