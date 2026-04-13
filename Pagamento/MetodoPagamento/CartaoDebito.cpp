#include "CartaoDebito.h"

CartaoDebito::CartaoDebito() : pagamentoConfirmado(false) {}

void CartaoDebito::pagar(double valor) {
    pagamentoConfirmado = valor > 0.0;
}

bool CartaoDebito::verificarPagamento() const {
    return pagamentoConfirmado;
}

std::string CartaoDebito::getDescricao() const {
    return "Cartao de debito";
}
