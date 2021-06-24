/**
 * @file pmv-OpenMP-b.c
 * @author Daniel Alconchel Vázquez
 * @brief Calcula el producto de una matriz por un vector (OPENMP B)
 * Compilacion: gcc -O2 -fopenmp pmv-OpenMP-b.c -o pmv-OpenMP-b
 */

#include <omp.h> //INCLUSION DE BIBLIOTECA PARA DIRECTIVAS OPENMP
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//SOLO PUEDE ESTAR DEFINIDO UNA DE LAS SIGUIENTES DIRECTIVAS
//#define VAR_GLOBAL //REALIZA LOS CALCULOS CON VARIABLES GLOBALES
#define VAR_DYNAMIC //REALIZA LOS CALCULOS CON VARIABLES DINAMICAS

#ifdef VAR_GLOBAL
#define MAX 32768	//=2^15
  double m[MAX][MAX], v[MAX], mv[MAX];
#endif

//FUNCION PRINCIPAL
int main(int argc, char ** argv){
    //VARIABLES PARA EL CALCULO DEL TIEMPO
    double ncgt;

    //PASO 0: COMPROBACION DE ARGUMENTOS
    if(argc < 2){
        printf("ERROR [O] AT %s. NUMERO DE ARGUMENTOS INSUFICIENTE.\n",argv[0]);
        printf("USO: %s [TAM]", argv[0]);
        exit(EXIT_FAILURE);
    }

    //PASO 1: OBTENCION DE DIMENSION
    unsigned int tam = atoi(argv[1]); //OBTENCION DEL TAM DE VECTOR Y MATRIZ
    printf("DIMENSION DE VECTOR Y MATRIZ: %u (%lu B)\n",tam,sizeof(unsigned int));

    //PASO 2: AJUSTE DE DIMENSION (GLOBAL) Y RESERVA DE MEMORIA (DINAMICA)
    #ifdef VAR_GLOBAL
      if(tam > MAX) tam = MAX;
    #endif

    #ifdef VAR_DYNAMIC
      //DEFINICION DE VARIABLES
      double ** m;
      double * v;
      double * mv;

      //RESERVA DE MEMORIA DINAMICA
      v = (double *) malloc(tam * sizeof(double)); //RESERVA DE MEMORIA PARA VECTOR
      mv = (double *) malloc(tam * sizeof(double)); //RESERVA DE MEMORIA PARA MULTIPLICACION DE MATRIZ X VECTOR
      m = (double **) malloc(tam * sizeof(double *)); //RESERVA DE MEMORIA PARA MATRIZ

      //COMPROBAMOS ERRORES DE ASIGNACION DE MEMORIA
      if(v == NULL || mv == NULL || m == NULL){
          printf("ERROR [1] AL RESERVAR MEMORIA PARA MATRIZ Y/O VECTOR.\n");
          exit(EXIT_FAILURE);
      }

      //CONTINUAMOS RESERVANDO MEMORIA PARA MATRIZ
      for(int i=0; i<tam;i++){
        m[i] = (double *) malloc(tam * sizeof(double));
        //COMPROBAMOS ERRORES
        if(m[i] == NULL){
            printf("ERROR [2] AL RESERVAR MEMORIA PARA MATRIZ.\n");
            exit(EXIT_FAILURE);
        }
      }
    #endif

    //VARIABLE AUXILIAR PARA IR CALCULANDO SUMA DE COMPONENTES
    double suma;
    //VARIABLES PARA ALMACENAR TIEMPO
    double t_inicio, t_fin;

    //PASO 3: INICIALIZACION DE VECTOR Y MATRIZ
    for(int i=0; i<tam; i++){
        v[i] = tam*0.1+i*0.1;
        mv[i] = 0;
        #pragma omp parallel for
        for(int j=0; j<tam; j++)
          m[i][j] = tam*0.1+i*0.1-j*0.1;
    }

    //PASO 4: CALCULO DEL PRODUCTO
    t_inicio = omp_get_wtime();
    for(int i = 0; i<tam ; i++){
        suma = 0;
        #pragma omp parallel
        {
            #pragma omp for reduction(+:suma)
            for(int j=0; j<tam; j++){
              suma += m[i][j] * v[j];
            }
            
            mv[i] = suma;
        }
    }
    t_fin = omp_get_wtime();

    //PASO 5: MOSTRAR EL RESULTADO
    if(tam < 10){
        //MATRIZ CREADA
        printf("MATRIZ M: \n");
        for(int i=0; i<tam; i++){
            for(int j=0; j<tam; j++){
                printf("%11.9f \t", m[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        //VECTOR CREADO
        printf("VECTOR V: [");
        for(int i=0; i<tam; i++){
            printf("%11.9f \t", v[i]);
        }
        printf("]\n");

        //RESULTADO MULTIPLICACION MATRIZ X VECTOR
        printf("RESULTADO DE MULTIPLICACION: [");
        for(int i=0; i<tam; i++){
            printf("%11.9f \t", mv[i]);
        }
        printf("]\n");
    }
    else{
        //MATRIZ CREADA
        printf("MATRIZ CREADA: m[0][0]=%11.9f || m[%d][%d]=%11.9f \n", m[0][0],tam-1,tam-1,m[tam-1][tam-1]);
        //VECTOR CREADO
        printf("VECTOR CREADO: v[0]=%11.9f || v[%d]=%11.9f \n", v[0],tam-1,v[tam-1]);
        //RESULTADO MULTIPLICACION MATRIZ X VECTOR
        printf("RESULTADO DE MULTIPLICACION: mv[0]=%11.9f || mv[%d]=%11.9f \n", mv[0], tam-1, mv[tam-1]);
    }

    //PASO 6: CALCULO DEL TIEMPO DE EJECUCION
    ncgt=t_fin - t_inicio;
    printf("TIEMPO DE EJECUCION: %11.9f || DIMENSION: %d \n",ncgt,tam);

    //PASO 7: LIBERACION DE LA MEMORIA DINAMICA EMPLEADA
    #ifdef VAR_DYNAMIC
      free(v);
      free(mv);
      for(int i=0; i<tam; i++)
        free(m[i]);
      free(m);
    #endif

    return EXIT_SUCCESS;
}
