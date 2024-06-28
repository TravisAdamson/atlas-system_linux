BITS 64

global asm_puts
extern asm_strlen

section .text
	;; size_t asm_puts(const char *str)
	;; load stack, call strlen, setup rax value for ret

asm_puts:
	push rbp
	mov rbp, rsp
	push rsi
	push rdx
	mov rsi, rdi

.get_length:
	call asm_strlen

.setup_ret:
	mov rdi, 1
	mov rdx, rax
	mov rax, 1

.call_and_exit:
	SYSCALL
	pop rbp
	pop rdx
	pop rbp
	ret
