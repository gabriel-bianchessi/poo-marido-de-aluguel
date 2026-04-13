#pragma once

#include <string>

class IMetodoPagamento {
public:
    virtual ~IMetodoPagamento() = default;

    virtual void pagar(double valor) = 0;
    virtual bool verificarPagamento() const = 0;
    virtual std::string getDescricao() const = 0;
};
