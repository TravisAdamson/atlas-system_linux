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

	cmp BYTE [rdi], 0x00
	je .null_equal
	cmp BYTE [rsi], 0x00
	je .null_not_equal
	jmp .get_next_char

.null_equal:
	cmp BYTE [rsi], 0x00
	je .return_found
	xor rax, rax
	mov rax, -1
	jmp .exit

.null_not_equal:
	xor rax, rax
	mov rax, 1
	jmp .exit

.get_next_char:
	movzx ebx, BYTE [rdi]
	movzx ecx, BYTE [rsi]

.check_null:
	cmp bl, 0x00
	je .check_other_null
	cmp cl, 0x00
	je .greater_than

.remove_char_1_case:
	cmp bl, 65
	jl .remove_char_2_case
	cmp bl, 90
	jg .remove_char_2_case
	add bl, 32

.remove_char_2_case:
	cmp cl, 65
	jl .char_1_v_char_2
	cmp cl, 90
	jg .char_1_v_char_2
	add cl, 32

.char_1_v_char_2:
	cmp bl, cl
	jl .less_than
	jg .greater_than
	inc rdi
	inc rsi
	jmp .get_next_char

.check_other_null:
	cmp cl, 0x00
	je .return_found
	jmp .less_than

.less_than:
	xor rax, rax
	sub bl, cl
	movsx rax, bl
	jmp .exit

.greater_than:
	xor rax, rax
	sub bl, cl
	movzx rax, bl
	jmp .exit

.return_found:
	xor rax, rax

.exit:
	pop rcx
	pop rbx
	pop rbp
	ret
