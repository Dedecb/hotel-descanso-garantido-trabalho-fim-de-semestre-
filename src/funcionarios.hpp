#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <cstring>
#include <string>
#include <vector>

const char FUNCIONARIOS_FILE[] = "funcionarios.bin";
const int MAX_NOME_FUNC = 100;
const int MAX_TEL_FUNC = 30;
const int MAX_CARGO = 50;

struct Funcionario {
    int codigo;
    char nome[MAX_NOME_FUNC];
    char telefone[MAX_TEL_FUNC];
    char cargo[MAX_CARGO];
    double salario;
    bool active;
};

bool cadastrarFuncionario(const Funcionario &f);
bool existeFuncionarioCodigo(int codigo, Funcionario &out);
bool existeFuncionarioNome(const std::string &nome, std::vector<Funcionario> &outMatches);
std::vector<Funcionario> listarTodosFuncionarios();
void imprimirFuncionario(const Funcionario &f);

int gerarCodigoFuncionario();

#endif // FUNCIONARIOS_H
