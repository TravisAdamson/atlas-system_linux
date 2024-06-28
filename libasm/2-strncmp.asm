BITS 64

global asm_strncmp
section .text

asm_strncmp:
    push rbp
    mov rbp, rsp

    ; Arguments:
    ; rdi = first string (S1)
    ; rsi = second string (S2)
    ; rdx = size_t n (number of characters to compare)

    xor eax, eax   ; Initialize eax (return value) to 0
	cmp byte [rdi], 0
	jne .asm_strncmp_loop
	cmp byte [rsi], 0
	jne .asm_strncmp_loop
	jmp .same

    ; Loop through the strings
.asm_strncmp_loop:
    ; Load byte from S1 and S2
    mov al, byte [rdi]
    mov dl, byte [rsi]

    cmp al, dl
    jl .less_than   ; al < dl
    jg .greater_than ; al > dl

	inc eax
	cmp eax, edx
	jg .same

    ; Characters are equal, move to next
    inc rdi
    inc rsi
	cmp BYTE [rdi], 0
	jz .s1_null
	cmp BYTE [rsi], 0
	jz .s2_null
    jmp .asm_strncmp_loop  ; Continue loop

.s1_null:
	cmp dl, 0
	jz .same
	cmp eax, edx
	jge .same
	xor eax, eax
	mov eax, 1
	jmp .exit

.s2_null:
	cmp eax, edx
	jge .same
	xor eax, eax
	mov eax, -1
	jmp .exit

.less_than:
    ; S1 < S2
	cmp edx, eax
	je .same
	cmp BYTE [rdi], 0
	jz .s1_null
	xor eax, eax
    mov eax, -1
    jmp .exit

.greater_than:
    ; S1 > S2
	cmp edx, eax
	je .same
	cmp BYTE [rsi], 0
	jz .s2_null
	xor eax, eax
    mov eax, 1
    jmp .exit

.same:
    ; Strings are equal up to n characters
    xor eax, eax
	mov eax, 0

.exit:
    pop rbp
    ret
