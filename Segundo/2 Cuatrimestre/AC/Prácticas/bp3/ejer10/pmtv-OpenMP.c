
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_num_threads() 0
#endif

#define VAR_DYNAMIC 

int main(int argc, char ** argv){
    if(argc < 2){
        printf("ERROR [O] AT %s. NUMERO DE ARGUMENTOS INSUFICIENTE.\n",argv[0]);
        printf("USO: %s [TAM]", argv[0]);
        exit(EXIT_FAILURE);
    }

    unsigned int tam = atoi(argv[1]); //OBTENCION DEL TAM DE VECTOR Y MATRIZ
    printf("DIMENSION DE VECTOR Y MATRIZ: %u (%lu B)\n",tam,sizeof(unsigned int));

    #ifdef VAR_DYNAMIC
      double ** m;
      double * v;
      double * mv;

      v = (double *) malloc(tam * sizeof(double)); //RESERVA DE MEMORIA PARA VECTOR
      mv = (double *) malloc(tam * sizeof(double)); //RESERVA DE MEMORIA PARA MULTIPLICACION DE MATRIZ X VECTOR
      m = (double **) malloc(tam * sizeof(double *)); //RESERVA DE MEMORIA PARA MATRIZ

      if(v == NULL || mv == NULL || m == NULL){
          printf("ERROR [1] AL RESERVAR MEMORIA PARA MATRIZ Y/O VECTOR.\n");
          exit(EXIT_FAILURE);
      }

      for(int i=0; i<tam;i++){
        m[i] = (double *) malloc(tam * sizeof(double));
        if(m[i] == NULL){
            printf("ERROR [2] AL RESERVAR MEMORIA PARA MATRIZ.\n");
            exit(EXIT_FAILURE);
        }
      }
    #endif

    for(int i=0; i<tam; i++){
        v[i] = tam*0.1+i*0.1;
        mv[i] = 0;
        for(int j=0; j<tam; j++){
          if(i>j)
            m[i][j] = 0;
          else
            m[i][j] = tam*0.1+i*0.1-j*0.1;
        }
    }

    omp_sched_t kind; int chunk_value;

    double ncgt, t_inicial, t_final;

    double suma;

    #pragma omp parallel
    {
      #pragma omp single
        t_inicial = omp_get_wtime();

      #pragma omp for firstprivate(suma) schedule(runtime)
      for(int i = 0; i<tam ; i++){
          #ifdef SEE_CHUNK_DEFAULT
            if(i==0){
                omp_get_schedule(&kind,&chunk_value);
                printf("KIND: %d | CHUNK: %d \n",kind,chunk_value);
            }
          #endif

          suma = 0;
          for(int j=i; j<tam; j++){
              suma += m[i][j] * v[j];
          }
          mv[i] = suma;
      }

      #pragma omp single
        t_final = omp_get_wtime();
    }

    ncgt=t_final - t_inicial;
    printf("TIEMPO DE EJECUCION: %11.9f || DIMENSION: %d \n",ncgt,tam);

    #ifdef VAR_DYNAMIC
      free(v);
      free(mv);
      for(int i=0; i<tam; i++)
        free(m[i]);
      free(m);
    #endif

    return EXIT_SUCCESS;
}
