#include "Pessoa.h"

Pessoa::Pessoa(int id,
               const std::string& nome,
               const std::string& documento,
               TipoDocumento tipoDocumento,
               const Data& dataNascimento)
    : id(id),
      nome(nome),
      documento(documento),
      tipoDocumento(tipoDocumento),
      dataNascimento(dataNascimento) {}

int Pessoa::getId() const {
    return id;
}

const std::string& Pessoa::getNome() const {
    return nome;
}

const std::string& Pessoa::getDocumento() const {
    return documento;
}

TipoDocumento Pessoa::getTipoDocumento() const {
    return tipoDocumento;
}

const Data& Pessoa::getDataNascimento() const {
    return dataNascimento;
}

bool Pessoa::ehMaiorDeIdade() const {
    return dataNascimento.calcularIdade(Data::hoje()) >= 18;
}
