#include "Pagamento.h"

#include <utility>

Pagamento::Pagamento(double valor, std::unique_ptr<IMetodoPagamento> metodo)
    : valor(valor), metodo(std::move(metodo)), pago(false) {}

double Pagamento::getValor() const {
    return valor;
}

bool Pagamento::estaPago() const {
    return pago;
}

bool Pagamento::processar() {
    if (metodo == nullptr) {
        pago = false;
        return false;
    }

    metodo->pagar(valor);
    pago = metodo->verificarPagamento();
    return pago;
}

std::string Pagamento::getDescricaoMetodo() const {
    if (metodo == nullptr) {
        return "Sem metodo";
    }

    return metodo->getDescricao();
}
