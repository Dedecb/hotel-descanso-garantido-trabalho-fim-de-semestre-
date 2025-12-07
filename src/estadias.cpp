#include "estadias.hpp"
#include "clientes.hpp"
#include "quartos.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

static int nextCodigoEstadia() {
    ifstream fin(ESTADIAS_FILE, ios::binary);
    if (!fin) return 1;
    Estadia e;
    int maxc = 0;
    while (fin.read(reinterpret_cast<char*>(&e), sizeof(Estadia))) {
        if (e.codigoEstadia > maxc) maxc = e.codigoEstadia;
    }
    fin.close();
    return maxc + 1;
}

int gerarCodigoEstadia() {
    return nextCodigoEstadia();
}

long dataParaDias(const Data &d) {
    // converte data para número contínuo de dias usando algoritmo de contagem de dias (Rata Die simplificado)
    int a = (14 - d.mes) / 12;
    int y = d.ano + 4800 - a;
    int m = d.mes + 12*a - 3;
    long jd = d.dia + (153*m + 2)/5 + 365*y + y/4 - y/100 + y/400 - 32045;
    return jd;
}

int calcularDiarias(const Data &entrada, const Data &saida) {
    long e = dataParaDias(entrada);
    long s = dataParaDias(saida);
    int diff = static_cast<int>(s - e);
    if (diff < 0) return -1;
    return diff; // cada diferença de dia é uma diaria
}

bool datasSobrepoem(const Data &s1, const Data &e1, const Data &s2, const Data &e2) {
    // overlap if start1 < end2 and start2 < end1 (assume end is exclusive? aqui consideramos inclusive saída -> hotel: saída no dia significa não ocupar a noite daquele dia)
    // Para o enunciado: as diárias iniciam 14h e findam às 12h do dia seguinte.
    // Usaremos a convenção: intervalo [entrada, saida) => não inclui o dia de saida como noite.
    long S1 = dataParaDias(s1);
    long E1 = dataParaDias(e1);
    long S2 = dataParaDias(s2);
    long E2 = dataParaDias(e2);
    return (S1 < E2) && (S2 < E1);
}

bool cadastrarEstadia(const Estadia &e) {
    // antes de cadastrar, regras:
    // - cliente existe
    Cliente ctmp;
    if (!existeClienteCodigo(e.codigoCliente, ctmp)) return false;
    // - tem quarto com numero e capacidade >= hóspedes e status desocupado e sem sobreposicao
    Quarto qtmp;
    if (!existeQuartoNumero(e.numeroQuarto, qtmp)) return false;
    if (qtmp.capacidade < e.quantidadeHospedes) return false;
    if (qtmp.status != 'D') return false;

    // checar se existe outra estadia ativa para mesmo quarto com sobreposição de datas
    ifstream fin(ESTADIAS_FILE, ios::binary);
    Estadia f;
    if (fin) {
        while (fin.read(reinterpret_cast<char*>(&f), sizeof(Estadia))) {
            if (!f.active) continue;
            if (f.numeroQuarto == e.numeroQuarto) {
                if (datasSobrepoem(f.dataEntrada, f.dataSaida, e.dataEntrada, e.dataSaida)) {
                    fin.close();
                    return false;
                }
            }
        }
        fin.close();
    }

    // grava nova estadia e marca quarto como ocupado
    ofstream fout(ESTADIAS_FILE, ios::binary | ios::app);
    if (!fout) return false;
    fout.write(reinterpret_cast<const char*>(&e), sizeof(Estadia));
    fout.close();

    // Atualiza status do quarto para ocupado
    atualizarStatusQuarto(e.numeroQuarto, 'O');
    return true;
}

vector<Estadia> listarTodasEstadias() {
    vector<Estadia> res;
    ifstream fin(ESTADIAS_FILE, ios::binary);
    if (!fin) return res;
    Estadia e;
    while (fin.read(reinterpret_cast<char*>(&e), sizeof(Estadia))) {
        res.push_back(e);
    }
    fin.close();
    return res;
}

bool existeEstadiaCodigo(int codigo, Estadia &out) {
    ifstream fin(ESTADIAS_FILE, ios::binary);
    if (!fin) return false;
    Estadia e;
    while (fin.read(reinterpret_cast<char*>(&e), sizeof(Estadia))) {
        if (e.codigoEstadia == codigo) {
            out = e;
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

vector<Estadia> listarEstadiasPorCliente(int codigoCliente) {
    vector<Estadia> res;
    ifstream fin(ESTADIAS_FILE, ios::binary);
    if (!fin) return res;
    Estadia e;
    while (fin.read(reinterpret_cast<char*>(&e), sizeof(Estadia))) {
        if (e.codigoCliente == codigoCliente) res.push_back(e);
    }
    fin.close();
    return res;
}

bool darBaixaEstadia(int codigoEstadia, double &valorTotal) {
    fstream f(ESTADIAS_FILE, ios::in | ios::out | ios::binary);
    if (!f) return false;
    Estadia e;
    while (f.read(reinterpret_cast<char*>(&e), sizeof(Estadia))) {
        if (e.codigoEstadia == codigoEstadia) {
            if (!e.active) { f.close(); return false; } // já dada baixa
            // calcula valor: numero de diarias * valor diaria do quarto
            Quarto q;
            if (!existeQuartoNumero(e.numeroQuarto, q)) { f.close(); return false; }
            int diarias = calcularDiarias(e.dataEntrada, e.dataSaida);
            valorTotal = diarias * q.valorDiaria;
            // marcar estadia como inactive
            e.active = false;
            f.seekp(-static_cast<int>(sizeof(Estadia)), ios::cur);
            f.write(reinterpret_cast<const char*>(&e), sizeof(Estadia));
            f.close();
            // liberar quarto
            atualizarStatusQuarto(e.numeroQuarto, 'D');
            return true;
        }
    }
    f.close();
    return false;
}
