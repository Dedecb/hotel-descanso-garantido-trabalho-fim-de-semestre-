#ifndef ESTADIAS_H
#define ESTADIAS_H

#include <cstring>
#include <vector>
#include "clientes.hpp"
#include "quartos.hpp"

const char ESTADIAS_FILE[] = "estadias.dat";

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Estadia {
    int codigoEstadia;
    Data dataEntrada;
    Data dataSaida;
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
    int quantidadeHospedes;
    bool active; // true enquanto ativos (não deram baixa)
};

int gerarCodigoEstadia();
bool cadastrarEstadia(const Estadia &e);
bool darBaixaEstadia(int codigoEstadia, double &valorTotal);
std::vector<Estadia> listarTodasEstadias();
std::vector<Estadia> listarEstadiasPorCliente(int codigoCliente);
bool existeEstadiaCodigo(int codigo, Estadia &out);

// funções utilitárias de data
long dataParaDias(const Data &d);
int calcularDiarias(const Data &entrada, const Data &saida);
bool datasSobrepoem(const Data &s1, const Data &e1, const Data &s2, const Data &e2);

#endif // ESTADIAS_H
