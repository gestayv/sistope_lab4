#include "politicas.h"

void algoritmos(FILE* io_in, FILE* io_out)
{
    //  Se crea un buffer para guardar cada número de página
    char *num = malloc(20);
    //  Se crea una variable para poder parsear el csv por caracter.
    char c;
    //  Se crea un contador i para ir almacenando el número de la página
    //  caracter por caracter en el buffer "num".
    int i = 0;
    //  Se crea un contador para ir almacenando cada número de página en un
    //  arreglo de enteros que se creará eventualmente.
    int i2 = 0;
    //  Se crea un contador de páginas para saber cuantas páginas hay en el csv.
    int counter = 0;
    //  Arreglo en el que se guardaran las páginas del csv.
    int *paginas;

    //  Primero se obtiene el primer caracter del csv, si el puntero queda en
    //  EOF significa que el archivo está vacío.
    c = fgetc(io_in);
    if(feof(io_in))
    {
        fprintf(stderr, "Archivo de entrada vacio.\n");
    }
    //  En caso contrario:
    else
    {
        //  Se devuelve el puntero al principio para leer el archivo desde 0.
        rewind(io_in);
        //  Se parsea el archivo caracter por caracter, por cada coma encontrada
        //  se suma 1 a la variable counter.
        do
        {
            c = fgetc(io_in);
            if(c == ',')
            {
                counter++;
            }
            if(feof(io_in))
            {
                break;
            }
        }while(1);
        //  Como la cantidad de comas es igual a la cantidad de páginas - 1
        //  se suma 1 más a counter.
        counter++;
        //  Se crea el arreglo que contendrá todas las páginas.
        paginas = malloc(sizeof(int)*counter);
        rewind(io_in);
        //  Si el contador es mayor a 1, se parsea nuevamente el csv
        //  esta vez almacenando todas las páginas en el arreglo creado.
        if(counter > 1)
        {
            do
            {
                c = fgetc(io_in);
                if(c == ',')
                {
                    num[i] = '\0';
                    sscanf(num, "%d", &paginas[i2]);
                    i2++;
                    i = 0;
                }
                else if(feof(io_in))
                {
                    num[i] = '\0';
                    sscanf(num, "%d", &paginas[i2]);
                    break;
                }
                else
                {
                    num[i] = c;
                    i++;
                }
            }while(1);
        }
        //  Si el contador es 1, se toma el primer elemento y se guarda en el
        //  arreglo creado.
        else if(counter == 1)
        {
            do
            {
                c = fgetc(io_in);
                if(feof(io_in))
                {
                    num[i] = '\0';
                    sscanf(num, "%d", &paginas[i2]);
                    break;
                }
                else
                {
                    num[i] = c;
                    i++;
                }
            } while(1);
        }
        //  Luego se llama a cada uno de los algoritmos de reemplazo

        algOptimo(paginas, counter, io_out);
        /*
        algFifo(paginas, counter, io_out);
        algLRU(paginas, counter, io_out);
        algClock(paginas, counter, io_out);
        */
    }
}

/*  Función algOptimo:
        - Aplica el algoritmo de reemplazo óptimo sobre el conjunto de págs recibido.
    Entrada:
        - pages:
        - size:
        - io_out:
    Salida:
        - Escribe en un archivo de texto un seguimiento al reemplazo de páginas
        y la tasa de miss y hit del algoritmo.
*/
void algOptimo(int *pages, int size, FILE *io_out)
{

    fprintf(io_out, "Algoritmo OPTIMO\n");
    int i = 0;
    int referencia = 0, tiempo = 0;
    listaC *marcosAlg = NULL;
    int numHit = 0;
    //  Primero creo el número de marcos, representados por nodos de una lista
    //  doblemente enlazada.
    while(i < marcosGlobales)
    {
        listaC *newM = createNode(-1);
        marcosAlg = addNodeLast(marcosAlg, newM);
        i++;
    }
    //  Luego, se comienzan a insertar las páginas en los marcos.

    int page = 0;
    listaC* aux = marcosAlg;
    listaC* aux2 = marcosAlg;

    //  Se comienza a recorrer el arreglo con las páginas entregadas en el csv
    for (page = 0; page < size; page++)
    {
        //  Si aún no se llenan todos los marcos con páginas, se ingresa una página en
        //  un marco vacío.
        if(page < marcosGlobales)
        {
            aux = searchNode(marcosAlg, pages[page]);
            if(aux != NULL)
            {
                numHit++;
                aux -> tiempo = page;
            }
            else
            {
                aux = marcosAlg;
                while(aux -> dato != -1)
                {
                    aux = aux -> next;
                }
                aux -> dato = pages[page];
                aux -> tiempo = page;
            }
            writeList(marcosAlg, io_out);
            showList(marcosAlg);
        }
        //  En el caso contrario, se debe buscar el dato en los marcos
        else
        {
            //  Si se encuentra, el número de hits aumenta en 1.

            aux = searchNode(marcosAlg, pages[page]);
            if(aux != NULL)
            {
                numHit++;
                aux -> tiempo = page;
            }
            //  En caso contrario, se debe ver cuál de las páginas cargadas en
            //  memoria (marcos), será referenciada en un mayor tiempo.
            else
            {
                aux = marcosAlg;
                do
                {
                    for(i = page; i < size; i++)
                    {
                        if(aux->dato == pages[i])
                        {
                            referencia = 1;
                            if(i-page > tiempo)
                            {
                                aux2 = aux;
                                tiempo = i - page;
                                break;
                            }
                        }
                    }
                    if(referencia == 0)
                    {
                        if(tiempo == 0)
                        {
                            tiempo = size;
                            aux2 = aux;
                        }
                        else if(tiempo == size)
                        {
                            if(aux2 -> tiempo > aux -> tiempo)
                            {
                                aux2 = aux;
                            }
                        }
                        else if(tiempo > 0 && tiempo < size)
                        {
                            aux2 = aux;
                            tiempo = size;
                        }
                    }
                    referencia = 0;
                    aux = aux -> next;
                }while(aux != marcosAlg);
                aux2 -> dato = pages[page];
                aux2 -> tiempo = page;
                tiempo = 0;
            }
            writeList(marcosAlg, io_out);
            showList(marcosAlg);
        }
    }

    float hitRate = numHit/(float)size * 100.0;
    missOptimo = 100.0 - hitRate;
    fprintf(io_out, "tasa miss: %.2f%% \n", missOptimo);
    fprintf(io_out, "tasa hit: %.2f%% \n", hitRate);

}

/*  Función algFifo
        - Aplica el algoritmo de reemplazo FIFO al conjunto de págs recibidos.
    Entrada:
        - pages:
        - size:
        - io_out:
    Salida:
        - Escribe en un archivo de texto un seguimiento al reemplazo de páginas
        y la tasa de miss y hit del algoritmo.
*/
void algFifo(int *pages, int size, FILE *io_out)
{
    fprintf(io_out, "Algoritmo FIFO\n");
    int i = marcosGlobales;
    listaC *marcosAlg = NULL;
    //  Primero creo el número de marcos, representados por nodos de una lista
    //  doblemente enlazada.
    while(i != 0)
    {
        listaC *newM = createNode(-1);
        marcosAlg = addNodeLast(marcosAlg, newM);
        i--;
    }
    //  Luego, se comienzan a insertar las páginas en los marcos.
    int page = 0;
    for (page = 0; page < size; page++)
    {

    }
}

/*  Función algLRU
        - Aplica el algoritmo de reemplazo LRU al conjunto de págs recibidas.
    Entrada:
        - pages:
        - size:
        - io_out:
    Salida:
        - Escribe en un archivo de texto un seguimiento al reemplazo de páginas
        y la tasa de miss y hit del algoritmo.
*/
void algLRU(int *pages, int size, FILE *io_out)
{
    int numHit = 0;
    fprintf(io_out, "Algoritmo LRU\n");
    int i = marcosGlobales;
    listaC *marcosAlg = NULL;
    //  Primero creo el número de marcos, representados por nodos de una lista
    //  doblemente enlazada.
    while(i != 0)
    {
        listaC *newM = createNode(-1);
        marcosAlg = addNodeLast(marcosAlg, newM);
        i--;
    }
    //  Luego, se comienzan a insertar las páginas en los marcos.
    int cont = marcosGlobales;
    listaC* aux = marcosAlg;
    listaC* ref = NULL;
    listaC* viejo = NULL;
    for (i = 0; i < size; i++)
    {
        //Si el marco esta vacio
        if(aux -> dato == -1){
            aux -> dato = pages[i];
            aux -> tiempo = cont;
            aux = aux -> next;
            cont--;
            writeList(marcosAlg,io_out);
        }
        //Si todos los marcos estan llenos
        else{
            //Busco si la pagina seleccionada esta en la lista de marcos.
            ref = searchNode(marcosAlg,pages[i]);
            //Si es asi (HIT)
            if(ref != NULL){
                //Sumo el hit
                numHit++;
                //Actualizo los tiempos.
                ref -> tiempo = 0;
                updateTime(marcosAlg);
                writeList(marcosAlg,io_out);
            }
            //Si no es asi (MISS). Reemplazo.
            else{
                //Encuentro el nodo antes referenciado
                viejo = findOldNode(marcosAlg);
                viejo -> dato = pages[i];
                viejo -> tiempo = 0;
                updateTime(marcosAlg);
                writeList(marcosAlg,io_out);
            }
        }

    }

    
    float hitRate = numHit/(float)size * 100.0;
    missOptimo = 100.0 - hitRate;
    fprintf(io_out, "tasa miss: %.2f%% \n", missOptimo);
    fprintf(io_out, "tasa hit: %.2f%% \n", hitRate);

}

/*  Función algClock
        - Aplica el algoritmo de reemplazo del reloj al conjunto de págs recibidas.
    Entrada:
        - pages:
        - size:
        - io_out:
    Salida:
        - Escribe en un archivo de texto un seguimiento al reemplazo de páginas
        y la tasa de miss y hit del algoritmo.
*/
void algClock(int *pages, int size, FILE *io_out)
{
    fprintf(io_out, "Algoritmo RELOJ\n");
    int i = marcosGlobales;
    listaC *marcosAlg = NULL;
    //  Primero creo el número de marcos, representados por nodos de una lista
    //  doblemente enlazada.
    while(i != 0)
    {
        listaC *newM = createNode(-1);
        marcosAlg = addNodeLast(marcosAlg, newM);
        i--;
    }
    //  Luego, se comienzan a insertar las páginas en los marcos.
    int page = 0;
    for (page = 0; page < size; page++)
    {

    }
}