// gcc -Og bomba.c -o bomba -no-pie -fno-guess-branch-probability

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 5

char password[]="abracadabra\n";	// contraseña
int  passcode  = 7777;			// pin

void boom(void){
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"·························\n"
		"··· bomba desactivada ···\n"
		"·························\n"
		"\n");
	exit(0);
}

// Función para encriptar password
void transform1(void){
	char *newpassword;
	newpassword = malloc(strlen(password)*sizeof(char));
	int i;
	for(i=strlen(password); i!=0; i--){
		newpassword[strlen(password)-i] = password[i];
	}
	for(i=0; i<strlen(password); i++){
		if(i%2==0)
			password[i]+=3;
		else
			password[i]-=2;
	}
	free(newpassword);
}

char* transform11(char s[]){
	char *newpassword;
	newpassword = malloc(strlen(s)*sizeof(char));
	int i;
	for(i=strlen(s); i!=0; i--){
		newpassword[strlen(s)-i] = s[i];
	}
	for(i=0; i<strlen(s); i++){
		if(i%2==0)
			s[i]+=3;
		else
			s[i]-=2;
	}
	free(newpassword);
	return s;
}

// Función para encriptar passcode
void transform2(void){
	passcode+=(strlen(password)-19)-(sizeof(char)-sizeof(int));
}

int transform22(int a){
	a+=(strlen(password)-19)-(sizeof(char)-sizeof(int));
	return a;
}


int main(){
	char pw[SIZE];
	int  pc, n;

	transform1();

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseña: ");
	while (	fgets(pw, SIZE, stdin) == NULL );
	if    (	strncmp(transform11(pw),password,sizeof(password)) )
	    boom();

	transform2();
	printf("%s\n%d\n", password, passcode);

	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );
	if    (	transform22(pc) != passcode )
	    boom();

	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	defused();
}
