.POSIX:

USER = ${USER}
GROUP = ${USER}
DESTDIR = ${HOME}
PREFIX = /bin/
SRC = projects.c
TARGET = projects
INCS = -I. -I/usr/include -I/usr/local/include -I/usr/local/include
LIBS = -L. -L/usr/local/lib -L/usr/lib 
CFLAGS = -Oz -fpic -fpie -fPIC -fPIE -ftrapv -fstack-protector-all -fstack-protector-strong -static -march=native -Wall -Wextra -pedantic -Werror
LDFLAGS = -z relro -z now -z combreloc -static -lc -lsqlite3
CC = clang-devel

options:
	@echo "Build options:"
	@echo "CFLAGS    = ${CFLAGS}"
	@echo "LDFLAGS   = ${LDFLAGS}"
	@echo "CC        = ${CC}"
	@echo "INCLUDE   = ${INCS}"
	@echo "LIBS      = ${LIBS}"
	@echo "PREFIX    = ${PREFIX}"
	@echo "DESTDIR   = ${DESTDIR}"
	@echo "TARGET    = ${TARGET}"
	@echo "INSTALL   = ${DESTDIR}${PREFIX}${TARGET}"

build:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) ${INCS} ${LIBS}

install:
	mkdir -p $(DESTDIR)$(PREFIX)
	install -g $(GROUP) -o $(USER) -m 0755 -s -S $(DESTDIR)$(PREFIX) $(TARGET) 
	@echo "Run $(DESTDIR)$(PREFIX)$(TARGET) -h for usage information"

uninstall:
	rm -f $(DESTDIR)$(PREFIX)$(TARGET)

