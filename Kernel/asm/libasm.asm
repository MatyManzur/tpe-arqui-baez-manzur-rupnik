GLOBAL cpuVendor
GLOBAL getScanCode
GLOBAL swapTasks
GLOBAL initializeTask
GLOBAL saveStackPointer
GLOBAL memdump
GLOBAL inforegisters

section .text

getScanCode:
	push rbp
	mov rbp, rsp
	
	mov rax,0
loop:    
	in al,0x64
	mov cl,al
        and al,0x01
        cmp al,0
        je loop
        
        in al,0x60
        
        mov rsp, rbp
        pop rbp
        ret
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
	
saveStackPointer:
	mov [rdi], rbp
	ret
	
swapTasks:
	mov rsp, rdi  ;; Por como usamos saveStackPointer en rdi apunta al rbp de TimerHandler entonces lo popeamos para no perderlo 
				;;y volvemos a timer handler es como hacer un desarmado de stack a mano
	pop rbp
	ret

initializeTask:
	mov rsp, rcx	;;movemos el rsp
	
	push rax	;;EOI
	mov al, 20h			
	out 20h, al
	pop rax
	
	call rdx	;;en rdi y rsi ya tenemos los argumentos de la funcion, llamamos a la funcion
	ret
	
;Desde C nos deberian pasar por argumentos primero la direccion de memoria y despues una direccion a un array para dejar los 32bytes
memdump:
	push rdx
	mov rdx,0
.loop:
	cmp rdx,32
	je .normal
	cmp rdi,7fffffffh
	jg .error
	mov rax,[rdi]
	mov [rsi],rax
	add rdi, 8
	add rsi, 8
	add rdx, 8
	jmp .loop
.normal:
	mov rax,1
	jmp .fin
.error:
	mov rax,-1
.fin:
	pop rdx
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





