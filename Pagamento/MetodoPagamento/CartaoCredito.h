#pragma once

#include "IMetodoPagamento.h"

class CartaoCredito : public IMetodoPagamento {
private:
    int parcelas;
    double valorParcela;
    bool pagamentoConfirmado;

public:
    explicit CartaoCredito(int parcelas = 1);

    void pagar(double valor) override;
    bool verificarPagamento() const override;
    std::string getDescricao() const override;

    double calcularParcela(double valor);
    int getParcelas() const;
    double getValorParcela() const;
};
