#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char * argv[]){
    struct timespec cgt1,cgt2; double t;
    

    if (argc < 3){
        printf("FALTAN LOS PARAMETROS N Y M\n");
        exit(-1);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    struct {
        int a[N];
        int b[N];
    } s;

    int R[M];
    int ii; double X1, X2;

     if (N>8 || M>8){
        for ( int i = 0; i < N; i++ ) {
		s.a[i] = drand48();
		s.b[i] = drand48();
	    }
    }else {
        for ( int i = 0; i < N; i++ ) {
            s.a[i] = i;
            s.b[i] = i;
	    }
    }
    
    clock_gettime(CLOCK_REALTIME,&cgt1);
    for(ii = 0; ii<M; ii++){
        X1 = 0; X2 = 0;
        for(int i=0; i<N; i++) X1 += 2*s.a[i]+ii;
        for(int i=0; i<N; i++) X2 += 3*s.b[i]-ii;

        if(X1 < X2) R[ii]=X1; else R[ii] = X2;
    }
    clock_gettime(CLOCK_REALTIME,&cgt2);

  t = (double) (cgt2.tv_sec-cgt1.tv_sec)+
	    (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	
	// Impresión de tiempo de ejecución
	printf("Tiempo (seg): %f\n", t);
	
	
	// Impresión de resultados
	printf("\n__________\nResultados:\n");
	
	printf("\nVector R: \n");
	printf("R[0]=%d R[39999]=%d\n", R[0], R[M-1]);
	
	return 0;
}