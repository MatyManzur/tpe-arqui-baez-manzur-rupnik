GLOBAL cpuVendor
GLOBAL getScanCode
GLOBAL swapTasks
GLOBAL initializeTask
GLOBAL saveStackPointer

section .text

getScanCode:			;Waits until something happens in the keyboard and returns that key
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
