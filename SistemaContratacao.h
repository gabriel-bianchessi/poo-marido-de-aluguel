#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Cliente.h"
#include "IMetodoPagamento.h"
#include "PrestadorDeServico.h"
#include "Servico.h"

class SistemaContratacao {
private:
    std::vector<std::unique_ptr<Cliente>> clientes;
    std::vector<std::unique_ptr<PrestadorDeServico>> prestadores;
    std::vector<std::unique_ptr<Servico>> servicos;
    int proximoIdCliente = 1;
    int proximoIdPrestador = 1;
    int proximoIdServico = 1;

public:
    Cliente& cadastrarCliente(const std::string& nome,
                              const std::string& documento,
                              TipoDocumento tipoDocumento,
                              const Data& dataNascimento);

    PrestadorDeServico& cadastrarPrestador(const std::string& nome,
                                           const std::string& documento,
                                           TipoDocumento tipoDocumento,
                                           const Data& dataNascimento);

    Servico* contratarServico(const std::string& descricao,
                              Cliente& cliente,
                              PrestadorDeServico& prestador,
                              const Data& data,
                              double valor,
                              std::unique_ptr<IMetodoPagamento> metodo);

    Cliente* buscarCliente(int id);
    std::vector<Cliente*> buscarCliente(const std::string& nome);
    PrestadorDeServico* buscarPrestador(int id);
    std::vector<PrestadorDeServico*> buscarPrestador(const std::string& nome);
    Servico* buscarServico(int id);
    std::vector<Servico*> buscarServico(const std::string& descricao);

    const std::vector<std::unique_ptr<Cliente>>& getClientes() const;
    const std::vector<std::unique_ptr<PrestadorDeServico>>& getPrestadores() const;
    const std::vector<std::unique_ptr<Servico>>& getServicos() const;
};
