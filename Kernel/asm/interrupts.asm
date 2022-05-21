
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _syscallHandler

GLOBAL _exception0Handler

EXTERN irqDispatcher
EXTERN exceptionDispatcher

EXTERN printChar
EXTERN print
EXTERN newLine
EXTERN clearScreen
EXTERN getCursor
EXTERN setCursor

EXTERN readPrintables
EXTERN getNextKey
EXTERN cleanBuffer

EXTERN getCurrentDateTime
EXTERN setTimeZone
EXTERN ticks_elapsed
EXTERN seconds_elapsed

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0


;syscallHandler calls the function in c with its respective arguments
;The arguments already come in its respective registers in order from C
_syscallHandler:
	push rbp
	mov rbp,rsp
.C10:
	cmp rax,10
	jne .C11
	call printChar
	jmp .end
.C11:
	cmp rax,11
	jne .C12
	call print
	jmp .end
.C12:
	cmp rax,12
	jne .C13
	call newLine
	jmp .end
.C13:
	cmp rax,13
	jne .C14
	call clearScreen
	jmp .end
.C14:
	cmp rax,14
	jne .C15
	call getCursor
	jmp .end
.C15:
	cmp rax,15
	jne .C20
	call setCursor
	jmp .end
.C20:
	cmp rax,20
	jne .C21
	call readPrintables
	jmp .end
	
.C21:
	cmp rax,21
	jne .C22
	call getNextKey
	jmp .end
	
.C22:
	cmp rax,22
	jne .C30
	call cleanBuffer
	jmp .end
.C30:
	cmp rax,30
	jne .C31
	call getCurrentDateTime
	jmp .end
.C31:
	cmp rax,31
	jne .C32
	call setTimeZone
	jmp .end
.C32:
	cmp rax,32
	jne .C33
	call ticks_elapsed
	jmp .end
.C33
	cmp rax,33
	jne .default
	call seconds_elapsed
	jmp .end
	
.default:
	jmp .end
	
.end
	mov rsp,rbp
	pop rbp
	iretq


haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1
