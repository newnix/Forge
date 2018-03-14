.POSIX:

MUSER = ${USER}
GROUP = ${USER}
PREFIX = ${HOME}
DESTDIR = /bin/c/
TARGET = nxenv
SRC = nxenv.c
INCS = -I. -I/usr/include -I/usr/local/include
LIBS = -L. -L/usr/lib -L/usr/local/lib
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Oz -fpic -fpie -fPIE -fPIC -ftrapv -fstack-protector-all -fstack-protector-strong -march=native -mtune=native -ffreestanding -fsanitize-stats -fsanitize-thread-memory-access -fsanitize-memory-use-after-dtor -fsanitize-address-use-after-scope -fsanitize-cfi-icall-generalize-pointers -fsanitize-cfi-cross-dso -ggdb
LDFLAGS = -z relro -z now -z combreloc -lc -pie 
TMPDIR = /tmp
CC = clang-devel
LD = ld.lld-devel

help: 
	printf"";

build: ${SRC}
	$(CC) ${SRC} -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(INCS) $(LIBS)

install: build
	#@strip -s $(TARGET)
	@mkdir -p $(PREFIX)
	@chown $(USER):$(GROUP) $(TARGET)
	@chmod 0755 $(TARGET)
	@cp -fp $(TARGET) $(PREFIX)$(DESTDIR)
	@rm -f $(TARGET)
	@printf "\n\n"
	$(PREFIX)$(DESTDIR)$(TARGET) -h

uninstall:
	@rm -f $(PREFIX)$(DESTDIR)$(TARGET)

rebuild: uninstall install 

run:
	$(PREFIX)$(DESTDIR)$(TARGET)
