#include "resultado.hpp"
#include <fstream>
#include <iostream>
#include <sstream> 
#include <string>
#include <vector>

// Save data to a CSV file
void resultado::saveToCSV(const std::vector<std::vector<double>>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) file << ",";
            }
            file << "\n";
        }
        file.close();
        std::cout << "Arquivo " << filename << " salvo com sucesso." << std::endl;
    } else {
        std::cerr << "Não foi possível salvar o arquivo " << filename << std::endl;
    }
}

// Load data from a CSV file
std::vector<std::vector<double>> resultado::loadFromCSV(const std::string& filename) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<double> row;
            std::stringstream lineStream(line);
            std::string cell;
            while (std::getline(lineStream, cell, ',')) {
                row.push_back(std::stod(cell));
            }
            data.push_back(row);
        }
        file.close();
        std::cout << "Arquivo " << filename << " carregado com sucesso." << std::endl;
    } else {
        std::cerr << "Não foi possível carregar o arquivo " << filename << std::endl;
    }
    return data;
}

// Display loaded data
void resultado::mostrarDados(const std::vector<std::vector<double>>& data) {
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << row[i] << " ";
        }
        std::cout << std::endl;
    }
}
