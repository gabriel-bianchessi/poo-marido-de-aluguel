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

const Habilidade* PrestadorDeServico::buscarHabilidade(int id) const {
    for (const auto& habilidade : habilidades) {
        if (habilidade.getId() == id) {
            return &habilidade;
        }
    }

    return nullptr;
}

std::vector<const Habilidade*> PrestadorDeServico::buscarHabilidade(const std::string& nome) const {
    std::vector<const Habilidade*> resultado;

    for (const auto& habilidade : habilidades) {
        if (habilidade.getNome() == nome) {
            resultado.push_back(&habilidade);
        }
    }

    return resultado;
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
