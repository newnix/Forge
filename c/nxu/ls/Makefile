.POSIX:

MUSER = ${USER}
GROUP = ${USER}
PREFIX = ${HOME}
DESTDIR = /bin/c/
TARGET = nxls
SRC = nxls.c
INCS = -I. -I/usr/include -I/usr/local/include
LIBS = -L. -L/usr/lib -L/usr/local/lib
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Oz -fpic -fpie -fPIC -fPIE -ftrapv -fstack-protector-all -fstack-protector-strong -march=native -mtune=native -static -ffreestanding -fsanitize-stats -fsanitize-thread-memory-access -fsanitize-memory-use-after-dtor -fsanitize-address-use-after-scope -fsanitize-cfi-icall-generalize-pointers -fsanitize-cfi-cross-dso
LDFLAGS = -lc -pie -z relro -z now -z combreloc 
TMPDIR = /tmp
CC = clang-devel
LD = ld.lld-devel

help:
	@printf "Nothing here yet!\n"

build: ${SRC}
	$(CC) ${SRC} -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(INCS) $(LIBS)

install: build
	@strip -s $(TARGET)
	@mkdir -m 0755 -p $(PREFIX)
	@chown $(USER):$(GROUP) $(TARGET)
	@cp -fp $(TARGET) $(PREFIX)$(DESTDIR)
	@rm -f $(TARGET)
	@printf "\n\n"
	$(PREFIX)$(DESTDIR)$(TARGET) -h

uninstall:
	@rm -f $(PREFIX)$(DESTDIR)$(TARGET)

rebuild: uninstall install

run:
	@$(PREFIX)$(DESTDIR)$(TARGET)
