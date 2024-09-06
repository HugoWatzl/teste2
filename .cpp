#include <iostream>
#include <unordered_map>
#include <string>

class ContaBancaria {
private:
    std::string cpf;
    std::string nome;
    std::string endereco;
    std::string telefone;
    double saldo;

public:
    ContaBancaria(const std::string& cpf, const std::string& nome, const std::string& endereco, const std::string& telefone)
        : cpf(cpf), nome(nome), endereco(endereco), telefone(telefone), saldo(0.0) {}

    std::string getCpf() const { return cpf; }
    std::string getNome() const { return nome; }
    std::string getEndereco() const { return endereco; }
    std::string getTelefone() const { return telefone; }
    double getSaldo() const { return saldo; }

    void setNome(const std::string& novoNome) { nome = novoNome; }
    void setEndereco(const std::string& novoEndereco) { endereco = novoEndereco; }
    void setTelefone(const std::string& novoTelefone) { telefone = novoTelefone; }

    void depositar(double valor) {
        if (valor > 0) saldo += valor;
        else std::cout << "Valor de depósito inválido!" << std::endl;
    }

    bool sacar(double valor) {
        if (valor > 0 && valor <= saldo) {
            saldo -= valor;
            return true;
        }
        std::cout << "Saldo insuficiente ou valor inválido!" << std::endl;
        return false;
    }

    void mostrarSaldo() const {
        std::cout << "Saldo: R$ " << saldo << std::endl;
    }
};

class GerenciadorDeContas {
private:
    std::unordered_map<std::string, ContaBancaria> contas;

public:
    void criarConta(const std::string& cpf, const std::string& nome, const std::string& endereco, const std::string& telefone) {
        if (contas.find(cpf) == contas.end()) {
            contas.emplace(cpf, ContaBancaria(cpf, nome, endereco, telefone));
            std::cout << "Conta criada com sucesso!" << std::endl;
        } else {
            std::cout << "Conta já existente com esse CPF!" << std::endl;
        }
    }

    void consultarConta(const std::string& cpf) const {
        auto it = contas.find(cpf);
        if (it != contas.end()) {
            const ContaBancaria& conta = it->second;
            std::cout << "Nome: " << conta.getNome() << std::endl;
            std::cout << "Endereço: " << conta.getEndereco() << std::endl;
            std::cout << "Telefone: " << conta.getTelefone() << std::endl;
            conta.mostrarSaldo();
        } else {
            std::cout << "Conta não encontrada!" << std::endl;
        }
    }

    void removerConta(const std::string& cpf) {
        if (contas.erase(cpf)) {
            std::cout << "Conta removida com sucesso!" << std::endl;
        } else {
            std::cout << "Conta não encontrada!" << std::endl;
        }
    }

    void editarConta(const std::string& cpf, const std::string& nome, const std::string& endereco, const std::string& telefone) {
        auto it = contas.find(cpf);
        if (it != contas.end()) {
            ContaBancaria& conta = it->second;
            conta.setNome(nome);
            conta.setEndereco(endereco);
            conta.setTelefone(telefone);
            std::cout << "Informações da conta atualizadas com sucesso!" << std::endl;
        } else {
            std::cout << "Conta não encontrada!" << std::endl;
        }
    }

    void realizarDeposito(const std::string& cpf, double valor) {
        auto it = contas.find(cpf);
        if (it != contas.end()) {
            it->second.depositar(valor);
        } else {
            std::cout << "Conta não encontrada!" << std::endl;
        }
    }

    void realizarSaque(const std::string& cpf, double valor) {
        auto it = contas.find(cpf);
        if (it != contas.end()) {
            it->second.sacar(valor);
        } else {
            std::cout << "Conta não encontrada!" << std::endl;
        }
    }
};

int main() {
    GerenciadorDeContas gerenciador;
    std::string opcao, cpf, nome, endereco, telefone;
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
            gerenciador.criarConta(cpf, nome, endereco, telefone);

        } else if (opcao == "2") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            gerenciador.consultarConta(cpf);

        } else if (opcao == "3") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            gerenciador.removerConta(cpf);

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
            gerenciador.editarConta(cpf, nome, endereco, telefone);

        } else if (opcao == "5") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            std::cout << "Digite Valor para Depósito: ";
            std::cin >> valor;
            gerenciador.realizarDeposito(cpf, valor);

        } else if (opcao == "6") {
            std::cout << "Digite CPF: ";
            std::cin >> cpf;
            std::cout << "Digite Valor para Saque: ";
            std::cin >> valor;
            gerenciador.realizarSaque(cpf, valor);

        } else if (opcao == "7") {
            std::cout << "Encerrando o sistema. Até mais!" << std::endl;
            break;

        } else {
            std::cout << "Opção inválida.Escolha numeros de 1-7!" << std::endl;
        }
    }

    return 0;
}
