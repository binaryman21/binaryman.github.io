#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numero_ingresado;
    int cant_num = 0;
    int cant_max_numeros = 5;
    int *pEspacio;
    int *pNuevo;
    pEspacio = (int *) malloc(cant_max_numeros * sizeof(int));

    if(pEspacio == NULL)
    {
        return 1;
    }

    do
    {
        if(cant_num == cant_max_numeros - 1)
        {
            pNuevo = (int *) realloc(pEspacio,(cant_max_numeros + 5) * sizeof(int));

                if(pNuevo == NULL)
                {
                    printf("\nNo se pudo expandir el espacio de memoria");
                }
                else
                {
                    printf("\nEl espacio en memoria se modifico correctamente");  
                    pEspacio = pNuevo; 
                    cant_max_numeros += 5;    
                }
        }
        printf("\nIngrese un numero entero (0 para salir): ");
        scanf("%d",&numero_ingresado);
        if(numero_ingresado != 0)
        {
            *(pEspacio + cant_num) = numero_ingresado;
            cant_num++;
        }

    } while (numero_ingresado != 0);
    
   
    free(pEspacio);
    
    return 0;
}