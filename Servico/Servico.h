#pragma once

#include <string>

#include "Data.h"
#include "Pagamento.h"
#include "StatusServico.h"

class Cliente;
class PrestadorDeServico;

class Servico {
private:
    int id;
    std::string descricao;
    Data data;
    StatusServico status;
    Cliente* cliente;
    PrestadorDeServico* prestador;
    Pagamento pagamento;

public:
    Servico(int id,
            const std::string& descricao,
            const Data& data,
            Cliente& cliente,
            PrestadorDeServico& prestador,
            Pagamento pagamento);

    int getId() const;
    const std::string& getDescricao() const;
    const Data& getData() const;
    StatusServico getStatus() const;
    Cliente& getCliente() const;
    PrestadorDeServico& getPrestador() const;
    Pagamento& getPagamento();
    const Pagamento& getPagamento() const;

    bool processarPagamento();
    void iniciar();
    void concluir();
    void cancelar();
    std::string resumo() const;
};
