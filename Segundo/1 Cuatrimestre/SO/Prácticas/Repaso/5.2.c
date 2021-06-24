/*
 reciboSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada sigaction para cambiar el comportamiento del proceso       
 frente a la recepción de una señal.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static void sig_USR_hdlr(int sigNum)
  {

    if(sigNum == SIGUSR1)
    printf("\nRecibida la senal SIGUSR1\n\n");
    else if(sigNum == SIGUSR2)
    printf("\nRecibida la senal SIGUSR2\n\n"); 
   }

int main(int argc, char *argv[])
   {
    struct sigaction sig_USR_nact;
    if(setvbuf(stdout,NULL,_IONBF,0)) 
       {    perror("\nError en setvbuf");
       }

//Inicializar la estructura sig_USR_na para especificar la nueva acción para la señal.

sig_USR_nact.sa_handler= sig_USR_hdlr;


//'sigemptyset' inicia el conjunto de señales dado al conjunto vacio. 

sigemptyset (&sig_USR_nact.sa_mask);
sig_USR_nact.sa_flags = 0;

//Establecer mi manejador particular de señales para SIGUSR1
if( sigaction(SIGUSR1,&sig_USR_nact,NULL) <0) 
    {
  perror("\nError al intentar establecer el manejador de senal para SIGUSR1");
  exit(EXIT_FAILURE);
    }
//Establecer mi manejador particular de señal para SIGUSR2
if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0) 
    {
  perror("\nError al intentar establecer el manejador de senal para SIGUSR2");
  exit(EXIT_FAILURE);
    }
for(;;)
   {
   }
}

/*  El programa comienza creando una struct signation, para pasar a desactivar el buffer
    de la salida estándar. A continuación,pasa a inicializar la estructura sig_USR_na 
    para especificar la nueva acción para la señal. Después, llama a 'sigemptyset', el cual,
    inicia el conjunto de señales dado al conjunto vacio y, por último, inicializa los flags a 0.
    Por último, llama a sigaction, el cual, permite cambiar la acción tomada
    por un proceso cuando recibe una señal. En ambos casos, comprueba si el manejador 
    falla, en cuyo caso, muestra un mensaje de error por pantalla y finaliza el
    programa
    struct sigaction{
        void (*sa_handler)(int);
        void (*sa_sigaction)(int, siginfo_t*, void *);
        sigset_tsa_mask;
        int sa_flags;
        void (*sa_restorer)(void);
    }
    NAME
       sigaction, rt_sigaction - examine and change a signal action
    SYNOPSIS
       #include <signal.h>
       int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);
       The  sigaction()  system  call  is used to change the action taken by a
       process on receipt of a specific signal.  (See signal(7) for  an  over‐
       view of signals.)
       signum  specifies the signal and can be any valid signal except SIGKILL
       and SIGSTOP.
       If act is non-NULL, the new action for signal signum is installed  from
       act.  If oldact is non-NULL, the previous action is saved in oldact.
  */
