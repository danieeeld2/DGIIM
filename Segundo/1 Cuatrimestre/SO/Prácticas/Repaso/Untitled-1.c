#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
int cont=1,leidos;
int filein,fileout;
char cadena[30];
char cad_bloque[40];
char salto_linea[2]="\n";
char caracter[1];
int num_char = 1;
if (argc==2)
{
filein=open(argv[1], O_RDONLY);
}
else{
filein=STDIN_FILENO;
}
fileout=open("archivo_salida", O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
if (fileout < 0){
printf("El fichero de salida no se pudo abrir correctamente\n");
exit(-1);
}
while((leidos=read(filein,caracter,1))!=0){
if (num_char == 1 || num_char%80 == 0){
if (num_char != 1)
write(fileout, salto_linea, strlen(salto_linea));
else{
sprintf(cad_bloque, "El numero de bloques es <%d>\n",cont);
write(fileout, cad_bloque, strlen(cad_bloque));
}
sprintf(cad_bloque, "%s%d\n", "Bloque", cont);
write(fileout, cad_bloque, strlen(cad_bloque));
cont++;
}
write(fileout, caracter, 1);
num_char++;
}
sprintf(cad_bloque, "El numero de bloques es <%d>\n", cont);
lseek(fileout,0,SEEK_SET);
write(fileout, cad_bloque, strlen(cad_bloque));
close(filein);
close(fileout);
return 0;
}