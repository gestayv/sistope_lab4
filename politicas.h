#ifndef POLITICAS_H
#define POLITCAS_H

#include "lista.h"

//  Variable global donde se almacena la tasa de miss del
//  óptimo para luego poder realizar la comparación.
float missOptimo;

//  Variable global donde se almacena el número de marcos
//  a ser utilizados.
int marcosGlobales;

void algoritmos(FILE* io_in, FILE* io_out);
void algOptimo(int *pages, int size, FILE *io_out);
void algFifo(int *pages, int size, FILE *io_out);
void algLRU(int *pages, int size, FILE *io_out);
void algClock(int *pages, int size, FILE *io_out);

#endif