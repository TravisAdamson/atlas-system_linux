BITS 64

global asm_strlen

section .text
	;; size_t asm_strlen(const char *str)
	;; {
	;;         size_t len = 0;
	;;         for (; *str; str++)
	;;                 len++;
	;;         return (len);
	;; }

asm_strlen:
	push rbp
	mov rbp, rsp
	mov QWORD [rbp - 24], rdi
	mov QWORD [rbp - 8], 0
	jmp .test_str_stuff
.inc_str_len:
	add QWORD [rbp - 8], 1
	add QWORD [rbp - 24], 1
.test_str_stuff:
	mov rax, QWORD [rbp - 24]
	movzx eax, BYTE [rax]
	test al, al
	jne .inc_str_len
	mov rax, QWORD [rbp - 8]
	pop rbp
	ret
