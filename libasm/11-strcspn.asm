BITS 64

global asm_strcspn
section .text
	;; size_t asm_strspn(const char *s, const char *accept)

asm_strcspn:
	push rbp
	mov rbp, rsp
	xor rax, rax
	mov rbx, rdi
	mov rcx, rsi

.setup_loops:
	movzx r8d, BYTE [rbx]
	movzx r9d, BYTE [rcx]
	cmp r8b, 0x00
	je .end
	cmp r9b, 0x00
	je .end

.outter_loop:
	cmp r8b, r9b
	je .end
	inc rcx
	movzx r9d, BYTE [rcx]
	cmp r9b, 0x00
	je .accept
	jmp .outter_loop

.accept:
	inc rax
	inc rbx
	mov rcx, rsi
	jmp .setup_loops

.end:
	pop rbp
	ret
