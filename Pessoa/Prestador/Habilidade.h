#pragma once

#include <string>

class Habilidade {
private:
    int id;
    std::string nome;

public:
    Habilidade(int id, const std::string& nome);

    int getId() const;
    const std::string& getNome() const;
};
