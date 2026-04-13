#pragma once

#include <memory>
#include <string>

#include "IMetodoPagamento.h"

class Pagamento {
private:
    double valor;
    std::unique_ptr<IMetodoPagamento> metodo;
    bool pago;

public:
    Pagamento(double valor, std::unique_ptr<IMetodoPagamento> metodo);

    Pagamento(Pagamento&& other) noexcept = default;
    Pagamento& operator=(Pagamento&& other) noexcept = default;
    Pagamento(const Pagamento&) = delete;
    Pagamento& operator=(const Pagamento&) = delete;

    double getValor() const;
    bool estaPago() const;
    bool processar();
    std::string getDescricaoMetodo() const;
};
