#include "Habilidade.h"

Habilidade::Habilidade(int id, const std::string& nome) : id(id), nome(nome) {}

int Habilidade::getId() const {
    return id;
}

const std::string& Habilidade::getNome() const {
    return nome;
}
