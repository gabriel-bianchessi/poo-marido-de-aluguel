#include "CartaoCredito.h"

CartaoCredito::CartaoCredito(int parcelas)
    : parcelas(parcelas > 0 ? parcelas : 1),
      valorParcela(0.0),
      pagamentoConfirmado(false) {}

void CartaoCredito::pagar(double valor) {
    valorParcela = calcularParcela(valor);
    pagamentoConfirmado = valor > 0.0;
}

bool CartaoCredito::verificarPagamento() const {
    return pagamentoConfirmado;
}

std::string CartaoCredito::getDescricao() const {
    return "Cartao de credito";
}

double CartaoCredito::calcularParcela(double valor) {
    return valor / parcelas;
}

int CartaoCredito::getParcelas() const {
    return parcelas;
}

double CartaoCredito::getValorParcela() const {
    return valorParcela;
}
