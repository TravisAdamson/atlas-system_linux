BITS 64

global asm_putc
section .text
	;; size_t asm_putc(int c)

asm_putc:
	push rbp
	mov rbp, rsp
	push rdi

.syscall_setup:
	mov rsi, rsp
	mov rdx, 1
	mov rax, 1
	SYSCALL

.exit:
	pop rdi
	pop rbp
	ret
