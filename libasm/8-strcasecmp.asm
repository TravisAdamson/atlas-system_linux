BITS 64

    global asm_strcasecmp  ; EXPORT function

    section .text

    ; int asm_strcasecmp(const char *s1, const char *s2);

asm_strcasecmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start
    push rbx
    push rcx

asm_strcasecmp_next:
	movzx ebx, BYTE [rdi]
	movzx ecx, BYTE [rsi]
    cmp bl, 0x00
    jnz asm_strcasecmp_bl_cnvt
    cmp cl, 0x00
    jnz asm_strcasecmp_cl_cnvt
    jmp asm_strcasecmp_ne

asm_strcasecmp_bl_cnvt:
    cmp bl, 65 ; compares char to 'A'
    jl asm_strcasecmp_cl_cnvt ; if less, is not a letter
    cmp bl, 90 ;  compares char to 'Z'
    jg asm_strcasecmp_cl_cnvt ; if greater is already lowercase, or not a letter
    add bx, 32 ; changes letter to lowercase
    jmp asm_strcasecmp_cl_cnvt

asm_strcasecmp_cl_cnvt:
    cmp cl, 65 ; compares char to 'A'
    jl asm_strcasecmp_cmp ; if less, is not a letter
    cmp cl, 90 ;  compares char to 'Z'
    jg asm_strcasecmp_cmp ; if greater is already lowercase, or not a letter
    add cx, 32 ; changes letter to lowercase
    jmp asm_strcasecmp_cmp

asm_strcasecmp_cmp:
    cmp bl, cl ; checks if bytes are same
    jnz asm_strcasecmp_ne ; jumps to end for positive diff
    inc rdi
    inc rsi ; incrementing strings
    jmp asm_strcasecmp_next; Loop

asm_strcasecmp_ne:
    sub rbx, rcx
    mov rax, rbx

    pop rcx
    pop rbx
    pop rbp
    ret ; exit
