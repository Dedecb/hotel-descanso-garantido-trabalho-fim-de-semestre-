#ifndef QUARTOS_H
#define QUARTOS_H

#include <cstring>
#include <vector>

const char QUARTOS_FILE[] = "quartos.dat";
const int MAX_STATUS = 2; // 'D' desocupado, 'O' ocupado

struct Quarto {
    int numero;
    int capacidade;
    double valorDiaria;
    char status; // 'D' ou 'O'
};

bool cadastrarQuarto(const Quarto &q);
bool existeQuartoNumero(int numero, Quarto &out);
bool atualizarStatusQuarto(int numero, char newStatus);
std::vector<Quarto> listarTodosQuartos();
void imprimirQuarto(const Quarto &q);

#endif // QUARTOS_H
