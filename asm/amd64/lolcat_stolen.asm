section .data
	char_buffer db 0

section .text
	global _start

_start:
	mov r12, 0
	.loop:
		call read_char
		mov rdi, rax
		cmp rdi, 0
		je .end
		call put_char
		mov rdi, r12
		call set_color
		inc r12
	jmp .loop
	.end:
		call exit

read_char:
	mov rax, 0
	mov rdi, 0
	mov rsi, char_buffer
	mov rdx, 1
	syscall
	cmp eax, 0
	jg .success
	mov rax, 0
	ret
	.success:
		mov rax, [char_buffer]
		ret

put_char:
	mov [char_buffer], rdi
	mov rax, 1
	mov rdi, 1
	mov rsi, char_buffer
	mov rdx, 1
	syscall
	ret

set_color:
	push rdi
	mov rdi, 27
	mov rdi, '['
	call put_char
	pop rdi
	mov rax, rdi
	mov rdi, 6
	div rdi
	mov rdi, '0'
	inc rdx
	add rdi, rdx
	call put_char
	mov rdi, ';'
	call put_char
	mov rdi, '1'
	call put_char
	mov rdi, 'm'
	call put_char
	ret

exit:
	mov rax, 60
	syscall
