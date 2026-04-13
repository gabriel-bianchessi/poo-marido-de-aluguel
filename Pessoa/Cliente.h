#pragma once

#include <vector>

#include "Pessoa.h"

class Servico;

class Cliente : public Pessoa {
private:
    std::vector<Servico*> servicos;

public:
    using Pessoa::Pessoa;

    void adicionarServico(Servico& servico);
    const std::vector<Servico*>& getServicos() const;
};
