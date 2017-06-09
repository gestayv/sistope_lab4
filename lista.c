#include "lista.h"

/*  Función createNode:
        - Se encarga de crear un nuevo nodo para una lista circular al reservar
        la memoria que le corresponde y asignarle un dato que se le entrega.

    Entrada:
        - dato: Entero correspondiente al dato del nodo que se crea.

    Salida:
        - Si no hay problemas al reservar memoria para el nodo, se devuelve un puntero
        al tipo de dato listaC, lo que corresponde a un nuevo nodo. De lo contrario
        se devuelve nulo.
*/
listaC* createNode(int dato)
{
    listaC *newNode = malloc(sizeof(listaC));
    if(newNode != NULL)
    {
        newNode -> dato = dato;
        newNode -> next = newNode;
        newNode -> prev = newNode;
        return newNode;
    }
    return NULL;
}

/*  Función addNodeFirst
        - Se encarga de insertar un nodo al principio de una lista circular.

    Entrada:
        - L: Puntero al primer nodo de la lista circular en la que se quiere insertar
        un nodo.

        - newNode: Nodo que se desea insertar en la lista circular.

    Salida:
        - Se entrega una nueva lista correspondiente a la lista original modificada
        con un nuevo nodo como el primer elemento.
*/
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

/*  Funcioń addNodeLast:
        - Se encarga de añadir un nodo al final de una lista circular.

    Entada:
        - L: Puntero al primer nodo de la lista circular en la que se quiere insertar
        un elemento.

        - newNode: Nodo que se desea insertar al final de la lista circular.

    Salida:
        - Se entrega una nueva lista correspondiente a la lista original modificada
        con un nuevo nodo como el último elemento.
*/
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

/*  Función deleteNode:
        - Se encarga de eliminar un nodo de una lista circular.

    Entrada:
        - L: Puntero al primer elemento de la lista circular de la cual se desea
        eliminar un nodo.

        - dato: Corresponde al dato que contiene el nodo que se desea eliminar.
        Como en este laboratorio los datos son únicos por nodo, no hay conflictos.

    Salida:
        - Se entrega una nueva lista, correspondiente a la lista original modificada
        con un nodo menos, correspondiente al que se desea eliminar. Si la lista queda
        vacía se devuelve NULL.
*/
listaC *deleteNode(listaC *L, int dato)
{
    if(L == NULL)
    {
        return NULL;
    }
    else if(L -> dato == dato)
    {
        if(L -> prev == L)
        {
            free(L);
            return NULL;
        }
        else
        {
            listaC *aux = L;
            listaC *auxPrev = aux -> prev;
            listaC *auxNext = aux -> next;
            auxPrev -> next = auxNext;
            auxNext -> prev = auxPrev;
            L = aux -> next;
            aux -> next = NULL;
            aux -> prev = NULL;
            free(aux);
            return L;
        }
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
            printf("El dato que se desea eliminar no esta en la lista.\n");
            return L;
        }
        else if(aux == L)
        {
            printf("El dato que se desea eliminar no esta en la lista.\n");
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

/*  Función showList:
        - Se encarga de mostrar por pantalla los contenidos de la lista circular.

    Entrada:
        - L: Puntero al primer elemento de la lista circular.
*/
void showList(listaC *L)
{
    if(L == NULL)
    {
        printf("Lista vacia\n");
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