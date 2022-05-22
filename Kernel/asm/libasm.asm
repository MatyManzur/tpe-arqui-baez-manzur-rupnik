GLOBAL cpuVendor
GLOBAL getScanCode
GLOBAL swapTasks
GLOBAL initializeTask

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
	push rbp
	mov [rdi], rsp
	pop rbp
	ret
	
swapTasks:
	push rbp
	mov rsp, rdi
	pop rbp
	ret

initializeTask:
	mov rsp, rsi
	
	push rax
	mov al, 20h			
	out 20h, al
	pop rax
	
	call rdi
	ret
