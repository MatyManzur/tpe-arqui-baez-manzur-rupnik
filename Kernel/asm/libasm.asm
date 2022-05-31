GLOBAL cpuVendor
GLOBAL getScanCode
GLOBAL swapTasks
GLOBAL initializeTask
GLOBAL saveStackPointer
GLOBAL memdump

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
	push rax
	mov rdx,0
.loop:
	cmp rdx,32
	je .fin
	mov rax,[rdi]
	mov [rsi],rax
	add rdi, 8
	add rsi, 8
	add rdx, 8
	jmp .loop
.fin:
	pop rax
	pop rdx
	ret





