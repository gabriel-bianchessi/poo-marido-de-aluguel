#include "PrestadorDeServico.h"

#include "Servico.h"

void PrestadorDeServico::adicionarHabilidade(const Habilidade& habilidade) {
    habilidades.push_back(habilidade);
}

void PrestadorDeServico::adicionarServico(Servico& servico) {
    servicos.push_back(&servico);
}

const std::vector<Habilidade>& PrestadorDeServico::getHabilidades() const {
    return habilidades;
}

const std::vector<Servico*>& PrestadorDeServico::getServicos() const {
    return servicos;
}

bool PrestadorDeServico::estaDisponivelEm(const Data& data) const {
    for (const Servico* servico : servicos) {
        if (servico != nullptr &&
            servico->getData().mesmaData(data) &&
            servico->getStatus() != StatusServico::CANCELADO) {
            return false;
        }
    }

    return true;
}
