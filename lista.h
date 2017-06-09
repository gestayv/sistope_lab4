#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

typedef struct listaC
{
    int dato;
    struct listaC* next;
    struct listaC* prev;
}listaC;

listaC* createNode(int dato);
listaC* addNodeFirst(listaC *L, listaC *newNode);
listaC* addNodeLast(listaC *L, listaC *newNode);
void showList(listaC *L);
listaC *deleteNode(listaC *L, int dato);

#endif