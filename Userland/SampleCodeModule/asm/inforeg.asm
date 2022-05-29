GLOBAL inforegisters
GLOBAL invalidOpcode

SECTION .text

invalidOpcode:
	ud2
	ret

inforegisters:
	mov [registers],    rax
	mov [registers+8],  rbx
	mov [registers+16], rcx
	mov [registers+24], rdx
	mov [registers+32], rsi
	mov [registers+40], rdi
	mov [registers+48], r8
	mov [registers+56], r9
	mov [registers+64], r10
	mov [registers+72], r11
	mov [registers+80], r12
	mov [registers+88], r13
	mov [registers+96], r14
	mov [registers+104], r15
	mov rax, [rbp]
	mov [registers+112], rax 	;la direccion de retorno es la instruccion de donde se llamo printRegisters()
	mov [registers+120], rbp
	mov [registers+128], rsp
	pushfq
	pop rax
	mov [registers+136], rax
	mov rax, registers
	ret
	
SECTION .bss

registers resq 18
