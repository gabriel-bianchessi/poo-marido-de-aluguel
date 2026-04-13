#pragma once

#include "IMetodoPagamento.h"

class Dinheiro : public IMetodoPagamento {
private:
    bool pagamentoConfirmado;
    double troco;
    double ultimoValorCobrado;

public:
    Dinheiro();

    void pagar(double valor) override;
    bool verificarPagamento() const override;
    std::string getDescricao() const override;

    double calcularTroco(double valorRecebido);
    double getTroco() const;
};
