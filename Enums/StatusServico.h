#pragma once

#include <string>

enum class StatusServico {
    PENDENTE,
    AGENDADO,
    EM_PROGRESSO,
    CONCLUIDO,
    CANCELADO
};

inline std::string statusServicoParaTexto(StatusServico status) {
    switch (status) {
        case StatusServico::PENDENTE:
            return "PENDENTE";
        case StatusServico::AGENDADO:
            return "AGENDADO";
        case StatusServico::EM_PROGRESSO:
            return "EM_PROGRESSO";
        case StatusServico::CONCLUIDO:
            return "CONCLUIDO";
        case StatusServico::CANCELADO:
            return "CANCELADO";
    }

    return "DESCONHECIDO";
}
