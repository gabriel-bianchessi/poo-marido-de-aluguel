#include "Cliente.h"

void Cliente::adicionarServico(Servico& servico) {
    servicos.push_back(&servico);
}

const std::vector<Servico*>& Cliente::getServicos() const {
    return servicos;
}
