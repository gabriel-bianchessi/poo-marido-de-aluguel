#include "Dinheiro.h"

Dinheiro::Dinheiro()
    : pagamentoConfirmado(false), troco(0.0), ultimoValorCobrado(0.0) {}

void Dinheiro::pagar(double valor) {
    ultimoValorCobrado = valor;
    troco = 0.0;
    pagamentoConfirmado = valor > 0.0;
}

bool Dinheiro::verificarPagamento() const {
    return pagamentoConfirmado;
}

std::string Dinheiro::getDescricao() const {
    return "Dinheiro";
}

double Dinheiro::calcularTroco(double valorRecebido) {
    troco = valorRecebido - ultimoValorCobrado;
    return troco;
}

double Dinheiro::getTroco() const {
    return troco;
}
