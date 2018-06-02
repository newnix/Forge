.POSIX:

# Where to install and what permissions to set
MUSER = ${USER} 
GROUP = ${USER}
PREFIX = ${HOME}
DESTDIR = /bin/c/
MODE = 0755

# Ensure all sources and libs are available
INCS = -I. -I/usr/include -I/usr/local/include
LIBS = -L. -L/usr/include -L/usr/local/include

# Flags shared between C and C++
DBG = gdb
BFLAGS = -Wall -Wextra -pedantic -std=c99 -Oz -fpic -fpie -fPIE -fPIC \
				 -march=native -mtune=native -z relro -z now -z combreloc -fvisibility=hidden \
				 -Wl,-pie,--gc-sections,--pic-executable -pipe -g${DBG}
CFLAGS = ${BFLAGS}
CXXFLAGS = ${BFLAGS}
TMPDIR = /tmp
# Which compiler and linker to use
CC = clang-devel
LD = ld.lld-devel

# When applicable, use this assembler
AS = yasm

help:
	@printf "Build configuration for ${TARGET}:\n"
	@printf "\nPREFIX:\t%s\nDIR:\t%s\nINST:\t%s\nOWNER:\t%s\nGROUP:\t%s\nMODE:\t%s\n\nCC:\t%s\nCFLAGS:\t%s\nINCS:\t%s\nLIBS:\t%s\n"\
		"${PREFIX}" "${DESTDIR}" "${PREFIX}${DESTDIR}${TARGET}" "${MUSER}" "${GROUP}" "${MODE}" "${CC}" "${CFLAGS}" "${INCS}" "${LIBS}"
	@printf "\n\nChange these settings with %s %s\n" ${EDITOR} "defaults.mk"
	@printf "Valid targets: build, debug, help, install, uninstall, rebuild, reinstall, run\n"

build: ${SRC}
	$(CC) -o $(TARGET) $(CFLAGS) $(INCS) $(LIBS) ${SRC}

debug: build
	@mkdir -p ${PREFIX}${DESTDIR}
	@chown ${USER}:${GROUP} ${TARGET}
	@chmod ${MODE} ${TARGET}
	@cp -fp ${TARGET} ${PREFIX}${DESTDIR}
	@rm -f ${TARGET}
	@printf "\n\n"
	$(PREFIX)$(DESTDIR)$(TARGET) -h

install: build
	@strip -s ${TARGET}
	@mkdir -p ${PREFIX}${DESTDIR}
	@chown ${USER}:${GROUP} ${TARGET}
	@chmod ${MODE} ${TARGET}
	@cp -fp ${TARGET} ${PREFIX}${DESTDIR}
	@rm -f ${TARGET}
	@printf "\n\n"
	$(PREFIX)$(DESTDIR)$(TARGET) -h

uninstall: 
	@rm -f ${PREFIX}${DESTDIR}${TARGET}

rebuild: uninstall debug

reinstall: uninstall install

run:
	$(PREFIX)$(DESTDIR)$(TARGET)
