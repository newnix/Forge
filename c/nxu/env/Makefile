.POSIX:

MUSER = ${USER}
GROUP = ${USER}
PREFIX = ${HOME}
DESTDIR = /bin/c/
TARGET = nxenv
SRC = nxenv.c
INCS = -I. -I/usr/include -I/usr/local/include
LIBS = -L. -L/usr/lib -L/usr/local/lib
# Add -DPRNTERR to enable error reporting, this adds about 400B to the size of the binary
# which is unlikely to be a serious issue on most hardware, but considering the anticipated use
# case for a reimplimentation of env(1), I didn't find it necessary to include by default
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Oz -fpic -fpie -fPIE -fPIC \
				 -march=native -mtune=native -z relro -z combreloc -z now -fvisibility=hidden \
				 -Xlinker -pie -Xlinker --gc-sections -Xlinker --pic-executable \
				 -pipe 
TMPDIR = /tmp
CC = clang-devel

help: 
	@printf "CFLAGS:\t${CFLAGS}\nTARGET:\t${TARGET}\nInstallpath:\t${PREFIX}${DESTIDIR}";
	@printf "\nCC:\t${CC}\n\n\tUse \`${EDITOR} Makefile\` to change these settigs\n\n";

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
