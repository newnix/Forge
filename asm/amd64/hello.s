section .data
	message db "Hello, world",0xa ; Create a static string with a trailing newline
	len equ $ - message ; somehow compute the length of the above string

section .text
	global _start

_start:
	mov rax,4 ; puts 4 in rax, a general purpose register
	mov rdi,1 ; puts 1 in rdi, a "destination index" register, which is passed as parameter 1 to functions
	mov rsi,message ; put the message in rsi, which is treated as parameter 2 in functions
	mov	rdx,len ; put the length of message in rdx, which is parameter 3 
	syscall ; call the function described by rax, which in this case is write(2)
	mov rbx,0 ; this is apparently a base pointer, I'm not sure that this is necessary for the hello world example
	mov rdi,0 ; put 0 in rdi, which will become our return code
	mov rax,1 ; put 1 in rax
	syscall ; call the function described by rax, which is now exit(3)
	;;
	;; this is basically 
	;;
	;; int main() { 
	;;  char *message="Hello, world\n";
	;;	write(1,message,strlen(message));
	;;	exit(0);
	;; }
