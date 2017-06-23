#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

//  Estructura utilizada para representar un marco en memoria
typedef struct listaC
{
    int dato;               //  Corresponde a la página que contiene.
    int tiempo;             //  Corresponde al tiempo en que la pág fue cargada o referenciada.
    int bitClock;           //  Corresponde al bit de uso del algoritmo del reloj.
    struct listaC* next;    //  Puntero al nodo siguiente de la lista.
    struct listaC* prev;    //  Puntero al nodo anterior de la lista.
}listaC;

listaC* createNode(int dato);
listaC* addNodeFirst(listaC *L, listaC *newNode);
listaC* addNodeLast(listaC *L, listaC *newNode);
listaC *deleteNode(listaC *L, int dato);
listaC* searchNode(listaC *L, int dato);
void writeList(listaC *L, FILE *io_out);
void showList(listaC *L);
listaC* findOldNode(listaC* L);
void updateTime(listaC* L);

#endif