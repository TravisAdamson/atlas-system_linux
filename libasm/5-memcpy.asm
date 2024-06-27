BITS 64

global asm_memcpy
section .text
	;; void *asm_memcpy(void *dest, const void *src, size_t n)
	;; {
	;; 	size_t i;
	;; 	unsigned char *_dest = (unsigned char *)dest;
	;; 	unsigned char *_src = (unsigned char *)src;
	;;
	;; 	if (!_dest || !_src)
	;; 		return (dest);
	;;
	;;	for (i = 0; i < n; i++)
	;; 	{
	;; 		*(_dest + i) = *(_src + i);
	;; 	}
	;;
	;; 	return (dest);
	;; }
asm_memcpy:
    push rbp
    mov rbp, rsp
	mov rdi, rdi
    mov rsi, rsi
    mov rdx, rdx
	test rdi, rdi
    je .destination
    test rsi, rsi
    je .destination
    test rdx, rdx
    jz .destination
.run_loop:
    mov al, [rsi]
    mov [rdi], al
    inc rsi
    inc rdi
    dec rdx
    jnz .run_loop
.destination:
    mov rax, rdi
    leave
    ret
