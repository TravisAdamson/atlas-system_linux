BITS 64

global asm_strpbrk
section .text
	;; char *asm_strpbrk(const char *s, const char *accept);

asm_strpbrk:
	push rbp
	mov rbp, rsp
	xor rax, rax
	mov rbx, rdi
	mov rcx, rsi

.setup_loops:
	movzx r8d, BYTE [rbx]
	movzx r9d, BYTE [rcx]
	cmp r8b, 0x00
	je .return_0
	cmp r9b, 0x00
	je .reset

.check:
	cmp r8b, r9b
	je .return_result
	inc rcx
	jmp .setup_loops

.reset:
	mov rcx, rsi
	inc rbx
	jmp .setup_loops

.return_result:
	mov rax, rbx
	jmp .end

.return_0:
	xor rax, rax
	jmp .end

.end:
	pop rbp
	ret
