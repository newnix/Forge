lolcat:
	yasm -f elf64 -o lolcat.o lolcat.asm
	ld -o lolcat lolcat.o

lolcat-c:
	clang-devel -S lolcat.c -o lolcat-c.asm
	clang-devel -Og lolcat.c -o lolcat-c

hello:
	yasm -f elf64 -o hello.o hello.asm
	ld -o hello hello.o

clean:
	rm -vf lolcat.o lolcat lolcat.core
	rm -vf hello.o hello.core hello

test:
	make lolcat
	echo "Testing the lolcat ^_^" | ./lolcat
