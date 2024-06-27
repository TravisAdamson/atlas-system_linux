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
	mov QWORD [rbp - 40], rdi
	mov QWORD [rbp - 48], rsi
	mov QWORD [rbp - 56], rdx
	mov rax, QWORD [rbp - 40]
	mov QWORD [rbp - 16], rax
	mov rax, QWORD [rbp - 48]
	mov QWORD [rbp - 24], rax
	cmp QWORD [rbp - 16], 0
	je .destination
	cmp QWORD [rbp - 24], 0
	jne .setup_loop
.destination:
	mov rax, QWORD [rbp - 40]
	jmp .return
.setup_loop:
	mov QWORD [rbp - 8], 0
	jmp .loop_test
.run_loop:
	mov rax, QWORD [rbp - 8]
	mov rdx, QWORD [rbp - 16]
	add rdx, rax
	mov rax, QWORD [rbp - 8]
	mov rcx, QWORD [rbp - 8]
	add rax, rcx
	movzx eax, BYTE [rax]
	mov BYTE [rdx], al
	add QWORD [rbp - 8], 1
.loop_test:
	mov rax, QWORD [rbp - 8]
	cmp rax, QWORD [rbp - 56]
	jb .run_loop
	mov rax, QWORD [rbp - 40]
.return:
	pop rbp
	ret
