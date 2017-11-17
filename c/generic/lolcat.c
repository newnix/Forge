#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

char read_char(void);
void set_color(int c);

int
main(int argc, char **argv) {
	int color;
	char input;

	color = input = 0;
	while (1 == 1) {
		input = read_char();
		if (input != 0) {
			putc(input, stdout);
			set_color(color);
			color++;
		} else {
			break;
		}
	}
	exit(0);
}

char
read_char() {
	char *char_buf;
	int result;

	result = scanf("%c",char_buf);
	if (result > 0) {
		return *char_buf;
	} else {
		return 0;
	}
}

void set_color(int color) {
	char put_color;

	put_color = 0;

	putc(27, stdout);
	putc('[', stdout);
	putc('3', stdout);

	put_color = (color % 6) + 1;
	putc('0' + put_color, stdout);
	putc(';', stdout);
	putc('1', stdout);
	putc('m', stdout);
}
