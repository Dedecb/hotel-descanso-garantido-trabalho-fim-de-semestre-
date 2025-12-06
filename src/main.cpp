#include <iostream>
#include <limits>
#include <vector>
#include <cstring>
#include "clientes.h"
#include "funcionarios.h"
#include "quartos.h"
#include "estadias.h"

using namespace std;

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Data lerData() {
    Data d;
    cout << "Dia: "; cin >> d.dia;
    cout << "Mes: "; cin >> d.mes;
    cout << "Ano: "; cin >> d.ano;
    limparEntrada();
    return d;
}

void opcCadastrarCliente() {
    Cliente c;
    c.codigo = gerarCodigoCliente();
    cout << "Gerando codigo: " << c.codigo << "\n";
    cout << "Nome: ";
    string nome; getline(cin, nome);
    strncpy(c.nome, nome.c_str(), MAX_NOME);
    c.nome[MAX_NOME-1]=0;
    cout << "Endereco: ";
    string end; getline(cin,end);
    strncpy(c.endereco, end.c_str(), MAX_END);
    c.endereco[MAX_END-1]=0;
    cout << "Telefone: ";
    string tel; getline(cin,tel);
    strncpy(c.telefone, tel.c_str(), MAX_TEL);
    c.telefone[MAX_TEL-1]=0;
    c.active = true;
    if (cadastrarCliente(c)) cout << "Cliente cadastrado.\n";
    else cout << "Falha ao cadastrar (codigo existente?).\n";
}

void opcCadastrarFuncionario() {
    Funcionario f;
    f.codigo = gerarCodigoFuncionario();
    cout << "Gerando codigo: " << f.codigo << "\n";
    cout << "Nome: ";
    string nome; getline(cin, nome);
    strncpy(f.nome, nome.c_str(), MAX_NOME_FUNC); f.nome[MAX_NOME_FUNC-1]=0;
    cout << "Telefone: "; string tel; getline(cin,tel);
    strncpy(f.telefone, tel.c_str(), MAX_TEL_FUNC); f.telefone[MAX_TEL_FUNC-1]=0;
    cout << "Cargo: "; string cargo; getline(cin,cargo);
    strncpy(f.cargo, cargo.c_str(), MAX_CARGO); f.cargo[MAX_CARGO-1]=0;
    cout << "Salario: "; cin >> f.salario; limparEntrada();
    f.active = true;
    if (cadastrarFuncionario(f)) cout << "Funcionario cadastrado.\n"; else cout << "Erro ao cadastrar.\n";
}

void opcCadastrarQuarto() {
    Quarto q;
    cout << "Numero do quarto: "; cin >> q.numero;
    cout << "Capacidade: "; cin >> q.capacidade;
    cout << "Valor diaria: "; cin >> q.valorDiaria;
    limparEntrada();
    q.status = 'D';
    if (cadastrarQuarto(q)) cout << "Quarto cadastrado.\n"; else cout << "Numero ja existente.\n";
}

void opcCadastrarEstadia() {
    Estadia e;
    e.codigoEstadia = gerarCodigoEstadia();
    cout << "Codigo gerado: " << e.codigoEstadia << "\n";
    cout << "Codigo do cliente: "; cin >> e.codigoCliente;
    cout << "Quantidade de hospedes: "; cin >> e.quantidadeHospedes;
    cout << "Data de entrada:\n"; e.dataEntrada = lerData();
    cout << "Data de saida:\n"; e.dataSaida = lerData();
    limparEntrada();
    e.quantidadeDiarias = calcularDiarias(e.dataEntrada, e.dataSaida);
    if (e.quantidadeDiarias <= 0) { cout << "Datas invalidas (saida antes da entrada ou mesmas datas).\n"; return; }
    // procurar quarto disponível com capacidade adequada
    vector<Quarto> quartos = listarTodosQuartos();
    bool achou = false;
    for (auto &q: quartos) {
        if (q.capacidade >= e.quantidadeHospedes && q.status == 'D') {
            // verificar sobreposicao com estadias existentes
            bool conflict = false;
            vector<Estadia> todas = listarTodasEstadias();
            for (auto &ex: todas) {
                if (!ex.active) continue;
                if (ex.numeroQuarto == q.numero) {
                    if (datasSobrepoem(ex.dataEntrada, ex.dataSaida, e.dataEntrada, e.dataSaida)) {
                        conflict = true; break;
                    }
                }
            }
            if (!conflict) {
                e.numeroQuarto = q.numero;
                e.active = true;
                if (cadastrarEstadia(e)) {
                    cout << "Estadia cadastrada. Quarto atribuido: " << q.numero << "\n";
                    cout << "Quantidade diarias: " << e.quantidadeDiarias << "\n";
                } else {
                    cout << "Falha ao cadastrar estadia.\n";
                }
                achou = true;
                break;
            }
        }
    }
    if (!achou) cout << "Nenhum quarto disponível para os requisitos.\n";
}

void opcDarBaixa() {
    cout << "Codigo da estadia para dar baixa: ";
    int cod; cin >> cod; limparEntrada();
    double valor;
    if (darBaixaEstadia(cod, valor)) {
        cout << "Baixa realizada. Valor total: " << valor << "\n";
    } else {
        cout << "Falha ao dar baixa (codigo inexistente ou ja deu baixa).\n";
    }
}

void opcPesquisarCliente() {
    cout << "Pesquisar por (1) codigo (2) nome: ";
    int op; cin >> op; limparEntrada();
    if (op == 1) {
        int cod; cout << "Codigo: "; cin >> cod; limparEntrada();
        Cliente c;
        if (existeClienteCodigo(cod, c)) imprimirCliente(c); else cout << "Nao encontrado.\n";
    } else {
        cout << "Nome (ou parte): ";
        string nome; getline(cin, nome);
        vector<Cliente> res;
        if (existeClienteNome(nome, res)) {
            for (auto &c : res) imprimirCliente(c);
        } else cout << "Nao encontrado.\n";
    }
}

void opcPesquisarFuncionario() {
    cout << "Pesquisar por (1) codigo (2) nome: ";
    int op; cin >> op; limparEntrada();
    if (op == 1) {
        int cod; cout << "Codigo: "; cin >> cod; limparEntrada();
        Funcionario f;
        if (existeFuncionarioCodigo(cod, f)) imprimirFuncionario(f); else cout << "Nao encontrado.\n";
    } else {
        cout << "Nome (ou parte): ";
        string nome; getline(cin, nome);
        vector<Funcionario> res;
        if (existeFuncionarioNome(nome, res)) {
            for (auto &c : res) imprimirFuncionario(c);
        } else cout << "Nao encontrado.\n";
    }
}

void opcListarEstadiasCliente() {
    cout << "Pesquisar por cliente (1) codigo (2) nome: ";
    int op; cin >> op; limparEntrada();
    int cod = -1;
    if (op == 1) {
        cout << "Codigo: "; cin >> cod; limparEntrada();
    } else {
        string nome; cout << "Nome (ou parte): "; getline(cin, nome);
        vector<Cliente> res;
        if (existeClienteNome(nome, res)) {
            if (res.size() == 1) cod = res[0].codigo;
            else {
                cout << "Resultados:\n";
                for (auto &c: res) imprimirCliente(c);
                cout << "Digite codigo desejado: "; cin >> cod; limparEntrada();
            }
        } else { cout << "Nenhum cliente.\n"; return; }
    }
    vector<Estadia> ests = listarEstadiasPorCliente(cod);
    if (ests.empty()) { cout << "Nenhuma estadia para esse cliente.\n"; return; }
    for (auto &e: ests) {
        cout << "Codigo estadia: " << e.codigoEstadia << "\n";
        cout << "Quarto: " << e.numeroQuarto << "\n";
        cout << "Data entrada: " << e.dataEntrada.dia << "/" << e.dataEntrada.mes << "/" << e.dataEntrada.ano << "\n";
        cout << "Data saida: " << e.dataSaida.dia << "/" << e.dataSaida.mes << "/" << e.dataSaida.ano << "\n";
        cout << "Diarias: " << e.quantidadeDiarias << "\n";
        cout << "Ativa: " << (e.active ? "Sim" : "Nao") << "\n";
        cout << "-----------------------------\n";
    }
}

void opcCalcularPontos() {
    cout << "Calcular pontos de fidelidade para cliente (1) codigo (2) nome: ";
    int op; cin >> op; limparEntrada();
    int cod = -1;
    if (op == 1) {
        cout << "Codigo: "; cin >> cod; limparEntrada();
    } else {
        string nome; cout << "Nome (ou parte): "; getline(cin, nome);
        vector<Cliente> res;
        if (existeClienteNome(nome, res)) {
            if (res.size() == 1) cod = res[0].codigo;
            else {
                cout << "Resultados:\n";
                for (auto &c: res) imprimirCliente(c);
                cout << "Digite codigo desejado: "; cin >> cod; limparEntrada();
            }
        } else { cout << "Nenhum cliente.\n"; return; }
    }
    vector<Estadia> ests = listarEstadiasPorCliente(cod);
    int somaDiarias = 0;
    for (auto &e: ests) somaDiarias += e.quantidadeDiarias;
    int pontos = somaDiarias * 10;
    cout << "Total de diarias acumuladas: " << somaDiarias << "\n";
    cout << "Pontos de fidelidade: " << pontos << "\n";
}

void mostrarMenu() {
    cout << "\n--- Hotel Descanso Garantido ---\n";
    cout << "1. Cadastrar cliente\n";
    cout << "2. Cadastrar funcionario\n";
    cout << "3. Cadastrar quarto\n";
    cout << "4. Cadastrar estadia\n";
    cout << "5. Dar baixa em estadia\n";
    cout << "6. Pesquisar cliente\n";
    cout << "7. Pesquisar funcionario\n";
    cout << "8. Mostrar estadias de um cliente\n";
    cout << "9. Calcular pontos fidelidade\n";
    cout << "10. Listar todos quartos\n";
    cout << "0. Sair\n";
    cout << "Escolha: ";
}

int main() {
    int opc;
    do {
        mostrarMenu();
        cin >> opc; limparEntrada();
        switch(opc) {
            case 1: opcCadastrarCliente(); break;
            case 2: opcCadastrarFuncionario(); break;
            case 3: opcCadastrarQuarto(); break;
            case 4: opcCadastrarEstadia(); break;
            case 5: opcDarBaixa(); break;
            case 6: opcPesquisarCliente(); break;
            case 7: opcPesquisarFuncionario(); break;
            case 8: opcListarEstadiasCliente(); break;
            case 9: opcCalcularPontos(); break;
            case 10: {
                auto quartos = listarTodosQuartos();
                for (auto &q: quartos) imprimirQuarto(q);
            } break;
            case 0: cout << "Saindo...\n"; break;
            default: cout << "Opcao invalida.\n";
        }
    } while (opc != 0);
    return 0;
}
