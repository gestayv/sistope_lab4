#include "lista.h"

listaC* createNode(int dato)
{
    listaC *newNode = malloc(sizeof(listaC));
    printf("asd\n");
    if(newNode != NULL)
    {
        newNode -> dato = dato;
        newNode -> next = newNode;
        newNode -> prev = newNode;
        return newNode;
    }
    return NULL;
}

listaC* addNodeFirst(listaC *L, listaC *newNode)
{
    //  Si la lista es de un solo nodo.
    if(L -> prev == L)
    {
        //  El anterior y el siguiente del nuevo son el primero.
        newNode -> next = L;
        newNode -> prev = L;
        //  El anterior y el siguiente del primero son el nuevo.
        L -> next = newNode;
        L -> prev = newNode;
    }
    else
    {
        //  Se guarda el último nodo en una variable auxiliar.
        listaC *aux_1 = L -> prev;
        //  El siguiente del último es el nuevo y el anterior del nuevo es el último.
        aux_1 -> next = newNode;
        newNode -> prev = aux_1;
        //  El anterior al primero es el nuevo y el siguiente del nuevo es el primero.
        L -> prev = newNode;
        newNode -> next = L;
    }
    //  El nuevo pasa a ser el primero.
    L = newNode;
    return L;
}

listaC* addNodeLast(listaC *L, listaC *newNode)
{
    if(L -> prev == L)
    {
        //  El anterior y el siguiente del nuevo son el primero.
        newNode -> next = L;
        newNode -> prev = L;
        //  El anterior y el siguiente del primero son el nuevo.
        L -> next = newNode;
        L -> prev = newNode;
    }
    else
    {
        //  Se guarda el último nodo en una variable auxiliar.
        listaC *aux_1 = L -> prev;
        //  El siguiente del último es el nuevo y el anterior del nuevo es el último.
        aux_1 -> next = newNode;
        newNode -> prev = aux_1;
        //  El anterior al primero es el nuevo y el siguiente del nuevo es el primero.
        L -> prev = newNode;
        newNode -> next = L;
    }
    return L;
}

listaC *deleteNode(listaC *L, int dato)
{
    if(L == NULL)
    {
        return NULL;
    }
    else
    {
        listaC *aux = L;
        do
        {
            if(aux -> dato == dato)
            {
                break;
            }
            aux = aux -> next;
        }while(aux != L);
        if(aux -> prev == aux)
        {
            free(aux);
            return NULL;
        }
        else if(aux == L)
        {
            listaC* auxPrev = aux -> prev;
            listaC* auxNext = aux -> next;
            auxPrev -> next = auxNext;
            auxNext -> prev = auxPrev;
            L = aux -> next;
            aux -> next = NULL;
            aux -> prev = NULL;
            free(aux);
            return L;
        }
        else
        {
            listaC* auxPrev = aux -> prev;
            listaC* auxNext = aux -> next;
            auxPrev -> next = auxNext;
            auxNext -> prev = auxPrev;
            aux -> next = NULL;
            aux -> prev = NULL;
            free(aux);
            return L;
        }
    }
}

void showList(listaC *L)
{
    if(L == NULL)
    {
        printf("Lista vacia");
    }
    else
    {
        listaC *aux = L;
        do
        {
            printf("%d ", aux->dato);
            aux = aux -> next;
        }while(aux != L);
        printf("\n");
    }
}