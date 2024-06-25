BITS 64

global asm_strncmp
section .text
	;; int asm_strncmp(const char *s1, const char *s2, size_t n)
	;; {
	;;	size_t i = 0;
	;; 	int diff = 0;
	;;	while (*s1 && *s2 && diff == 0 && i < n)
	;; 	{
	;; 		diff = *s1 - *s2;
	;; 	        s1++;
	;; 		s2++;
	;; 		i++;
	;;	}
	;; 	if (diff > 0)
	;; 		return (1);
	;; 	if (diff < 0)
	;; 		return (-1);
	;; 	return (0);
	;; }
asm_strncmp:
	push rbp
	mov rbp, rsp
	mov QWORD [rbp - 24], rdi
	mov QWORD [rbp - 32], rsi
	mov QWORD [rbp - 40], rdx
	mov QWORD [rbp - 8], 0
	mov DWORD [rbp - 12], 0
	jmp .testing_s1_v_s2
.test_loop:
	mov rax, QWORD [rbp - 24]
	movzx eax, BYTE [rax]
	movsx edx, al
	mov rax, QWORD [rbp - 32]
	movzx eax, BYTE [rax]
	movsx eax, al
	sub edx, eax
	mov eax, edx
	mov DWORD [rbp - 12], eax
	add QWORD [rbp - 24], 1
	add QWORD [rbp - 32], 1
	add QWORD [rbp - 8], 1
.testing_s1_v_s2:
	mov rax, QWORD [rbp - 24]
	movzx eax, BYTE [rax]
	test al, al
	jne .testing_diff
	mov rax, QWORD [rbp - 32]
	movzx eax, BYTE [rax]
	test al, al
	je .diff_true
.testing_diff:
	cmp DWORD [rbp - 12], 0
	jne .diff_true
	mov rax, QWORD [rbp - 8]
	cmp rax, QWORD [rbp - 40]
	jb .test_loop
.diff_true:
	cmp DWORD [rbp - 12], 0
	jle .no_diff
	mov eax, 1
	jmp .return
.no_diff:
	cmp DWORD [rbp - 12], 0
	jns .return_0
	mov eax, -1
	jmp .return
.return_0:
	mov eax, 0
.return:
	pop rbp
	ret
