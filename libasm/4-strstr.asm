BITS 64

global asm_strstr
section .text
	;; char *asm_strstr(const char *haystack, const char *needle)

asm_strstr:
	push rbp
	mov rbp, rsp

.get_first_char:
	movzx ebx, BYTE [rdi]
	movzx eax, BYTE [rsi]
	cmp al, 0x00
	je .return_found

.outter_loop:
	cmp bl, 0x00
	jz .outter_null_found

	cmp bl, al
	je .inner_loop_setup

	inc rdi
	movzx ebx, BYTE [rdi]
	jmp .outter_loop

.inner_loop_setup:
	mov R8, rdi
	mov R9, rsi
	inc R8
	inc R9
	movzx R10D, BYTE [R8]
	movzx R11D, BYTE [r9]
	cmp r10b, r11b
	je .run_inner_loop
	jmp .back_to_outter

.run_inner_loop:
	cmp r10b, 0x00
	jz .inner_null_found
	cmp r11b, 0x00
	jz .return_found

	cmp r10b, r11b
	jne .back_to_outter

	inc R8
	inc R9
	movzx R10D, BYTE [R8]
	movzx R11D, BYTE [R9]
	jmp .run_inner_loop

.back_to_outter:
	inc rdi
	movzx ebx, BYTE [rdi]
	jmp .outter_loop

.outter_null_found:
	cmp al, 0x00
	je .return_found
	jmp .return_0

.inner_null_found:
	cmp r11b, 0x00
	je .return_found
	jmp .return_0

.return_0:
	xor rax, rax
	jmp .exit

.return_found:
	xor rax, rax
	mov rax, rdi
	jmp .exit

.exit:
	pop rbp
	ret
