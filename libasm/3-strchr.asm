BITS 64

global asm_strchr
section .text
	;; char *asm_strchr(const char *s, int c);

asm_strchr:
	push rbp
	mov rbp, rsp

.get_next_char:
	movzx ebx, BYTE [rdi]
	mov eax, esi

.run_loop:
	cmp bl, 0x00
	jz .null_found

	cmp bl, al
	je .return_found

	inc rdi
	movzx ebx, BYTE [rdi]
	jmp .run_loop

.null_found:
	cmp al, 0x00
	jz .return_found
	xor rax, rax
	jmp .exit

.return_found:
	xor rax, rax
	mov rax, rdi

.exit:
	pop rbp
	ret
