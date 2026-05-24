#include "SistemaContratacao.h"

#include <utility>

Cliente& SistemaContratacao::cadastrarCliente(const std::string& nome,
                                              const std::string& documento,
                                              TipoDocumento tipoDocumento,
                                              const Data& dataNascimento) {
    clientes.push_back(
        std::make_unique<Cliente>(proximoIdCliente++, nome, documento, tipoDocumento, dataNascimento));
    return *clientes.back();
}

PrestadorDeServico& SistemaContratacao::cadastrarPrestador(const std::string& nome,
                                                           const std::string& documento,
                                                           TipoDocumento tipoDocumento,
                                                           const Data& dataNascimento) {
    prestadores.push_back(std::make_unique<PrestadorDeServico>(
        proximoIdPrestador++, nome, documento, tipoDocumento, dataNascimento));
    return *prestadores.back();
}

Servico* SistemaContratacao::contratarServico(const std::string& descricao,
                                              Cliente& cliente,
                                              PrestadorDeServico& prestador,
                                              const Data& data,
                                              double valor,
                                              std::unique_ptr<IMetodoPagamento> metodo) {
    if (!prestador.estaDisponivelEm(data)) {
        return nullptr;
    }

    auto servico = std::make_unique<Servico>(
        proximoIdServico++,
        descricao,
        data,
        cliente,
        prestador,
        Pagamento(valor, std::move(metodo)));

    Servico* referencia = servico.get();
    cliente.adicionarServico(*referencia);
    prestador.adicionarServico(*referencia);
    servicos.push_back(std::move(servico));

    return referencia;
}

Cliente* SistemaContratacao::buscarCliente(int id) {
    for (const auto& cliente : clientes) {
        if (cliente != nullptr && cliente->getId() == id) {
            return cliente.get();
        }
    }

    return nullptr;
}

std::vector<Cliente*> SistemaContratacao::buscarCliente(const std::string& nome) {
    std::vector<Cliente*> resultado;

    for (const auto& cliente : clientes) {
        if (cliente != nullptr && cliente->getNome() == nome) {
            resultado.push_back(cliente.get());
        }
    }

    return resultado;
}

PrestadorDeServico* SistemaContratacao::buscarPrestador(int id) {
    for (const auto& prestador : prestadores) {
        if (prestador != nullptr && prestador->getId() == id) {
            return prestador.get();
        }
    }

    return nullptr;
}

std::vector<PrestadorDeServico*> SistemaContratacao::buscarPrestador(const std::string& nome) {
    std::vector<PrestadorDeServico*> resultado;

    for (const auto& prestador : prestadores) {
        if (prestador != nullptr && prestador->getNome() == nome) {
            resultado.push_back(prestador.get());
        }
    }

    return resultado;
}

Servico* SistemaContratacao::buscarServico(int id) {
    for (const auto& servico : servicos) {
        if (servico != nullptr && servico->getId() == id) {
            return servico.get();
        }
    }

    return nullptr;
}

std::vector<Servico*> SistemaContratacao::buscarServico(const std::string& descricao) {
    std::vector<Servico*> resultado;

    for (const auto& servico : servicos) {
        if (servico != nullptr && servico->getDescricao() == descricao) {
            resultado.push_back(servico.get());
        }
    }

    return resultado;
}

const std::vector<std::unique_ptr<Cliente>>& SistemaContratacao::getClientes() const {
    return clientes;
}

const std::vector<std::unique_ptr<PrestadorDeServico>>&
SistemaContratacao::getPrestadores() const {
    return prestadores;
}

const std::vector<std::unique_ptr<Servico>>& SistemaContratacao::getServicos() const {
    return servicos;
}
