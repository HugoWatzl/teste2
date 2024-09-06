#include <iostream>
#include <unordered_map>
#include <string>
#include <limits> // Para std::numeric_limits
#include <sstream> // Para std::stringstream

// Estrutura para armazenar informações da conta bancária
struct ContaBancaria {
    std::string cpf;
    std::string nome;
    std::string endereco;
    std::string telefone;
    double saldo;

    ContaBancaria(const std::string& cpf, const std::string& nome, const std::string& endereco, const std::string& telefone)
        : cpf(cpf), nome(nome), endereco(endereco), telefone(telefone), saldo(0.0) {}
};

// Mapa para gerenciar contas
std::unordered_map<std::string, ContaBancaria> contas;

// Função para criar uma conta
void criarConta(const std::string& cpf, const std::string& nome, const std::string& endereco, const std::string& telefone) {
    if (contas.find(cpf) == contas.end()) {
        contas.emplace(cpf, ContaBancaria(cpf, nome, endereco, telefone));
        std::cout << "Conta criada com sucesso!" << std::endl;
    } else {
        std::cout << "Conta já existente com esse CPF!" << std::endl;
    }
}

// Função para consultar uma conta
void consultarConta(const std::string& cpf) {
    auto it = contas.find(cpf);
    if (it != contas.end()) {
        const ContaBancaria& conta = it->second;
        std::cout << "Nome: " << conta.nome << std::endl;
        std::cout << "Endereço: " << conta.endereco << std::endl;
        std::cout << "Telefone: " << conta.telefone << std::endl;
        std::cout << "Saldo: R$ " << conta.saldo << std::endl;
    } else {
        std::cout << "Conta não encontrada!" << std::endl;
    }
}

// Função para remover uma conta
void removerConta(const std::string& cpf) {
    if (contas.erase(cpf)) {
        std::cout << "Conta removida com sucesso!" << std::endl;
    } else {
        std::cout << "Conta não encontrada!" << std::endl;
    }
}

// Função para editar uma conta
void editarConta(const std::string& cpf, const std::string& nome, const std::string& endereco, const std::string& telefone) {
    auto it = contas.find(cpf);
    if (it != contas.end()) {
        ContaBancaria& conta = it->second;
        conta.nome = nome;
        conta.endereco = endereco;
        conta.telefone = telefone;
        std::cout << "Informações da conta atualizadas com sucesso!" << std::endl;
    } else {
        std::cout << "Conta não encontrada!" << std::endl;
    }
}

// Função para realizar um depósito
void realizarDeposito(const std::string& cpf, double valor) {
    auto it = contas.find(cpf);
    if (it != contas.end()) {
        if (valor > 0) {
            it->second.saldo += valor;
            std::cout << "Depósito realizado com sucesso!" << std::endl;
        } else {
            std::cout << "Valor de depósito inválido!" << std::endl;
        }
    } else {
        std::cout << "Conta não encontrada!" << std::endl;
    }
}

// Função para realizar um saque
void realizarSaque(const std::string& cpf, double valor) {
    auto it = contas.find(cpf);
    if (it != contas.end()) {
        if (valor > 0 && valor <= it->second.saldo) {
            it->second.saldo -= valor;
            std::cout << "Saque realizado com sucesso!" << std::endl;
        } else {
            std::cout << "Saldo insuficiente ou valor inválido!" << std::endl;
        }
    } else {
        std::cout << "Conta não encontrada!" << std::endl;
    }
}

// Função auxiliar para verificar se uma string pode ser convertida para um número
bool validarDouble(const std::string& str, double& resultado) {
    std::stringstream ss(str);
    return (ss >> resultado) && (ss.eof()); // Verifica se a conversão foi bem-sucedida e se não há caracteres restantes
}

int main() {
    std::string opcao, cpf, nome, endereco, telefone, valorStr;
    double valor;

    std::cout << "Bem-vindo ao sistema bancário!" << std::endl;

    while (true) {
        std::cout << "\nEscolha uma opção:\n";
        std::cout << "1. Criar Conta\n";
        std::cout << "2. Consultar Conta\n";
        std::cout << "3. Remover Conta\n";
        std::cout << "4. Editar Conta\n";
        std::cout << "5. Depositar\n";
        std::cout << "6. Sacar\n";
        std::cout << "7. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer

        if (opcao == "1") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            std::cout << "Digite Nome: ";
            std::cin.ignore(); // Limpa o buffer
            std::getline(std::cin, nome);
            std::cout << "Digite Endereço: ";
            std::getline(std::cin, endereco);
            std::cout << "Digite Telefone: ";
            std::getline(std::cin, telefone);
            criarConta(cpf, nome, endereco, telefone);

        } else if (opcao == "2") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            consultarConta(cpf);

        } else if (opcao == "3") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            removerConta(cpf);

        } else if (opcao == "4") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            std::cout << "Digite Novo Nome: ";
            std::cin.ignore(); // Limpa o buffer
            std::getline(std::cin, nome);
            std::cout << "Digite Novo Endereço: ";
            std::getline(std::cin, endereco);
            std::cout << "Digite Novo Telefone: ";
            std::getline(std::cin, telefone);
            editarConta(cpf, nome, endereco, telefone);

        } else if (opcao == "5") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            std::cout << "Digite Valor para Depósito: ";
            std::getline(std::cin, valorStr); // Lê como string
            if (validarDouble(valorStr, valor)) {
                realizarDeposito(cpf, valor);
            } else {
                std::cout << "Número inválido para depósito!" << std::endl;
            }

        } else if (opcao == "6") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            std::cout << "Digite Valor para Saque: ";
            std::getline(std::cin, valorStr); // Lê como string
            if (validarDouble(valorStr, valor)) {
                realizarSaque(cpf, valor);
            } else {
                std::cout << "Número inválido para saque!" << std::endl;
            }

        } else if (opcao == "7") {
            std::cout << "Encerrando o sistema. Até mais!" << std::endl;
            break;

        } else {
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    }

    return 0;
}
