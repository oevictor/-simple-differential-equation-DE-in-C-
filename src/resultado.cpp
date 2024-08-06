#include "resultado.hpp"
#include <iostream>
  
  
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
};
    

