#include "politicas.h"

int main(int argc, char* argv[])
{
    char    *entrada = malloc(200);
    int     eflag = 0;
    int     marcos = 0;
    int     mflag = 0;

    int c;
    opterr = 0;

    //  Se emplea getopt para obtener datos por terminal.
    while((c = getopt(argc, argv, "m:e:")) != -1)
	{
		switch(c)
		{
			case 'm':
                if(sscanf(optarg, "%d", &marcos) != 1)
                {
                    fprintf(stderr, "El número de marcos ha sido ingresado de forma erronea.\n");
                    fprintf(stderr, "Uso: ./politica -m NUMERO_MARCO -e NOMBRE_ARCHIVO_ENTRADA.\n");
                    return 1;
                }
                if(marcos <= 0)
                {
                    fprintf(stderr, "El número de marcos debe ser mayor a cero.\n");
                }
                mflag = 1;
				break;
            case 'e':
                if(sscanf(optarg, "%s", entrada) != 1)
                {
                    fprintf(stderr, "El nombre del archivo de entrada ha sido ingresado de forma erronea.\n");
                    fprintf(stderr, "Uso: ./politica -m NUMERO_MARCO -e NOMBRE_ARCHIVO_ENTRADA.\n");
                    return 1;
                }
                eflag = 1;
                break;
            //	Si getopt detecta un error, devuelve el valor '?'. Por lo que es necesario agregar el caso.
			case '?':
				//	Si el error encontrado está en el argumento "-m", se indica que se debe ingresar el número de marcos.
                if(optopt == 'm')
				{
					fprintf(stderr, "Se debe indicar el numero de marcos junto al parametro -%c.\n", optopt);
                    fprintf(stderr, "Uso: ./politica -m NUMERO_MARCO -e NOMBRE_ARCHIVO_ENTRADA\n");
				}
                //	Si el error encontrado está en el argumento "-m", se indica que se debe ingresar el nombre del archivo de entrada.
                else if(optopt == 'e')
                {
                    fprintf(stderr, "Se debe indicar el nombre del archivo de entrada junto al parametro -%c.\n", optopt);
                    fprintf(stderr, "Uso: ./politica -m NUMERO_MARCO -e NOMBRE_ARCHIVO_ENTRADA\n");
                }
				//	Si el argumento en el que se encontró el error se puede imprimir,
				//	se indica que la opción no existe.
				else if (isprint(optopt))
				{
					fprintf(stderr, "Opcion desconocida -%c.\n", optopt);
                    fprintf(stderr, "Uso: ./politica -m NUMERO_MARCO -e NOMBRE_ARCHIVO_ENTRADA\n");
				}
				//	Si el argumento en el que se encuentra el error no se puede imprimir,
				//	se indica que la opción tiene un caracter desconocido.
				else
				{
					fprintf(stderr, "Opcion con caracter desconocido `\\x%x'.\n", optopt);
                    fprintf(stderr, "Uso: ./politica -m NUMERO_MARCO -e NOMBRE_ARCHIVO_ENTRADA\n");
				}
				return 1;
			default:
				abort();
		}
	}

    //  Se verifica si se ingresaron los parámetros o no.
    if(!eflag)
    {
        fprintf(stderr, "No se ingreso el parametro -e.\n");
        return 1;
    }
    else if(!mflag)
    {
        fprintf(stderr, "No se ingreso el parametro -m.\n");
        return 1;
    }
    
    return 0;
}
