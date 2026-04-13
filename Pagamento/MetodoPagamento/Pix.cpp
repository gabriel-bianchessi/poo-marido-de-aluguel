#include "Pix.h"

#include <iomanip>
#include <sstream>

Pix::Pix() : pagamentoConfirmado(false) {}

void Pix::pagar(double valor) {
    qrCode = gerarQrCode();
    codigoCopiaCola = gerarCodigoCopiaCola();
    pagamentoConfirmado = valor > 0.0;
}

bool Pix::verificarPagamento() const {
    return pagamentoConfirmado;
}

std::string Pix::getDescricao() const {
    return "Pix";
}

std::string Pix::gerarQrCode() {
    return "QR-PIX-PADRAO";
}

std::string Pix::gerarCodigoCopiaCola() {
    return "PIXCOPIACOLA0001";
}

const std::string& Pix::getQrCode() const {
    return qrCode;
}

const std::string& Pix::getCodigoCopiaCola() const {
    return codigoCopiaCola;
}
