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

    ; Loop through the strings
.asm_strncmp_loop:
    ; Load byte from S1 and S2
    mov al, byte [rdi]
    mov dl, byte [rsi]

	test al, 0
	je .less_than
	test dl, 0
	je .greater_than
    cmp al, dl
    jl .less_than   ; al < dl
    jg .greater_than ; al > dl

	inc eax
	cmp eax, edx
	jg .same

    ; Characters are equal, move to next
    inc rdi
    inc rsi
    jmp .asm_strncmp_loop  ; Continue loop

.less_than:
    ; S1 < S2
	cmp edx, eax
	jle .same
	xor eax, eax
    mov eax, -1
    jmp .exit

.greater_than:
    ; S1 > S2
	cmp edx, eax
	je .same
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
