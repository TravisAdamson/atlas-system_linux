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
	cmp cl, 0x00
	jnz .remove_char_2_case
	jmp .exit

.remove_char_1_case:
	cmp bl, 65
	jl .char_1_v_char_2
	cmp bl, 90
	jg
