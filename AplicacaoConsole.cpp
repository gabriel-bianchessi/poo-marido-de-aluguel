#include "AplicacaoConsole.h"

#include <iostream>
#include <sstream>

#include "CartaoCredito.h"
#include "CartaoDebito.h"
#include "Dinheiro.h"
#include "Habilidade.h"
#include "Pix.h"

namespace {
std::string textoBooleano(bool valor) {
    return valor ? "sim" : "nao";
}
}

void AplicacaoConsole::executar() {
    bool executando = true;

    while (executando) {
        mostrarMenu();
        executarOpcao(lerInteiro("Escolha uma opcao: "), executando);
    }
}

void AplicacaoConsole::mostrarMenu() const {
    std::cout << "\n=== Marido de Aluguel ===\n";
    std::cout << "1. Carregar dados de exemplo\n";
    std::cout << "2. Cadastrar cliente\n";
    std::cout << "3. Cadastrar prestador\n";
    std::cout << "4. Adicionar habilidade a prestador\n";
    std::cout << "5. Contratar servico\n";
    std::cout << "6. Listar clientes\n";
    std::cout << "7. Listar prestadores\n";
    std::cout << "8. Listar servicos\n";
    std::cout << "9. Processar pagamento de servico\n";
    std::cout << "10. Alterar status de servico\n";
    std::cout << "0. Sair\n";
}

void AplicacaoConsole::executarOpcao(int opcao, bool& executando) {
    switch (opcao) {
        case 1:
            carregarDadosExemplo();
            break;
        case 2:
            cadastrarCliente();
            break;
        case 3:
            cadastrarPrestador();
            break;
        case 4:
            adicionarHabilidade();
            break;
        case 5:
            contratarServico();
            break;
        case 6:
            listarClientes();
            break;
        case 7:
            listarPrestadores();
            break;
        case 8:
            listarServicos();
            break;
        case 9:
            processarPagamentoServico();
            break;
        case 10:
            alterarStatusServico();
            break;
        case 0:
            executando = false;
            break;
        default:
            std::cout << "Opcao invalida.\n";
            break;
    }
}

void AplicacaoConsole::carregarDadosExemplo() {
    if (dadosExemploCarregados) {
        std::cout << "Os dados de exemplo ja foram carregados.\n";
        return;
    }

    Cliente& cliente = sistema.cadastrarCliente(
        "Dayse", "12345678900", TipoDocumento::CPF, Data(10, 5, 1998));

    PrestadorDeServico& joao = sistema.cadastrarPrestador(
        "Joao", "98765432100", TipoDocumento::CPF, Data(12, 8, 1990));
    joao.adicionarHabilidade(Habilidade(proximoIdHabilidade++, "Encanador"));
    joao.adicionarHabilidade(Habilidade(proximoIdHabilidade++, "Eletricista"));

    PrestadorDeServico& maria = sistema.cadastrarPrestador(
        "Maria", "11222333000199", TipoDocumento::CNPJ, Data(20, 3, 1988));
    maria.adicionarHabilidade(Habilidade(proximoIdHabilidade++, "Jardineira"));

    Servico* servico1 = sistema.contratarServico(
        "Conserto de pia", cliente, joao, Data(10, 4, 2026), 150.0, std::make_unique<Pix>());

    if (servico1 != nullptr) {
        servico1->processarPagamento();
    }

    Servico* servico2 = sistema.contratarServico(
        "Poda do jardim", cliente, maria, Data(11, 4, 2026), 120.0, std::make_unique<Dinheiro>());

    if (servico2 != nullptr) {
        servico2->processarPagamento();
        servico2->iniciar();
        servico2->concluir();
    }

    dadosExemploCarregados = true;

    std::cout << "Dados de exemplo carregados com sucesso.\n";
}

void AplicacaoConsole::cadastrarCliente() {
    const std::string nome = lerTexto("Nome do cliente: ");
    const std::string documento = lerTexto("Documento do cliente: ");
    const TipoDocumento tipoDocumento = lerTipoDocumento();
    const Data dataNascimento = lerData("Data de nascimento do cliente");

    Cliente& cliente = sistema.cadastrarCliente(nome, documento, tipoDocumento, dataNascimento);

    std::cout << "Cliente cadastrado com ID " << cliente.getId() << ".\n";
}

void AplicacaoConsole::cadastrarPrestador() {
    const std::string nome = lerTexto("Nome do prestador: ");
    const std::string documento = lerTexto("Documento do prestador: ");
    const TipoDocumento tipoDocumento = lerTipoDocumento();
    const Data dataNascimento = lerData("Data de nascimento do prestador");

    PrestadorDeServico& prestador =
        sistema.cadastrarPrestador(nome, documento, tipoDocumento, dataNascimento);

    std::cout << "Prestador cadastrado com ID " << prestador.getId() << ".\n";
}

void AplicacaoConsole::adicionarHabilidade() {
    if (sistema.getPrestadores().empty()) {
        std::cout << "Cadastre pelo menos um prestador antes de adicionar habilidades.\n";
        return;
    }

    listarPrestadores();

    PrestadorDeServico* prestador =
        sistema.buscarPrestador(lerInteiro("ID do prestador: "));

    if (prestador == nullptr) {
        std::cout << "Prestador nao encontrado.\n";
        return;
    }

    prestador->adicionarHabilidade(Habilidade(proximoIdHabilidade++, lerTexto("Nome da habilidade: ")));
    std::cout << "Habilidade adicionada com sucesso.\n";
}

void AplicacaoConsole::contratarServico() {
    if (sistema.getClientes().empty()) {
        std::cout << "Cadastre pelo menos um cliente antes de contratar servicos.\n";
        return;
    }

    if (sistema.getPrestadores().empty()) {
        std::cout << "Cadastre pelo menos um prestador antes de contratar servicos.\n";
        return;
    }

    listarClientes();
    Cliente* cliente = sistema.buscarCliente(lerInteiro("ID do cliente: "));

    if (cliente == nullptr) {
        std::cout << "Cliente nao encontrado.\n";
        return;
    }

    listarPrestadores();
    PrestadorDeServico* prestador =
        sistema.buscarPrestador(lerInteiro("ID do prestador: "));

    if (prestador == nullptr) {
        std::cout << "Prestador nao encontrado.\n";
        return;
    }

    const std::string descricao = lerTexto("Descricao do servico: ");
    const Data data = lerData("Data do servico");
    double valor = 0.0;

    do {
        valor = lerDouble("Valor do servico: ");
        if (valor <= 0.0) {
            std::cout << "Informe um valor maior que zero.\n";
        }
    } while (valor <= 0.0);

    Servico* servico = sistema.contratarServico(
        descricao, *cliente, *prestador, data, valor, criarMetodoPagamento());

    if (servico == nullptr) {
        std::cout << "O prestador nao esta disponivel nessa data.\n";
        return;
    }

    std::cout << "Servico contratado com ID " << servico->getId() << ".\n";
}

void AplicacaoConsole::listarClientes() const {
    if (sistema.getClientes().empty()) {
        std::cout << "Nenhum cliente cadastrado.\n";
        return;
    }

    std::cout << "\nClientes cadastrados:\n";

    for (const auto& cliente : sistema.getClientes()) {
        std::cout << "[" << cliente->getId() << "] " << cliente->getNome()
                  << " | documento: " << cliente->getDocumento()
                  << " | tipo: " << tipoDocumentoParaTexto(cliente->getTipoDocumento())
                  << " | maior de idade: " << textoBooleano(cliente->ehMaiorDeIdade())
                  << " | servicos: " << cliente->getServicos().size() << "\n";
    }
}

void AplicacaoConsole::listarPrestadores() const {
    if (sistema.getPrestadores().empty()) {
        std::cout << "Nenhum prestador cadastrado.\n";
        return;
    }

    std::cout << "\nPrestadores cadastrados:\n";

    for (const auto& prestador : sistema.getPrestadores()) {
        std::cout << "[" << prestador->getId() << "] " << prestador->getNome()
                  << " | documento: " << prestador->getDocumento()
                  << " | tipo: " << tipoDocumentoParaTexto(prestador->getTipoDocumento())
                  << " | habilidades: ";

        if (prestador->getHabilidades().empty()) {
            std::cout << "nenhuma";
        } else {
            for (std::size_t i = 0; i < prestador->getHabilidades().size(); ++i) {
                if (i > 0) {
                    std::cout << ", ";
                }

                std::cout << prestador->getHabilidades()[i].getNome();
            }
        }

        std::cout << " | servicos: " << prestador->getServicos().size() << "\n";
    }
}

void AplicacaoConsole::listarServicos() const {
    if (sistema.getServicos().empty()) {
        std::cout << "Nenhum servico cadastrado.\n";
        return;
    }

    std::cout << "\nServicos cadastrados:\n";

    for (const auto& servico : sistema.getServicos()) {
        std::cout << servico->resumo()
                  << " | pago: " << textoBooleano(servico->getPagamento().estaPago()) << "\n";
    }
}

void AplicacaoConsole::processarPagamentoServico() {
    if (sistema.getServicos().empty()) {
        std::cout << "Nenhum servico cadastrado.\n";
        return;
    }

    listarServicos();

    Servico* servico = sistema.buscarServico(lerInteiro("ID do servico: "));

    if (servico == nullptr) {
        std::cout << "Servico nao encontrado.\n";
        return;
    }

    if (servico->getPagamento().estaPago()) {
        std::cout << "O pagamento desse servico ja foi processado.\n";
        return;
    }

    if (servico->processarPagamento()) {
        std::cout << "Pagamento processado com sucesso.\n";
        return;
    }

    std::cout << "Nao foi possivel processar o pagamento.\n";
}

void AplicacaoConsole::alterarStatusServico() {
    if (sistema.getServicos().empty()) {
        std::cout << "Nenhum servico cadastrado.\n";
        return;
    }

    listarServicos();

    Servico* servico = sistema.buscarServico(lerInteiro("ID do servico: "));

    if (servico == nullptr) {
        std::cout << "Servico nao encontrado.\n";
        return;
    }

    std::cout << "1. Iniciar\n";
    std::cout << "2. Concluir\n";
    std::cout << "3. Cancelar\n";

    switch (lerInteiro("Nova acao para o servico: ")) {
        case 1:
            servico->iniciar();
            break;
        case 2:
            servico->concluir();
            break;
        case 3:
            servico->cancelar();
            break;
        default:
            std::cout << "Opcao invalida.\n";
            return;
    }

    std::cout << "Status atualizado para "
              << statusServicoParaTexto(servico->getStatus()) << ".\n";
}

int AplicacaoConsole::lerInteiro(const std::string& mensagem) const {
    while (true) {
        std::cout << mensagem;

        std::string linha;
        std::getline(std::cin, linha);

        int valor = 0;
        if (tentarLerInteiro(linha, valor)) {
            return valor;
        }

        std::cout << "Informe um numero inteiro valido.\n";
    }
}

double AplicacaoConsole::lerDouble(const std::string& mensagem) const {
    while (true) {
        std::cout << mensagem;

        std::string linha;
        std::getline(std::cin, linha);

        double valor = 0.0;
        if (tentarLerDouble(linha, valor)) {
            return valor;
        }

        std::cout << "Informe um numero valido.\n";
    }
}

std::string AplicacaoConsole::lerTexto(const std::string& mensagem) const {
    while (true) {
        std::cout << mensagem;

        std::string valor;
        std::getline(std::cin, valor);

        if (!valor.empty()) {
            return valor;
        }

        std::cout << "O texto nao pode ficar vazio.\n";
    }
}

Data AplicacaoConsole::lerData(const std::string& contexto) const {
    while (true) {
        const int dia = lerInteiro(contexto + " - dia: ");
        const int mes = lerInteiro(contexto + " - mes: ");
        const int ano = lerInteiro(contexto + " - ano: ");

        if (dataValida(dia, mes, ano)) {
            return Data(dia, mes, ano);
        }

        std::cout << "Data invalida. Tente novamente.\n";
    }
}

TipoDocumento AplicacaoConsole::lerTipoDocumento() const {
    while (true) {
        std::cout << "1. CPF\n";
        std::cout << "2. CNPJ\n";

        switch (lerInteiro("Tipo de documento: ")) {
            case 1:
                return TipoDocumento::CPF;
            case 2:
                return TipoDocumento::CNPJ;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }
    }
}

std::unique_ptr<IMetodoPagamento> AplicacaoConsole::criarMetodoPagamento() const {
    while (true) {
        std::cout << "1. Pix\n";
        std::cout << "2. Dinheiro\n";
        std::cout << "3. Cartao de debito\n";
        std::cout << "4. Cartao de credito\n";

        switch (lerInteiro("Metodo de pagamento: ")) {
            case 1:
                return std::make_unique<Pix>();
            case 2:
                return std::make_unique<Dinheiro>();
            case 3:
                return std::make_unique<CartaoDebito>();
            case 4: {
                int parcelas = 0;

                do {
                    parcelas = lerInteiro("Quantidade de parcelas: ");
                    if (parcelas <= 0) {
                        std::cout << "Informe uma quantidade maior que zero.\n";
                    }
                } while (parcelas <= 0);

                return std::make_unique<CartaoCredito>(parcelas);
            }
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }
    }
}

bool AplicacaoConsole::dataValida(int dia, int mes, int ano) const {
    if (ano <= 0 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool anoBissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);

    if (anoBissexto) {
        diasPorMes[1] = 29;
    }

    return dia <= diasPorMes[mes - 1];
}

bool AplicacaoConsole::tentarLerInteiro(const std::string& texto, int& valor) {
    std::istringstream stream(texto);
    return (stream >> valor) && stream.eof();
}

bool AplicacaoConsole::tentarLerDouble(const std::string& texto, double& valor) {
    std::istringstream stream(texto);
    return (stream >> valor) && stream.eof();
}
