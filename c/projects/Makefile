.POSIX:

MUSER = ${USER}
GROUP = ${USER}
DESTDIR = ${HOME}
PREFIX = /bin/c/
SRC = projects.c
TARGET = projects
INCS = -I. -I/usr/include -I/usr/local/include -I/usr/local/include
LIBS = -L. -L/usr/local/lib -L/usr/lib 
CFLAGS = -Oz -fpic -fpie -fPIC -fPIE -ftrapv -fstack-protector-all -fstack-protector-strong -march=native -Wall -Wextra -pedantic 
LDFLAGS = -z relro -z now -z combreloc -lc -lsqlite3 -lpthread -lm
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

clean:
	rm $(target)

install: build
	strip -s $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)
	chown $(USER):$(GROUP) $(TARGET)
	chmod 0755 $(TARGET)
	cp -fp $(TARGET) $(DESTDIR)$(PREFIX)$(TARGET)
	@echo "Run $(DESTDIR)$(PREFIX)$(TARGET) -h for usage information"

uninstall:
	rm -f $(TARGET)
	rm -f $(DESTDIR)$(PREFIX)$(TARGET)

