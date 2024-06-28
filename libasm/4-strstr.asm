BITS 64

global asm_strstr
section .text
	;; char *asm_strstr(const char *haystack, const char *needle)
	;; {
	;; 	char *hs = (char *)haystack, *ndl = (char *)needle,
	;; 		*temp = NULL;
	;; 	if (!*ndl)
	;; 		return (hs);
	;;	for (; *hs; hs++)
	;; 	{
	;;		for (temp = ndl; *temp; temp++)
	;; 		{
	;; 			if (*temp != *(hs + (temp - ndl)))
	;;				break;
	;; 		}
	;; 		if (!*temp)
	;;              	return (hs);
	;; 	}
	;;	return (NULL);
	;; }
asm_strstr:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rdi, rdi
    mov rsi, rsi
    mov [rbp-8], rdi
    mov [rbp-16], rsi
    mov rax, [rbp-16]
    movzx eax, byte [rax]
    test al, al
    je .return_haystack
.haystack_loop:
    mov rdi, [rbp-8]
    mov rsi, [rbp-16]
    mov rcx, rdi
.needle_loop:
    mov al, byte [rsi]
    mov dl, byte [rdi]
    test al, al
    je .found
    test dl, dl
    je .not_found
    cmp al, dl
    jne .next_char
    inc rsi
    inc rdi
    jmp .needle_loop
.next_char:
    mov rdi, [rbp-8]
    inc rdi
    mov [rbp-8], rdi
    mov al, byte [rdi]
    test al, al
    jne .haystack_loop
.not_found:
    xor eax, eax
    jmp .cleanup
.found:
    mov rax, rcx
.return_haystack:
    mov rax, [rbp-8]
.cleanup:
    leave
    ret
