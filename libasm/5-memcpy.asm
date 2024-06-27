BITS 64

global asm_memcpy
section .text
	;; void *asm_memcpy(void *dest, const void *src, size_t n)
asm_memcpy:
    push rbp
    mov rbp, rsp
    mov rdi, rdi
    mov rsi, rsi
    mov rdx, rdx
    test rdi, rdi
    je .return_dest
    test rsi, rsi
    je .return_dest
    mov rcx, rdx
	rep movsb
.return_dest:
    mov rax, rdi
    leave
    ret
