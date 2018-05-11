.POSIX:

MUSER = ${USER}
GROUP = ${USER}
PREFIX = ${HOME}
DESTDIR = /bin/c/
TARGET = nxenv
SRC = nxenv.c
INCS = -I. -I/usr/include -I/usr/local/include
LIBS = -L. -L/usr/lib -L/usr/local/lib
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Oz -fpic -fpie -fPIE -fPIC \
				 -march=native -mtune=native -z relro -z combreloc -z now -fvisibility=hidden \
				 -Xlinker -pie -Xlinker --gc-sections -Xlinker --pic-executable \
				 -pipe 
TMPDIR = /tmp
CC = clang-devel
LD = ld.lld-devel
AS = llvm-as-devel

help: 
	printf"";

build: ${SRC}
	$(CC) -o $(TARGET) $(CFLAGS) $(INCS) $(LIBS) ${SRC}

install: build
	@strip -s $(TARGET)
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
