#pragma once

#include <string>

enum class TipoDocumento {
    CPF,
    CNPJ
};

inline std::string tipoDocumentoParaTexto(TipoDocumento tipo) {
    switch (tipo) {
        case TipoDocumento::CPF:
            return "CPF";
        case TipoDocumento::CNPJ:
            return "CNPJ";
    }

    return "Desconhecido";
}
