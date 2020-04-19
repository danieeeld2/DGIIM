/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: daniel
 *
 * Created on 31 de marzo de 2020, 16:53
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//  Declaración de funciones
//  Implementación y comentarios después del main

void Mostrarmenu();
int Respuestamenu();
void EjecutarMenu(int a, int turno, char tablero[6][7], FILE *r, FILE *g);
void MostrarTablero(char tablero[6][7]);
bool Ganador1(char tablero[6][7]);
bool Ganador2(char tablero[6][7]);
bool Jugadavalida(char tablero[6][7], int columna);
void EstablecerJugada(int turno, char ficha1, char ficha2, char tablero[6][7], int columna);


/*
 * 
 */
int main() {
    //  Declaración de variables
    
    int respuesta = 0;  //  Variable para moverse por el menú
    char tablero[6][7]; 
    const char ficha1 = 'O';    //  Ficha jugador1
    const char ficha2 = 'X'; //  Ficha jugador 2
    bool hay_ganador = false;
    bool gana1 = false;
    bool gana2 = false;
    int turno = 0;
    const int maximo = 42;  //  Máximo de turnos posibles
    bool seguirjugando = true;  //  Cuando este en false cierra el programa
    int columna;    //  Variable para elegir donde colocar
    FILE *cargar;   //  Variable de flujo para cargar partida guardada
    FILE *guardar;  //  Variable de flujo para guardar partida
    
    Mostrarmenu();    //  Comenzamos mostrando el menú
    respuesta = Respuestamenu();    //  Elegimos opción
    EjecutarMenu(respuesta, turno, tablero, cargar, guardar); //  Ejecutamos la opción del menú
    
    /*  Hacemos un bucle while para el desarrollo del juego. El programa no saldrá del bucle
        hasta que o bien se llegue al máximo de turnos posibles, o bien haya ganador o bien
        se decida parar el juego */
    
    //  Como las variables están previamente inicializadas, podemos recurrir a un bucle while
    //  en vez de a un bucle do-while
    
    while((!hay_ganador) && (turno != maximo)){     // hay_ganador || turno != maximo
        turno++;    //  Por jugada se aumenta en uno su valor
        
        if(turno % 2 != 0){ //  Si el turno es impar, le toca al jugador uno
            printf("\n Turno del jugador 1: \n\n");
        }
        
        if(turno % 2 == 0){ //  Si el turno es par, le toca al jugador dos, en este caso la CPU
            printf("\n Turno de la CPU: \n\n");
        }
        
        MostrarTablero(tablero);    // Mostramos el tablero para poder decidir la siguiente jugada
        
        if (turno % 2 != 0) {
            do { //  Pedimos la columna donde colocar
                printf("\n Introduce una columna válida o -1 para mostrar menú:");
                scanf("%i", &columna);
            } while ((!Jugadavalida(tablero, columna) && (columna != -1)) || ((columna < 1 || columna > 7) && (columna != -1))); //  Bucle para comprobar que la posición es válida
        } else {
            do{
                printf("\n Generando número aleatorio: ");
                columna = rand()%7;                        
            }while((!Jugadavalida(tablero, columna)) || ((columna <1 || columna > 7))); // Jugadavalida == false es igual a !Jugadavalida
        }
        
        if(Jugadavalida(tablero, columna) && (columna != -1)){
            EstablecerJugada(turno, ficha1, ficha2, tablero, columna);  //  Modificamos el tablero
            MostrarTablero(tablero);                                    //  y mostramos el resultado
        }
        
        if(columna == -1){  //  Damos la opción de entrar al menú
            turno = turno - 1;
            Mostrarmenu();
            respuesta = Respuestamenu();
            EjecutarMenu(respuesta, turno, tablero, cargar, guardar);
        }   
        
        gana1 = Ganador1(tablero);
        gana2 = Ganador2(tablero);
        hay_ganador = gana1 || gana2;
    }
    
    if(hay_ganador == true){
        if(gana1 = Ganador1(tablero))
            printf("\n\n Gana el jugador 1");
        
        if(gana2 = Ganador2(tablero))
            printf("\n\n Gana la CPU");        
    }else{
        if(turno == 42)
            printf("\n\n Empate");
    }
            
    return 0;
}

//  Función que muestra el menú

void Mostrarmenu(){
    printf("\n 1. Nueva partida");
    printf("\n 2. Cargar partida");
    printf("\n 3. Guardar partida actual");
    printf("\n 4. Salir");
}

//  Función para navegar por el menú

int Respuestamenu(){
    int a;
    
    do{
        printf("\n Seleccione una opción:");
        scanf("%d", &a);
    }while(a <= 0 || a > 4);    //  Bucle para asegurarnos de que la respuesta sea válida
    
    return a;
}

//  Función para ejecutar respuesta del menu

void EjecutarMenu(int a, int turno, char tablero[6][7], FILE *r, FILE *g){
    if(a == 1){ //  Inicializamos los datos para una nueva partida
        int i;
        int j;

        for (i = 0; i < 6; i++)
            for (j = 0; j < 7; j++)
                tablero[i][j] = ' ';

        turno = 0;        
    }
    
    if(a == 2){ //  Cargamos una partida
        r = fopen("partida.txt", "r"); //  Introduzca la ruta absoluta del fichero. Lo abrimos para solo lectura
        if(r == NULL){  //  Comprobamos si se ha abierto correctamente
            printf("\n No se ha podido cargar el fichero");
            exit(1);    //  Paramos el proceso en caso fallido
        }else{  //  Leemos los datos en el orden que los inicializamos
            int i;
            int j;
            
            for(i = 0; i != 6; i++)
                for(j = 0; j != 7; j++)
                    fscanf(r, "%c", &tablero[i][j]);
            
            fscanf(r, "\n");
            fscanf(r, "%d", &turno);
            
            fclose(r);
        }     
    }
    
    if(a == 3){ //  Guardar partida
        g = fopen("partida.txt", "w"); //  Introduzca la ruta absoluta del fichero. Lo abrimos en modo escritura
        if(g == NULL){  //  Comprobamos si se ha abierto correctamente
            printf("\n No se ha podido cargar el fichero");
            exit(1);    //  Paramos el proceso en caso fallido
        } else { //  Copiamos los datos en el mismo orden que lo inicializamos
            int i;
            int j;
            for (i = 0; i != 6; i++)
                for (j = 0; j != 7; j++)
                    fprintf(g, "%c", tablero[i][j]);
            
            fprintf(g, "\n");
            fprintf(g, "%d", turno);
            
            fclose(g);
        }     
    }
    
    if(a == 4){ //   Salir del juego
        exit(1);  //  Acabamos la partida;
    }
}

//  Función para mostrar el tablero


void MostrarTablero(char tablero[6][7]){
    int i;
    int j;
    
    printf("|--------------------|\n");
    printf("| 1| 2| 3| 4| 5| 6| 7|\n");
    
    for(i=0; i<6; i++){
        printf("|");
        for(j=0; j<7; j++){
            printf("%c |", tablero[i][j]);
        }
        printf("\n|--------------------|\n");
    }    
}

//  Función para comprobar si hay un ganador

bool Ganador1(char tablero[6][7]){
    int contador = 0; // Cuando llegue a 4 significa que hay un ganador
    bool hay_ganador = false;
    char ficha = 'O';
    int i;
    int j;
    int h;
    int z;
    
    //  Comprobamos las horizontales
    
    for(i = 0; i != 6; i++){
        for(j = 0; j != 7; j++){
            if(tablero[i][j] == 'O') // Miramos si dos posiciones consecutivas son iguales
                contador++;
            
            if(tablero[i][j] == ' ' || tablero[i][j] == 'X')    //  Reseteamos el contador si no hay ninguna ficha colocada o no son iguales
                contador = 0;
            
            if(contador == 4)
                hay_ganador = true;
        }
    }
    
    contador = 0;
    
    //  Comprobamos ahora las verticales (si no hay ganador)

    if (hay_ganador == false) {
        for (j = 0; j != 7; j++) {
            for (i = 0; i != 6; i++) {
                if (tablero[i][j] == 'O') // Miramos si dos posiciones consecutivas son iguales
                    contador++;

                if (tablero[i][j] == ' ' || tablero[i + 1][j] == 'X') //  Reseteamos el contador si no hay ninguna ficha colocada o no son iguales
                    contador = 0;

                if (contador == 4)
                    hay_ganador = true;
            }
        }
    }
    
    contador = 0;
    
    //  Comprobamos todas las diagonales con 4 o mas elementos (si no hay ganador
    
    /* if(hay_ganador == false) {
        int ii, jj;
        for (i = 1; i < 5; i++) {
            for (j = 1; j < 6; j++) {

                /
                contador = 0;
                // izquierda-arriba:
                for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--) {
                    if (tablero[ii][jj] == 'O') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }
                // derecha-abajo:
                for (ii = i + 1, jj = j + 1; (ii <= 5) || (jj <= 6); ii++, jj++) {
                    if (tablero[ii][jj] == 'O') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }

              
                contador = 0;
                // izquierda-arriba:
                for (ii = i, jj = j; (ii <= 5) || (jj >= 0); ii++, jj--) {
                    if (tablero[ii][jj] == 'O') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }
                // derecha-arriba:
                for (ii = i - 1, jj = j + 1; (ii >= 0) || (jj <= 6); ii--, j++) {
                    if (tablero[ii][jj] == 'O') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }

            }
        }
    }*/
    
    return hay_ganador;
    
}

bool Ganador2(char tablero[6][7]) {
    int contador = 0; // Cuando llegue a 4 significa que hay un ganador
    bool hay_ganador = false;
    int i;
    int j;
    int z;
    int h;

    //  Comprobamos las horizontales

    for (i = 0; i != 6; i++) {
        for (j = 0; j != 7; j++) {
            if (tablero[i][j] == 'X') // Miramos si dos posiciones consecutivas son iguales
                contador++;

            if (tablero[i][j] == ' ' || tablero[i][j] == 'O') //  Reseteamos el contador si no hay ninguna ficha colocada o no son iguales
                contador = 0;

            if (contador == 4)
                hay_ganador = true;
        }
    }

    contador = 0;

    //  Comprobamos ahora las verticales (si no hay ganador)

    if (hay_ganador == false) {
        for (j = 0; j != 7; j++) {
            for (i = 0; i != 6; i++) {
                if (tablero[i][j] == 'X') // Miramos si dos posiciones consecutivas son iguales
                    contador++;

                if (tablero[i][j] == ' ' || tablero[i + 1][j] == 'O') //  Reseteamos el contador si no hay ninguna ficha colocada o no son iguales
                    contador = 0;

                if (contador == 4)
                    hay_ganador = true;
            }
        }
    }

    contador = 0;


    //  Comprobamos todas las diagonales con 4 o mas elementos (si no hay ganador)
/*
    if(hay_ganador == false) {
        int ii, jj;
        for (i = 1; i < 5; i++) {
            for (j = 1; j < 6; j++) {

               
                contador = 0;
                // izquierda-arriba:
                for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--) {
                    if (tablero[ii][jj] == 'X') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }
                // derecha-abajo:
                for (ii = i + 1, jj = j + 1; (ii <= 5) || (jj <= 6); ii++, jj++) {
                    if (tablero[ii][jj] == 'X') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }

              
                contador = 0;
                // izquierda-arriba:
                for (ii = i, jj = j; (ii <= 5) || (jj >= 0); ii++, jj--) {
                    if (tablero[ii][jj] == 'X') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }
                // derecha-arriba:
                for (ii = i - 1, jj = j + 1; (ii >= 0) || (jj <= 6); ii--, j++) {
                    if (tablero[ii][jj] == 'X') {
                        contador++;
                        if (contador == 4) 
                            hay_ganador = true;
                    } else
                        break;
                }

            }
        }
    }
*/

    return hay_ganador;
}

//  Comprueba si una jugada es válida

/*  Aclaración para las funciones que utilizan la columna
    en la que se desea colocar como argumento:
 
    En la declaración de la matriz, la primera posició es la 00,
    luego, como tenemos 7 columnas, estas van de la 0 a la 6, 
    pero al usuario se la pedimos de la 1 a la 7, por lo que hay
    que restarle una unidad para no salirnos de los límites de la misma*/

bool Jugadavalida(char tablero[6][7], int columna){
    bool valido = false;    //  Auxiliar
    int i;
    
    for(i = 0; i != 6; i++)
        if(tablero[i][columna-1] == ' ') //   En el fichero de nueva partida inicializo todas las posiciones a 0
            valido = true;
    
    return valido;
}

//  Función para establecer una jugada

void EstablecerJugada(int turno, char ficha1, char ficha2, char tablero[6][7], int columna){
    char ficha;
    int auxiliar = 0;
    int i;
    
    if(turno % 2 != 0){ //  Si el turno es impar, le toca al jugador uno
        ficha = ficha1;
    }else
        ficha = ficha2;     //  Sino, le toca a jugador 2
    
    if(Jugadavalida(tablero, columna))  //  Medida de seguridad para comprobar que la jugada establecida es válida
        for(i = 5; auxiliar != 1; i--)  //  Al igual que las columnas, las filas van de 0 a 5
            if(tablero[i][columna-1] != ficha1 && tablero[i][columna-1] != ficha2){
                tablero[i][columna-1] = ficha;
                auxiliar++;
            }
}
