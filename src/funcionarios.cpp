#include "funcionarios.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

static int nextCodigoFuncionario() {
    ifstream fin(FUNCIONARIOS_FILE, ios::binary);
    if (!fin) return 1;
    Funcionario f;
    int maxc = 0;
    while (fin.read(reinterpret_cast<char*>(&f), sizeof(Funcionario))) {
        if (f.codigo > maxc) maxc = f.codigo;
    }
    fin.close();
    return maxc + 1;
}

int gerarCodigoFuncionario() {
    return nextCodigoFuncionario();
}

bool cadastrarFuncionario(const Funcionario &f) {
    Funcionario tmp;
    ifstream fin(FUNCIONARIOS_FILE, ios::binary);
    if (fin) {
        while (fin.read(reinterpret_cast<char*>(&tmp), sizeof(Funcionario))) {
            if (tmp.codigo == f.codigo) {
                fin.close();
                return false;
            }
        }
        fin.close();
    }
    ofstream fout(FUNCIONARIOS_FILE, ios::binary | ios::app);
    if (!fout) return false;
    fout.write(reinterpret_cast<const char*>(&f), sizeof(Funcionario));
    fout.close();
    return true;
}

bool existeFuncionarioCodigo(int codigo, Funcionario &out) {
    ifstream fin(FUNCIONARIOS_FILE, ios::binary);
    if (!fin) return false;
    Funcionario f;
    while (fin.read(reinterpret_cast<char*>(&f), sizeof(Funcionario))) {
        if (f.codigo == codigo) {
            out = f;
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool existeFuncionarioNome(const std::string &nome, std::vector<Funcionario> &outMatches) {
    outMatches.clear();
    ifstream fin(FUNCIONARIOS_FILE, ios::binary);
    if (!fin) return false;
    Funcionario f;
    std::string lowerName = nome;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    while (fin.read(reinterpret_cast<char*>(&f), sizeof(Funcionario))) {
        std::string stored = f.nome;
        std::string storedLow = stored;
        transform(storedLow.begin(), storedLow.end(), storedLow.begin(), ::tolower);
        if (storedLow.find(lowerName) != std::string::npos) {
            outMatches.push_back(f);
        }
    }
    fin.close();
    return !outMatches.empty();
}

vector<Funcionario> listarTodosFuncionarios() {
    vector<Funcionario> res;
    ifstream fin(FUNCIONARIOS_FILE, ios::binary);
    if (!fin) return res;
    Funcionario f;
    while (fin.read(reinterpret_cast<char*>(&f), sizeof(Funcionario))) {
        res.push_back(f);
    }
    fin.close();
    return res;
}

void imprimirFuncionario(const Funcionario &f) {
    cout << "Codigo: " << f.codigo << "\n";
    cout << "Nome: " << f.nome << "\n";
    cout << "Telefone: " << f.telefone << "\n";
    cout << "Cargo: " << f.cargo << "\n";
    cout << "Salario: " << f.salario << "\n";
    cout << "---------------------------\n";
}
