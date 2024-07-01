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
	cmp BYTE [rsi], 0x00
	je .no_reject

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

.no_reject:
	mov rax, rdi
	jmp .end

.end:
	pop rbp
	ret
