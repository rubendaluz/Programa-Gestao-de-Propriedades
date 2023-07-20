#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_CT 20
#define ID 10000

class Cultura {
public:
    Cultura(const std::string& name, const std::string& description, float area)
        : nome(name), descricao(description), area_cultivo(area) {}

    std::string nome;
    std::string descricao;
    float area_cultivo;
};

class PropAvaliada {
public:
    PropAvaliada(float value, const std::string& evaluator)
        : valAvaliacao(value), avaliador(evaluator) {}

    float valAvaliacao;
    std::string avaliador;
};

class Propriedade {
public:
    Propriedade(const std::string& owner, int number, int identifier, const std::string& desc, float area)
        : nome_proprietario(owner), numero(number), identificador(identifier), descricao(desc), area(area),
          numCulturas(0), estado("para avaliar") {}

    void addCultura(const Cultura& cultura) {
        if (numCulturas < MAX_CT) {
            culturas.push_back(cultura);
            numCulturas++;
        }
    }

    std::string nome_proprietario;
    int numero;
    int identificador;
    std::string descricao;
    float area;
    std::vector<Cultura> culturas;
    int numCulturas;
    std::string estado;
    PropAvaliada propAvaliada;
};

class QueuePropriedades {
public:
    void adicionarPropriedade(const Propriedade& propriedade) {
        fila.push_back(propriedade);
    }

    void listarPropriedades() const {
        std::cout << "/-------------- FILA PROPRIEDADES PARA AVALIAR -------------/" << std::endl;
        if (fila.empty()) {
            std::cout << "A fila esta vazia" << std::endl;
        } else {
            headerListaPropsAvaliar(std::cout);
            for (const auto& prop : fila) {
                std::cout << "\t|" << prop.numero << "\t|" << prop.nome_proprietario << "\t|" << prop.identificador << "\t|" << std::endl;
            }
            footerListaPropsAvaliar(std::cout);
        }
    }

private:
    static void headerListaPropsAvaliar(std::ostream& out) {
        out << "\t+---+--------------------+--------------+" << std::endl;
        out << "\t|Num|Proprietario        |Identificador |" << std::endl;
        out << "\t+---+--------------------+--------------+" << std::endl;
    }

    static void footerListaPropsAvaliar(std::ostream& out) {
        out << "\t+---+--------------------+--------------+" << std::endl;
    }

    std::vector<Propriedade> fila;
};

class Utilizador {
public:
    Utilizador(const std::string& name, const std::string& username, const std::string& password, char type)
        : nome(name), username(username), password(password), tipo(type) {}

    std::string nome;
    std::string username;
    std::string password;
    char tipo; // a/A->administrador e e/E->(evaluator)avaliador
};

class GerenciadorUtilizadores {
public:
    GerenciadorUtilizadores() {
        carregarUtilizadores();
    }

    void inserirUtilizador(const Utilizador& utilizador) {
        utilizadores.push_back(utilizador);
        salvarUtilizadores();
    }

    void listarUtilizadores() const {
        std::cout << "/------------- LISTA DE UTILIZADORES -----------/" << std::endl;
        if (utilizadores.empty()) {
            std::cout << "Lista vazia" << std::endl;
        } else {
            std::cout << "\n\tUsername\t\tTipo" << std::endl;
            for (const auto& user : utilizadores) {
                std::cout << "\t" << user.username << "\t\t" << (user.tipo == 'a' ? "Administrador" : "Avaliador") << std::endl;
            }
        }
    }

private:
    void carregarUtilizadores() {
        std::ifstream fin("Dados_Utilizadores.dat", std::ios::binary);
        if (!fin) {
            std::cout << "Erro na abertura do ficheiro que guarda os dados dos utilizadores!!!" << std::endl;
            return;
        }

        Utilizador user;
        while (fin.read(reinterpret_cast<char*>(&user), sizeof(Utilizador))) {
            utilizadores.push_back(user);
        }
    }

    void salvarUtilizadores() const {
        std::ofstream fout("Dados_Utilizadores.dat", std::ios::binary);
        if (!fout) {
            std::cout << "Erro na abertura do ficheiro para guardar os dados dos utilizadores!!!" << std::endl;
            return;
        }

        for (const auto& user : utilizadores) {
            fout.write(reinterpret_cast<const char*>(&user), sizeof(Utilizador));
        }
    }

    std::vector<Utilizador> utilizadores;
};

class Menu {
public:
    Menu(GerenciadorUtilizadores& userManager, QueuePropriedades& propertyQueue)
        : gerenciadorUtilizadores(userManager), queuePropriedades(propertyQueue) {}

    void mostrarMenu() {
        int escolha;
        char tipo_utilizador;
        do {
            std::cout << "\n/------------- MENU ------------/" << std::endl;
            std::cout << "1 - Inserir Utilizador" << std::endl;
            std::cout << "2 - Listar Utilizadores" << std::endl;
            std::cout << "3 - Adicionar Propriedade na fila para avaliar" << std::endl;
            std::cout << "4 - Listar Propriedades na fila para avaliar" << std::endl;
            std::cout << "5 - Sair" << std::endl;
            std::cout << "Escolha: ";
            std::cin >> escolha;

            switch (escolha) {
                case 1:
                    inserirUtilizador();
                    break;
                case 2:
                    listarUtilizadores();
                    break;
                case 3:
                    adicionarPropriedadeParaAvaliar();
                    break;
                case 4:
                    listarPropriedadesParaAvaliar();
                    break;
                case 5:
                    std::cout << "A sair..." << std::endl;
                    break;
                default:
                    std::cout << "Escolha invalida! Tente novamente." << std::endl;
            }
        } while (escolha != 5);
    }

private:
    void inserirUtilizador() {
        std::string nome, username, password;
        char tipo;
        std::cout << "\n/---------- INSERIR UTILIZADOR ----------/" << std::endl;
        std::cout << "Nome: ";
        std::cin.ignore();
        std::getline(std::cin, nome);

        std::cout << "Username: ";
        std::getline(std::cin, username);

        std::cout << "Password: ";
        std::getline(std::cin, password);

        do {
            std::cout << "Tipo (a/A para administrador ou e/E para avaliador): ";
            std::cin >> tipo;
            tipo = std::tolower(tipo);
        } while (tipo != 'a' && tipo != 'e');

        Utilizador user(nome, username, password, tipo);
        gerenciadorUtilizadores.inserirUtilizador(user);
    }

    void listarUtilizadores() {
        gerenciadorUtilizadores.listarUtilizadores();
    }

    void adicionarPropriedadeParaAvaliar() {
        std::string owner, desc;
        float area;
        std::cout << "\n/---------- ADICIONAR PROPRIEDADE PARA AVALIAR ----------/" << std::endl;
        std::cout << "Nome do Proprietario: ";
        std::cin.ignore();
        std::getline(std::cin, owner);

        std::cout << "Descricao: ";
        std::getline(std::cin, desc);

        std::cout << "Area: ";
        std::cin >> area;

        Propriedade prop(owner, ID++, ID, desc, area);
        queuePropriedades.adicionarPropriedade(prop);
    }

    void listarPropriedadesParaAvaliar() {
        queuePropriedades.listarPropriedades();
    }

    GerenciadorUtilizadores& gerenciadorUtilizadores;
    QueuePropriedades& queuePropriedades;
};

int main() {
    QueuePropriedades queuePropriedades;
    GerenciadorUtilizadores gerenciadorUtilizadores;
    Menu menu(gerenciadorUtilizadores, queuePropriedades);
    menu.mostrarMenu();
    return 0;
}
