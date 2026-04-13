#pragma once

#include <memory>
#include <string>

#include "SistemaContratacao.h"

class AplicacaoConsole {
private:
    SistemaContratacao sistema;
    bool dadosExemploCarregados = false;
    int proximoIdHabilidade = 1;

    void mostrarMenu() const;
    void executarOpcao(int opcao, bool& executando);
    void carregarDadosExemplo();
    void cadastrarCliente();
    void cadastrarPrestador();
    void adicionarHabilidade();
    void contratarServico();
    void listarClientes() const;
    void listarPrestadores() const;
    void listarServicos() const;
    void processarPagamentoServico();
    void alterarStatusServico();
    int lerInteiro(const std::string& mensagem) const;
    double lerDouble(const std::string& mensagem) const;
    std::string lerTexto(const std::string& mensagem) const;
    Data lerData(const std::string& contexto) const;
    TipoDocumento lerTipoDocumento() const;
    std::unique_ptr<IMetodoPagamento> criarMetodoPagamento() const;
    bool dataValida(int dia, int mes, int ano) const;
    static bool tentarLerInteiro(const std::string& texto, int& valor);
    static bool tentarLerDouble(const std::string& texto, double& valor);

public:
    void executar();
};
