#pragma once

#include <string>

#include "IMetodoPagamento.h"

class Pix : public IMetodoPagamento {
private:
    bool pagamentoConfirmado;
    std::string qrCode;
    std::string codigoCopiaCola;

public:
    Pix();

    void pagar(double valor) override;
    bool verificarPagamento() const override;
    std::string getDescricao() const override;

    std::string gerarQrCode();
    std::string gerarCodigoCopiaCola();
    const std::string& getQrCode() const;
    const std::string& getCodigoCopiaCola() const;
};
