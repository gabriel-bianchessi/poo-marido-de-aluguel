#include "Servico.h"

#include <sstream>

#include "Cliente.h"
#include "PrestadorDeServico.h"

Servico::Servico(int id,
                 const std::string& descricao,
                 const Data& data,
                 Cliente& cliente,
                 PrestadorDeServico& prestador,
                 Pagamento pagamento)
    : id(id),
      descricao(descricao),
      data(data),
      status(StatusServico::AGENDADO),
      cliente(&cliente),
      prestador(&prestador),
      pagamento(std::move(pagamento)) {}

int Servico::getId() const {
    return id;
}

const std::string& Servico::getDescricao() const {
    return descricao;
}

const Data& Servico::getData() const {
    return data;
}

StatusServico Servico::getStatus() const {
    return status;
}

Cliente& Servico::getCliente() const {
    return *cliente;
}

PrestadorDeServico& Servico::getPrestador() const {
    return *prestador;
}

Pagamento& Servico::getPagamento() {
    return pagamento;
}

const Pagamento& Servico::getPagamento() const {
    return pagamento;
}

bool Servico::processarPagamento() {
    return pagamento.processar();
}

void Servico::iniciar() {
    status = StatusServico::EM_PROGRESSO;
}

void Servico::concluir() {
    status = StatusServico::CONCLUIDO;
}

void Servico::cancelar() {
    status = StatusServico::CANCELADO;
}

std::string Servico::resumo() const {
    std::ostringstream stream;
    stream << "Servico #" << id
           << " | descricao: " << descricao
           << " | data: " << data.toString()
           << " | cliente: " << cliente->getNome()
           << " | prestador: " << prestador->getNome()
           << " | status: " << statusServicoParaTexto(status)
           << " | pagamento: " << pagamento.getDescricaoMetodo()
           << " | valor: " << pagamento.getValor();
    return stream.str();
}
