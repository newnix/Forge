NAME = rsnix
SRC = rsnix.c

CFLAGS = -fPIC -Oz -fstack-protector-all -fstack-protector-strong -fpic -fpie -fPIE -pie
LDFLAGS = -z relro -z now -z combreloc
CC = clang-devel
INCLUDE = -I/usr/include -I/usr/local/include
LIBS = -L/usr/lib -L/usr/local/lib -Wl,-rpath,/usr/local/lib -gssapi_krb5 -lk5crypto -lcom_err -lz -lkrb5 -lc -lxml2 -lsqlite3

DESTDIR = ${HOME}
PREFIX = bin/c/

all: options ${NAME}

${NAME}:
	@echo CC -o $@
	@${CC} ${SRC} -o $@ ${LDFLAGS}

options:
	@echo "${SRC} build options:"
	@echo "CFLAGS   = ${CFLAGS}"
	@echo	"LDFLAGS  = ${LDFLAGS}"
	@echo	"CC       = ${CC}"
	@echo "INCLUDES = ${INCLUDE}"
	@echo "LIBS     = ${LIBS}"

clean:
	@echo Cleaning...
	@unlink ${NAME}
	@echo "No temp files to clean"

install:
	@echo Installing executable file to ${DESTDIR}${PREFIX}
	@mkdir -p ${DESTDIR}${PREFIX}
	@cp -f ${NAME} ${DESTDIR}${PREFIX}
	@chmod 0755 ${DESTDIR}${PREFIX}${NAME}
	@echo "Use ${DESTDIR}${PREFIX}${NAME} -h to see the options for this program"

uninstall:
	@echo Removing executable from system
	@unlink ${DESTDIR}${PREFIX}${NAME}

.PHONY: all options clean install uninstall
