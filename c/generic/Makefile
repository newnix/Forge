NAME = interview
SRC = bsdnow_qs.c

CFLAGS = -fPIC -Os 
LDFLAGS = -static -z relro -z now -z combreloc
CC = cc

all: options ${NAME}

${NAME}:
	@echo CC -o $@
	@${CC} ${SRC} -o $@ ${LDFLAGS}

options:
	@echo ${SRC} build options:
	@echo "CFLAGS  = ${CFLAGS}"
	@echo	"LDFLAGS = ${LDFLAGS}"
	@echo	"CC      = ${CC}"

clean:
	@echo Cleaning...
	@echo "No temp files to clean"

install:
	@echo Installing executable file to ${DESTDIR}${PREFIX}
	@mkdir -p ${DESTDIR}${PREFIX}
	@cp -f ${NAME} ${DESTDIR}${PREFIX}
	@chmod 0755 ${DESTDIR}${PREFIX}${NAME}
	@echo "Use ${DESTDIR}${PREFIX}${NAME} -h to see the options for this program"

uninstall:
	@echo Removing executable from system
	@rm -f ${DESTDIR}${PREFIX}${NAME}

.PHONY: all options clean install uninstall
