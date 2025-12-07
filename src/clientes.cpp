#include "clientes.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

static int nextCodigoCliente() {
    // tenta ler último código no arquivo
    ifstream fin(CLIENTES_FILE, ios::binary);
    if (!fin) return 1;
    Cliente c;
    int maxc = 0;
    while (fin.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
        if (c.codigo > maxc) maxc = c.codigo;
    }
    fin.close();
    return maxc + 1;
}

int gerarCodigoCliente() {
    return nextCodigoCliente();
}

bool cadastrarCliente(const Cliente &c) {
    // valida duplicidade de codigo
    Cliente temp;
    ifstream fin(CLIENTES_FILE, ios::binary);
    if (fin) {
        while (fin.read(reinterpret_cast<char*>(&temp), sizeof(Cliente))) {
            if (temp.codigo == c.codigo) {
                fin.close();
                return false;
            }
        }
        fin.close();
    }
    ofstream fout(CLIENTES_FILE, ios::binary | ios::app);
    if (!fout) return false;
    fout.write(reinterpret_cast<const char*>(&c), sizeof(Cliente));
    fout.close();
    return true;
}

bool existeClienteCodigo(int codigo, Cliente &out) {
    ifstream fin(CLIENTES_FILE, ios::binary);
    if (!fin) return false;
    Cliente c;
    while (fin.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
        if (c.codigo == codigo) {
            out = c;
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool existeClienteNome(const std::string &nome, std::vector<Cliente> &outMatches) {
    outMatches.clear();
    ifstream fin(CLIENTES_FILE, ios::binary);
    if (!fin) return false;
    Cliente c;
    std::string lowerName = nome;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    while (fin.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
        std::string stored = c.nome;
        std::string storedLow = stored;
        transform(storedLow.begin(), storedLow.end(), storedLow.begin(), ::tolower);
        if (storedLow.find(lowerName) != std::string::npos) {
            outMatches.push_back(c);
        }
    }
    fin.close();
    return !outMatches.empty();
}

vector<Cliente> listarTodosClientes() {
    vector<Cliente> res;
    ifstream fin(CLIENTES_FILE, ios::binary);
    if (!fin) return res;
    Cliente c;
    while (fin.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
        res.push_back(c);
    }
    fin.close();
    return res;
}

void imprimirCliente(const Cliente &c) {
    cout << "Codigo: " << c.codigo << "\n";
    cout << "Nome: " << c.nome << "\n";
    cout << "Endereco: " << c.endereco << "\n";
    cout << "Telefone: " << c.telefone << "\n";
    cout << "---------------------------\n";
}
