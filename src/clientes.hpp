#ifndef CLIENTES_H
#define CLIENTES_H

#include <cstring>
#include <string>
#include <vector>

const char CLIENTES_FILE[] = "data/clientes.dat";
const int MAX_NOME = 100;
const int MAX_END = 150;
const int MAX_TEL = 30;

struct Cliente {
    int codigo;
    char nome[MAX_NOME];
    char endereco[MAX_END];
    char telefone[MAX_TEL];
    bool active; // para marcar exclusão se precisar
};

bool cadastrarCliente(const Cliente &c);
bool existeClienteCodigo(int codigo, Cliente &out);
bool existeClienteNome(const std::string &nome, std::vector<Cliente> &outMatches);
std::vector<Cliente> listarTodosClientes();
void imprimirCliente(const Cliente &c);

int gerarCodigoCliente();

#endif // CLIENTES_H
