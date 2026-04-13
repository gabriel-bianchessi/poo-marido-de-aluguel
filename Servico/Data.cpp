#include "Data.h"

#include <ctime>
#include <iomanip>
#include <sstream>

Data::Data(int dia, int mes, int ano) : dia(dia), mes(mes), ano(ano) {}

int Data::getDia() const {
    return dia;
}

int Data::getMes() const {
    return mes;
}

int Data::getAno() const {
    return ano;
}

bool Data::mesmaData(const Data& outra) const {
    return dia == outra.dia && mes == outra.mes && ano == outra.ano;
}

int Data::calcularIdade(const Data& referencia) const {
    int idade = referencia.ano - ano;

    if (referencia.mes < mes || (referencia.mes == mes && referencia.dia < dia)) {
        idade--;
    }

    return idade;
}

std::string Data::toString() const {
    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(2) << dia << "/"
           << std::setw(2) << mes << "/" << ano;
    return stream.str();
}

Data Data::hoje() {
    std::time_t agora = std::time(nullptr);
    std::tm dataAtual = *std::localtime(&agora);
    return Data(dataAtual.tm_mday, dataAtual.tm_mon + 1, dataAtual.tm_year + 1900);
}
