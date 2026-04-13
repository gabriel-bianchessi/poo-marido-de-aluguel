#pragma once

#include <vector>

#include "Habilidade.h"
#include "Pessoa.h"

class Servico;

class PrestadorDeServico : public Pessoa {
private:
    std::vector<Habilidade> habilidades;
    std::vector<Servico*> servicos;

public:
    using Pessoa::Pessoa;

    void adicionarHabilidade(const Habilidade& habilidade);
    void adicionarServico(Servico& servico);

    const std::vector<Habilidade>& getHabilidades() const;
    const std::vector<Servico*>& getServicos() const;
    bool estaDisponivelEm(const Data& data) const;
};
