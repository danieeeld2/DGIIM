/* Incluir asm de forma genérica en un código de C */

// Tenemos nuestro código en C

int lista[] = {1, 2, 10,  1,2,0b10,  1,2,0x10};
int longlista = sizeof(lista)/sizeof(int);
int resultado = 0;

int suma(int *array, int len){
	/* Código en C:
		int i, res = 0;
		for(int i=0; i<len; i++)
			res += array[i];
		return res;
	*/

	/* En este primer caso, incluimos el código en ensamblador de forma básica,
	   es decir, incluimos el código sin especificar registros y haciendo toda la 
	   función en asm
	*/

	asm("   xor %eax, %eax                 \n\t"	// Ponemos registro a 0
		"   xor %edx, %edx             \n\t"	// Ponemos registro a 0
		"0: cmp %edx, %esi             \n\t"	// Comparamos los dos registros
		"   je  if                     \n\t"	// Salta si vale 0, es decir edx = esi
		"   add (%rdi, %rdx, 4), %eax  \n\t"	// Suma el nuevo elemento
		"   inc %edx                   \n\t"	// Incrementa el registro en uno
		"   jmp 0b                     \n\t"	// Vuelve a 0: cmp
		"1:                            \n\t"	// Sale de la función
		);
}

int main(){
	resultado = suma(lista, longlista);
}
