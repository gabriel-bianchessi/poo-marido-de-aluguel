#pragma once

#include <string>

#include "Data.h"
#include "TipoDocumento.h"

class Pessoa {
private:
    int id;
    std::string nome;
    std::string documento;
    TipoDocumento tipoDocumento;
    Data dataNascimento;

public:
    Pessoa(int id,
           const std::string& nome,
           const std::string& documento,
           TipoDocumento tipoDocumento,
           const Data& dataNascimento);

    virtual ~Pessoa() = default;

    int getId() const;
    const std::string& getNome() const;
    const std::string& getDocumento() const;
    TipoDocumento getTipoDocumento() const;
    const Data& getDataNascimento() const;
    bool ehMaiorDeIdade() const;
};
