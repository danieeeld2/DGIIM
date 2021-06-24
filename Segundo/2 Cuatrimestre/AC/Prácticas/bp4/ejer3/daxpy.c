#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    if ( argc < 2 ) {
        fprintf(stderr,"Falta num\n");
        exit(-1);
    }
    
    int N = atoi(argv[1]);

    struct timespec ini, fin;
    double tiempo;

    // Creación de vector y matriz
    int i,a=47;
    int x[N], y[N];

    // Inicialización
    for (i=1; i<=N;i++) {
        x[i]=i;
        y[i]=i;
    }
	
    // Cálculo del resultado
    clock_gettime(CLOCK_REALTIME,&ini);

    for ( i=1; i<=N;i++ )
        y[i]=a*x[i]+y[i];

    clock_gettime(CLOCK_REALTIME,&fin);
    
    
    
    tiempo=(double) (fin.tv_sec-ini.tv_sec)+(double) ((fin.tv_nsec-ini.tv_nsec)/(1.e+9));

    // Resultados
    printf("Tiempo(seg): %f\ny[0]=%d, y[N-1]=%d \n", tiempo, y[0], y[N-1]);
}