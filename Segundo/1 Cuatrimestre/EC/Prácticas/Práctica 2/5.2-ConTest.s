.section .data
#ifndef TEST
#endif
	.macro linea
#if TEST==1
	.int 1, 1, 1, 1
#elif TEST==2
	.int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
#elif TEST==3
	.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==4
	.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
#elif TEST==5
	.int -1, -1, -1, -1
#elif TEST==6
	.int 200000000, 200000000, 200000000, 200000000
#elif TEST==7
	.int 300000000, 300000000, 300000000, 300000000
#elif TEST==8
	.int 5000000000, 5000000000, 5000000000, 5000000000
#else
	.error "Definir TEST valido"
#endif
	.endm
			
	lista:		.irpc i,1234
			linea
			.endr

	longlista:	.int (.-lista)/4
	resultado:	.quad   0
  	formato: 	
  			.ascii "resultado \t =   %18lu (uns)\n"
  			.ascii "\t\t = 0x%18lx (hex)\n"
  			.asciz "\t\t = 0x %08x %08x\n"
  	
.section .text
_start: .global _start

	call trabajar	 
	call imprim_C	 
	call acabar_C	 
	ret

trabajar:
	mov     $lista, %rdi
	mov  longlista, %esi
	call suma		
	mov  %eax, resultado
	mov  %edx, resultado+4		 
	ret

suma:
	xor %eax, %eax			 
	xor %ecx, %ecx			 
	xor %edx, %edx			 
.Lbucle:
	cmp %rcx, %rsi			 
	je .Lfin			 
	add (%rdi,%rcx,4), %eax		 
	adc $0, %edx			 
	inc %rcx			 
	jmp .Lbucle			 
.Lfin:
	ret			

imprim_C:			 
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	xor   %eax, %eax	
	call  printf		 
	ret


acabar_C:			 
	mov  resultado, %edi
	call _exit		 
	ret
