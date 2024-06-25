BITS 64

global asm_strchr
section .text
	;; char *asm_strchr(const char *s, int c)
	;; {
	;; 	char *temp = (char *)s;
	;;	while (*temp)
	;; 	{
	;;	 	if (*temp == c)
	;; 			return (temp);
	;; 		temp++;
	;;	}
	;; 	if (c == 0)
	;; 		return (temp);
	;; 	return (NULL);
	;; }
asm_strchr:
	push rbp
	mov rbp, rsp
	mov QWORD [rbp - 24], rdi
	mov DWORD [rbp - 28], esi
	mov rax, QWORD [rbp - 24]
	mov QWORD [rbp - 8], rax
	jmp .testing_loop_test
.testing_loop:
	mov rax, QWORD [rbp - 8]
	movzx eax, BYTE [rax]
	movsx eax, al
	cmp eax, DWORD [rbp - 28]
	jne .inbound
	mov rax, QWORD [rbp - 8]
	jmp .return
.inbound:
	add QWORD [rbp - 8], 1
.testing_loop_test:
	mov rax, QWORD [rbp - 8]
	movzx eax, BYTE [rax]
	test al, al
	jne .testing_loop
	cmp DWORD [rbp - 28], 0
	jne .return_empty
	mov rax, QWORD [rbp - 8]
	jmp .return
.return_empty:
	mov eax, 0
.return:
	pop rbp
	ret
