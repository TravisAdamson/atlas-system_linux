BITS 64

global asm_strcasecmp
section .text
	;; int asm_strcasecmp(const char *s1, const char *s2)
	;; load stack, get individual chars to cmp,
	;; convert to lower case if needed
	;; compare, if not equal, return 1, or -1 as needed,
	;; if equal continue, if both reach null then return 0
asm_strcasecmp:
	push rbp
	mov rbp, rsp
	xor rax, rax
	push rcx
	push rbx

.get_next_char:
	movzx ebx, BYTE [rdi]
	movzx ecx, BYTE [rsi]

.check_null:
	cmp bl, 0x00
	jnz .remove_char_1_case
	cmp bl, al
	je .return_found
	jl .less_than
	jg .greater_than

.remove_char_1_case:
	cmp bl, 65
	jl .remove_char_2_case
	cmp bl, 90
	jg .remove_char_2_case
	add bl, 32

.remove_char_2_case:
	cmp al, 65
	jl .char_1_v_char_2
	cmp al, 90
	jg .char_1_v_char_2
	add al, 32
	jmp .char_1_v_char_2

.char_1_v_char_2:
	cmp bl, al
	jl .less_than
	jg .greater_than
	inc rdi
	inc rsi
	jmp .get_next_char

.less_than:
	xor rax, rax
	mov rax, -1
	jmp .exit

.greater_than:
	xor rax, rax
	mov rax, 1
	jmp .exit

.return_found:
	xor rax, rax

.exit:
	pop rbp
	pop rbx
	pop rcx
	ret
