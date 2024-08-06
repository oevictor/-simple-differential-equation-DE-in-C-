#ifndef RESULTADO_HPP
#define RESULTADO_HPP

#include <fstream> // para salvar o arquivo CSV
#include <vector>
#include <iostream>
/*Organizando os resultados e saidas das populações*/

class resultado{
public:
    void saveToCSV(const std::vector<std::vector<double>>& data, const std::string& filename); 
};

#endif 