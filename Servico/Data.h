#pragma once

#include <string>

class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    Data(int dia = 1, int mes = 1, int ano = 2000);

    int getDia() const;
    int getMes() const;
    int getAno() const;

    bool mesmaData(const Data& outra) const;
    int calcularIdade(const Data& referencia) const;
    std::string toString() const;

    static Data hoje();
};
