#pragma once

#include "IMetodoPagamento.h"

class CartaoDebito : public IMetodoPagamento {
private:
    bool pagamentoConfirmado;

public:
    CartaoDebito();

    void pagar(double valor) override;
    bool verificarPagamento() const override;
    std::string getDescricao() const override;
};
