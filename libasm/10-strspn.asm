BITS 64

global asm_strspn
section .text
	;; size_t asm_strspn(const char *s, const char *accept)

asm_strspn:
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
	je .accept
	inc rcx
	movzx r9d, BYTE [rcx]
	cmp r9b, 0x00
	je .return_result
	jmp .outter_loop

.accept:
	inc rax
	inc rbx
	mov rcx, rsi
	jmp .setup_loops

.return_result:
	jmp .end

.return_0:
	xor rax, rax
	jmp .end

.end:
	pop rbp
	ret
