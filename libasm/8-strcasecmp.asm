BITS 64

global asm_strcasecmp
section .text
	;; int asm_strcasecmp(const char *s1, const char *s2)
	;; load stack, get individual chars to cmp,
	;; convert to lower case if needed
	;; compare, if not equal, return 1, or -1 as needed,
	;; if equal continue, if both reach  null then return 0
asm_strcasecmp:
	push rbp
	mov rbp, rsp
	xor rax, rax
	push rbx
	push rcx

.get_next_char:
	mov bl, BYTE [rdi]
	mov cl, BYTE [rsi]

.check_null:
	cmp bl, 0x00
	jnz .remove_char_1_case
	cmp cl, 0x00
	jnz .remove_char_2_case
	jmp .not_equals

.remove_char_1_case:
	cmp bl, 65
	jl .remove_char_2_case
	cmp bl, 90
	jg .remove_char_2_case
	add bx, 32
	jmp .remove_char_2_case

.remove_char_2_case:
	cmp cl, 65
	jl .char_1_v_char_2
	cmp cl, 90
	jg .char_1_v_char_2
	add cx, 32
	jmp .char_1_v_char_2

.char_1_v_char_2:
	cmp bl, cl
	jnz .not_equals
	inc rdi
	inc rsi
	jmp .get_next_char

.not_equals:
	sub rbx, rcx
	mov rax, rbx
	jmp .exit

.return_found:
	xor rax, rax

.exit:
	pop rcx
	pop rbx
	pop rbp
	ret
