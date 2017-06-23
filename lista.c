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
        newNode -> tiempo = 0;
        newNode -> bitClock = 0;
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
    if(L == NULL)
    {
        L = newNode;
    }
    else if(L -> prev == L)
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

/*  Función showList
        - Se encarga de mostrar una lista circular por terminal/consola.
    Entrada:
        - L: Puntero al primer elemento de la lista circular.
*/
void showList(listaC *L)
{
    listaC *aux = L;
    if(aux == NULL)
    {
        printf("Lista vacia.\n");
    }
    else
    {
        do
        {
            printf("|d: %d (%d) |", aux -> dato, aux -> tiempo);
            aux = aux -> next;
        } while(aux != L);
        printf("\n");
    }
}



/*  Función writeList:
        - Se encarga de escribir en un archivo los contenidos de la lista circular.

    Entrada:
        - L: Puntero al primer elemento de la lista circular.
        - io_out: Puntero al archivo en el que se escriben los datos.
*/
void writeList(listaC *L, FILE *io_out)
{
    if(L != NULL)
    {
        listaC *aux = L;
        do
        {
            if(aux == L -> prev)
            {
                if(aux -> dato != -1)
                {
                    fprintf(io_out, "%d", aux->dato);
                    aux = aux -> next;
                }
                else
                {
                    aux = aux -> next;
                }
            }
            else
            {
                if(aux -> dato != -1)
                {
                    fprintf(io_out, "%d - ", aux->dato);
                    aux = aux -> next;
                }
                else
                {
                    fprintf(io_out, " - ");
                    aux = aux -> next;
                }
            }
        }while(aux != L);
        fprintf(io_out, "\n");
    }
}

/*  Función searchNode:
        - Se encarga de buscar un nodo en una lista a partir de un dato determinado.
    Entrada:
        - L: Puntero al primer nodo de la lista en la que se busca.
        - dato: Dato utilizado para encontrar el nodo.
    Salida:
        - Puntero a un nodo de la lista, si se encuentra, se devuelve un puntero
        al nodo que tiene el dato, en el caso contrario se devuelve nulo.
*/
listaC* searchNode(listaC *L, int dato)
{
    listaC *aux = L;
    do {
        if(aux -> dato == dato)
        {
            return aux;
        }
        aux = aux -> next;
    } while(aux != L);
    return NULL;
}

/*  Función findOldNode:
        - Retorna el nodo que lleva mayor tiempo en la lista de marcos
        - Función utilizada en el algoritmo LRU.
    Entrada:  
        - L: Puntero al primer nodo de la lista de marcos (lista donde se guardan las referencias)
    Salida:
        - Puntero al nodo con el mayor tiempo.
*/
listaC* findOldNode(listaC* L){
    listaC* aux = L -> next;
    listaC* viejo = L;
    int mayor = L -> tiempo;
    while(aux != L){
        if(aux->tiempo > mayor){
            mayor = aux -> tiempo;
            viejo = aux;
        }
        aux = aux -> next;
    }
    return viejo;
}

/*  Función updateTime:
        - Actualiza el tiempo de los nodos de la lista de marcos, sumandole uno al tiempo de cada nodo.
        - Función utilizada en el algoritmo LRU.
    Entrada:  
        - L: Puntero al primer nodo de la lista de marcos (lista donde se guardan las referencias).
    Salida:
        - La misma lista con los tiempos actualizados.
*/
void updateTime(listaC* L){
    listaC* aux = L;
    aux -> tiempo = aux -> tiempo + 1;
    aux = aux -> next;
    while(aux != L){
        aux -> tiempo = aux -> tiempo + 1;
        aux = aux -> next;
    }
}