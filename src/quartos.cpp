#include "quartos.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool cadastrarQuarto(const Quarto &q) {
    Quarto tmp;
    ifstream fin(QUARTOS_FILE, ios::binary);
    if (fin) {
        while (fin.read(reinterpret_cast<char*>(&tmp), sizeof(Quarto))) {
            if (tmp.numero == q.numero) {
                fin.close();
                return false;
            }
        }
        fin.close();
    }
    ofstream fout(QUARTOS_FILE, ios::binary | ios::app);
    if (!fout) return false;
    fout.write(reinterpret_cast<const char*>(&q), sizeof(Quarto));
    fout.close();
    return true;
}

bool existeQuartoNumero(int numero, Quarto &out) {
    ifstream fin(QUARTOS_FILE, ios::binary);
    if (!fin) return false;
    Quarto q;
    while (fin.read(reinterpret_cast<char*>(&q), sizeof(Quarto))) {
        if (q.numero == numero) {
            out = q;
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool atualizarStatusQuarto(int numero, char newStatus) {
    fstream f(QUARTOS_FILE, ios::in | ios::out | ios::binary);
    if (!f) return false;
    Quarto q;
    while (f.read(reinterpret_cast<char*>(&q), sizeof(Quarto))) {
        if (q.numero == numero) {
            q.status = newStatus;
            f.seekp(-static_cast<int>(sizeof(Quarto)), ios::cur);
            f.write(reinterpret_cast<const char*>(&q), sizeof(Quarto));
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

vector<Quarto> listarTodosQuartos() {
    vector<Quarto> res;
    ifstream fin(QUARTOS_FILE, ios::binary);
    if (!fin) return res;
    Quarto q;
    while (fin.read(reinterpret_cast<char*>(&q), sizeof(Quarto))) {
        res.push_back(q);
    }
    fin.close();
    return res;
}

void imprimirQuarto(const Quarto &q) {
    cout << "Numero: " << q.numero << "\n";
    cout << "Capacidade: " << q.capacidade << "\n";
    cout << "Valor diaria: " << q.valorDiaria << "\n";
    cout << "Status: " << (q.status == 'D' ? "Desocupado" : "Ocupado") << "\n";
    cout << "---------------------------\n";
}
