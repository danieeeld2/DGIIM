#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t new_mask;
    
    // vaciamos la máscara
    sigemptyset(&new_mask);	// Inicializa a vacío un conjunto de señales
    
    // rellenamos la máscara con todas las señales
    sigfillset(&new_mask);	// Inicializa un conjunto con todas las señales
    
    // eliminamos SIGUSR1
    sigaddset(&new_mask, SIGUSR1);	// Añade una señal a un cojunto de señales set previamente inicializado
    
    // cuando suspendamos el programa no reaccionará a ninguna señal excepto SIGUSR1
    sigsuspend(&new_mask);
}

/*	SIGSUSPEND(2)              Linux Programmer's Manual             SIGSUSPEND(2)

	NAME
       sigsuspend, rt_sigsuspend - wait for a signal

	SYNOPSIS
       #include <signal.h>

       int sigsuspend(const sigset_t *mask);

   	   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       sigsuspend(): _POSIX_C_SOURCE

	DESCRIPTION
       sigsuspend() temporarily replaces the signal mask of the calling thread
       with the mask given by mask and then suspends the thread until delivery
       of  a signal whose action is to invoke a signal handler or to terminate
       a process.

       If the signal terminates the process, then sigsuspend()  does  not  re‐
       turn.   If  the  signal  is caught, then sigsuspend() returns after the
       signal handler returns, and the signal mask is restored  to  the  state
       before the call to sigsuspend().

       It  is  not possible to block SIGKILL or SIGSTOP; specifying these sig‐
       nals in mask, has no effect on the thread's signal mask.

   RETURN VALUE
       sigsuspend() always returns -1, with errno set to  indicate  the  error
       (normally, EINTR).

  SIGSETOPS(3)               Linux Programmer's Manual              SIGSETOPS(3)

  NAME
       sigemptyset, sigfillset, sigaddset, sigdelset, sigismember - POSIX sig‐
       nal set operations

  SYNOPSIS
       #include <signal.h>

       int sigemptyset(sigset_t *set);

       int sigfillset(sigset_t *set);

       int sigaddset(sigset_t *set, int signum);

       int sigdelset(sigset_t *set, int signum);

       int sigismember(const sigset_t *set, int signum);

  DESCRIPTION
       These functions allow the manipulation of POSIX signal sets.

       sigemptyset() initializes the signal set given by set  to  empty,  with
       all signals excluded from the set.

       sigfillset() initializes set to full, including all signals.

       sigaddset()  and  sigdelset() add and delete respectively signal signum
       from set.

       sigismember() tests whether signum is a member of set.
*/

