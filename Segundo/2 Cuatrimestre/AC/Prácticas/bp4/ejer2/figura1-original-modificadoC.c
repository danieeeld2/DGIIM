#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Vectores globales
struct bp4{
	int a;
	int b;
};

int main(int argc, char **argv){
	struct timespec cgt1,cgt2; double t;	// para tiempos
	
	int i, ii, X1, X2;
	

    if (argc < 3){
        printf("ERROR EN LOS PARAMETROS\n");
        exit(EXIT_FAILURE);
    }

    int N=atoi(argv[1]);
    int M=atoi(argv[2]);
    
    struct bp4 s[N];
    int R[M];

	if (N>8 || M>8){
        for ( i = 0; i < N; i++ ) {
		s[i].a = drand48();
		s[i].b = drand48();
	    }
    }else {
        for ( i = 0; i < N; i++ ) {
            s[i].a = i;
            s[i].b = i;
	    }
    }
    
    clock_gettime(CLOCK_REALTIME,&cgt1);
    for(ii = 0; ii<M; ii++){
        X1 = 0; X2 = 0;
        for(int i=0; i<N; i+=4){
            X1 += 2*s[i].a+ii;
            X2 += 3*s[i].b-ii;
            X1 += 2*s[i+1].a+ii;
            X2 += 3*s[i+1].b-ii;
            X1 += 2*s[i+2].a+ii;
            X2 += 3*s[i+2].b-ii;
            X1 += 2*s[i+3].a+ii;
            X2 += 3*s[i+3].b-ii;
        }

        if(X1 < X2) R[ii]=X1; else R[ii] = X2;
    }
    clock_gettime(CLOCK_REALTIME,&cgt2);

    t=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
    
    // Impresión de tiempo de ejecución
	printf("Tiempo (seg): %f\n", t);
	
	
	// Impresión de resultados
	printf("\n__________\nResultados:\n");
	
	printf("\nVector R: \n");
	printf("R[0]=%d R[39999]=%d\n", R[0], R[M-1]);
	
	return 0;

}
