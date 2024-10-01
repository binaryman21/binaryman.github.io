/***################# EJERCICIO: CONTROLANDO AL ROBOT #####################
AUTOR: CANAL DE YOUTUBE https://youtube.com/@binaryman01
SUSCRIBETE PARA RECIBIR NUEVOS VIDEOTUTORIALES DE PROGRAMACION EN C!
***/

#include <stdio.h>
#include <stdlib.h>
struct Punto //Struct para almacenar las coordenadas (x,y)
{
    short x;
    short y;
};
struct Robot //Structs para almacenar los datos del robot
{
    struct Punto posicion;
    unsigned short direccion;
    unsigned short nivel_bateria;
};

//################# PROTOTIPOS DE FUNCIONES #####################
void inicializarRobot(struct Robot *);
void mostrarDatosRobot(struct Robot *);
short cargarObstaculos(struct Punto *);
short hayObstaculo(struct Punto *,short,struct Punto);
short avanzar(struct Robot *,struct Punto *,short);
short girar(struct Robot *);
void dibujarPlano(struct Robot *,struct Punto *,short);

//################# FUNCION MAIN #####################
int main()
{
    char direcciones[4][15] = {"Derecha","Abajo","izquierda","arriba"};
    unsigned short opcion;
    short cant_obstaculos;
    struct Robot *miRobot; //Puntero al espacio de memoria con los datos del robot
    struct Punto *obstaculos; //Puntero al espacio de memoria que guarda los obstaculos
    short resultado_avanzar; 

    //Reservo espacio en memoria con malloc para el struct Robot
    miRobot = (struct Robot *) malloc(sizeof(struct Robot)); 
    //Valido que el espacio se haya asignado correctamente
    if(miRobot == NULL)
    {
        return 1;
    }
    //Reservo espacio en memoria con malloc para almacenar hasta 10 obstaculos
    obstaculos = (struct Punto *) malloc(sizeof(struct Punto) * 10);
    //Valido que el espacio se haya asignado correctamente
    if(obstaculos == NULL)
    {
        return 2;
    }

    printf("\nInicializando robot...");
    inicializarRobot(miRobot); //Inicializo los datos del robot
    mostrarDatosRobot(miRobot); //Muestro los valores actuales por pantalla
    printf("\n############### CARGA DE OBSTACULOS EN EL MAPA ##################\n");
    cant_obstaculos = cargarObstaculos(obstaculos); //Cargo los obstaculos en el mapa
    dibujarPlano(miRobot,obstaculos,cant_obstaculos); //Dibuja el mapa
    //------------------------MENU PRINCIPAL----------------------------
    do
    {
        //Imprimo las opciones del menu
        printf("\n\n############### MENU PRINCIPAL ##################\n");
        printf("\n01: Girar a la derecha");  
        printf("\n02: Avanzar en la direccion actual"); 
        printf("\n03: Dibujar plano");
        printf("\n00: Salir");    
        printf("\n>> Ingrese una opcion: ");
        scanf("%hu",&opcion); //El usuario ingresa una opcion

        //Switch con las diferentes opciones
        switch(opcion)
        {
            case 1: //GIRAR ROBOT A LA DERECHA
            if(girar(miRobot)) //Llamo a la funcion para girar el robot
            {
                printf("\n>ORDEN AL ROBOT >> GIRAR A LA DERECHA\n");
                printf(">> \nGirando a la derecha...");
                printf(">> \nEl robot ha girado a la direccion %s",direcciones[miRobot->direccion]);
            }
            else //Si no se pudo girar el robot
            {
                printf("\n>> *** No se pudo realizar el giro ***");
                printf("\n>> *** Nivel de bateria bajo ***");
            }
            break;
            case 2: //AVANZAR EN LA DIR ACTUAL
            printf("\n>ORDEN AL ROBOT >> AVANZAR EN LA POSICION ACTUAL\n");
            printf("\n>> *** Intentando avanzar en la direccion %s... ***",direcciones[miRobot->direccion]);
            printf("\n>> *** Analizando obstaculos... ***");
            printf("\n>> *** Analizando fontera del mapa... ***");
            resultado_avanzar = avanzar(miRobot,obstaculos,cant_obstaculos); //Llamo a la funcion 'avanzar'
            if(resultado_avanzar == 0) //return 0: nivel de bateria bajo 
            {
                printf("\n>> *** No se pudo avanzar en la dir actual > Nivel de bateria bajo ***");
            }
            else if(resultado_avanzar == -1) //return -1: Excede frontera
            {
                printf("\n>> *** No se pudo avanzar en la dir actual > Excede la frontera ***");
            }
            else if(resultado_avanzar == -2) //return -2: Obstaculo
            {
                printf("\n>> *** No se pudo avanzar en la dir actual > Hay un obstaculo ***");
            }
            else
            {
                printf("\n>> *** El robot avanzo correctamente ***");
                mostrarDatosRobot(miRobot); //Muestra los datos del robot
            }
            dibujarPlano(miRobot,obstaculos,cant_obstaculos); //Dibuja el mapa
            break;
            case 3: //DIBUJAR MAPA
            printf("\n################# VISTA DEL MAPA ###############\n");
            dibujarPlano(miRobot,obstaculos,cant_obstaculos); //Llama a la funcion para dibujar el mapa
            break;
            case 0: //SALIR
            free(miRobot); //Libera el espacio de memoria del robot
            free(obstaculos); //Libera el espacio de memoria de los obstaculos
            return 0;
            break;
            default: //DEFAULT
            printf("\n\n>> *** La opcion seleccionada es incorrecta ***\n");
            break;
        }
    } while (opcion != 0); //El programa se ejecuta mientras no se elija salir
    return 0;
}
/***################# FUNCION PARA INICIALIZAR EL ROBOT #####################
 * Parametros: Puntero struct Robot -> apunta al espacio de memoria con los datos del robot
***/
void inicializarRobot(struct Robot * r)
{
    r->nivel_bateria = 100;
    r->direccion = 0;
    r->posicion.x = 0;
    r->posicion.y = 0;
}
/***################# FUNCION PARA MOSTRAR LOS DATOS DEL ROBOT #####################
 * Parametros: Puntero struct Robot -> apunta al espacio de memoria con los datos del robot
***/
void mostrarDatosRobot(struct Robot * r)
{
    printf("\n################# ESTADO DEL ROBOT ###############\n");   
    printf("\nNivel de bateria: %u",r->nivel_bateria);
    printf("\nDireccion actual: %u",r->direccion);
    printf("\nPosicion actual: (%i,%i))",r->posicion.x,r->posicion.y);
    printf("\n\n##################################################\n");
}
/***################# FUNCION PARA CARGAR LOS OBSTACULOS #####################
 * Parametros: Puntero struct Punto -> apunta al espacio de memoria con los obstaculos
***/
short cargarObstaculos(struct Punto * p)
{
    short cant_obstaculos = 0; //Inicializo el contador de obstaculos
    do
    {
        printf("\n>> Ingrese la coord x del obstaculo (-1 para terminar): ");
        scanf("%hi",&p->x); //Ingresa la coord x del obstaculo
        
        //Valido que no haya elegido salir (-1) y que la coord x este dentro del plano (0-7)
        if(p->x != -1 && (p->x >= 0 && p->x <= 7)) 
        {
            printf("\n>> Ingrese la coord y del obstaculo: ");
            scanf("%hi",&p->y); //Ingresa la coord y del obstaculo

            /***Valido que:
             * La coord y este dentro del plano (0-7)
             * La coord x o la coord y sean distintos de cero ya que (0,0) no es un obstaculo valido
               porque ahi comienza posicionado el robot
            ***/
            if((p->y >= 0 && p->y <= 7) && (p->x != 0 || p->y != 0))
            {
                cant_obstaculos++; //Incremento el contador de obstaculos
                p++; //Incremento la dir de memoria: Paso a apuntar al espacio del siguiente punto en el vector
                printf("\n>> *** El obstaculo se cargo correctamente ***\n");
            }
            else
            {
                printf("\n>> *** La coordenada y no es valida ***\n");
            }

        }
        else if(p->x == -1)
        {
            printf("\n>> *** Finalizo la carga de obstaculos *** \n");
        }
        else
        {
            printf("\n>> *** La coordenada x no es valida *** \n");
        }


    } while (cant_obstaculos < 10 && p->x != -1);
    
    return cant_obstaculos;
}
/***################# FUNCION PARA GIRAR EL ROBOT A LA DERECHA #####################
 * Parametros: Puntero struct Robot -> apunta al espacio de memoria con los datos del robot
***/
short girar(struct Robot *r)
{
    if(r->nivel_bateria > 15) //Valido que el nivel de bateria sea superior al 15%
    {
        if(r->direccion == 3) //Si esta en la direccion 3 (arriba) pasa a 0 (derecha)
        {
            r->direccion = 0;
        }
        else //Si esta en las direccion 0,1,2 pasa a la siguiente (incremento la dir)
        {
            r->direccion++;
        }
        r->nivel_bateria -= 5; //disminuyo el nivel de bateria en 5%
        return 1;
    }
    else
    {
        return 0;
    }
}
/***################# FUNCION PARA REVISAR SI HAY UN OBSTACULO #####################
 * PARAMETROS: 
    * Puntero struct Punto 'obs' -> apunta al espacio de memoria con los obstaculos
    * short 'cant' cantidad de obstaculos
    * struct Punto 'p' -> coordenadas donde se quiere revisar si hay un obstaculo
 * SALIDA:
    * 1: Hay obstaculo en ese punto
    * 2: No hay obstaculo en ese punto 
***/
short hayObstaculo(struct Punto * obs,short cant,struct Punto p)
{
    for(int i = 0; i < cant;i++) //Recorro el espacio de mem con los obstaculos
    {
        //Si coinciden las coord (x,y) del obs con las coord (x,y) del punto devuelve 1
        if((obs + i)->x == p.x && (obs + i)->y == p.y) 
        {
            return 1;
        }
    }
    return 0;
}
/***################# FUNCION PARA AVANZAR EN LA DIRECCION ACTUAL #####################
 * PARAMETROS: 
    * puntero struct Robot * 'r' -> Apunta al espacio de memoria con los datos del robot
    * Puntero struct Punto * 'obs' -> apunta al espacio de memoria con los obstaculos
    * short 'cant' cantidad de obstaculos
 * SALIDA:
    * -2: No se pudo avanzar por obstaculo en ese punto
    * -1: No se pudo avanzar porque excede la frontera
    * 0: No se pudo avanzar por bateria baja 
    * 1: Avance correcto
***/
short avanzar(struct Robot * r,struct Punto * obs ,short cant)
{
    if(r->nivel_bateria <= 15) //Valida el nivel de bateria
    {
        return 0;
    }
    struct Punto aux; //Punto auxiliar donde se guarda temporalmente la nueva coord con el avance
    aux = r->posicion; //Inicializo el punto auxiliar con las coord actuales del robot
    switch(r->direccion) //Modifico las coord del punto auxiliar segun la direccion de avance
    {
        case 0: //Direccion derecha '->' incrementa la coord x
        aux.x++;
        break;
        case 1: //Direccion abajo 'v' disminuye la coord y
        aux.y--;
        break;
        case 2: //Direccion izquierda '<-' disminuye la coord x
        aux.x--;
        break;
        case 3: //Direccion arriba '^' incremento la coord y
        aux.y++;
        break;
    }
    //Si el punto auxiliar en la nueva posicion esta fuera de la frontera del plano devuelvo -1
    if(aux.x < 0 || aux.x > 7 || aux.y < 0 || aux.y > 7)
    {
        return -1;
    }
    //Si el punto auxiliar en la nueva posicion esta en un obstaculo devuelvo -2
    else if(hayObstaculo(obs,cant,aux))
    {
        return -2;
    }
    else //Si el punto auxiliar en la nueva posicion es correcto se lo asigno a la posicion del robot
    {
        r->posicion = aux; //Asigno el punto auxiliar a la poscion del robot
        r->nivel_bateria -= 5; //Disminuye la bateria en 5%
        return 1; 
    }
}
/***################# FUNCION PARA AVANZAR EN LA DIRECCION ACTUAL #####################
 * PARAMETROS: 
    * puntero struct Robot * 'r' -> Apunta al espacio de memoria con los datos del robot
    * Puntero struct Punto * 'obs' -> apunta al espacio de memoria con los obstaculos
    * short 'cant' cantidad de obstaculos
***/
void dibujarPlano(struct Robot *r,struct Punto *obs,short cant)
{
    struct Punto p1; //Declaro un punto (x,y)
    for(short y = 7;y>=0;y--) //Avanza en y (Una fila de coord del plano, comenzando en la esquina sup izq (7,0))
    {
        printf("\n"); //Salto de linea para formar una nueva fila o renglon del plano
        p1.y = y; //Fijo la coord y 
        for(short x = 0;x < 8;x++) //Comienzo a variar las coord x con la coord y fijada anteriormente
        {
            p1.x = x; //Armo el punto con la coord x actual y la coord y fijada anteriormente
            if(hayObstaculo(obs,cant,p1)) //Reviso si hay obstaculos
            {
                printf(" O "); //Si hay un obstaculo dibujo una 'O'
            }
            else if(r->posicion.x == p1.x && r->posicion.y == p1.y) //Reviso si en ese punto esta el robot
            {
                printf(" R "); //Si esta el robot dibujo 'R'
            }
            else
            {
                printf(" X "); //Si la posicion esta libre dibujo 'X'
            }
        }  
    } 
    printf("\n");
}