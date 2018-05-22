.POSIX:

# More to come

INCS = -I/usr/include -I/usr/local/include
LIBS = -L/usr/lib -L/usr/local/lib
SRCS = nxt.c config.h
CFLAGS = -Wall -Wextra -Werror -Weverything -pedantic -std=c99 -Oz -fpic -fpie -fPIC -fPIE --fuse-linker=ld.lld-devel
LDFLAGS = -z relro -z combreloc -z now -Wl,--gc-sections,--pic-executable,-pie
CC = clang-devel
LD = ld.lld-devel

help: 
	@printf "Sources:\t%s\n" "${SRCS}"
	@printf "INCS:\t\t%s\n" "${INCS}"
	@printf "LIBS:\t\t%s\n" "${LIBS}"
	@printf "CFLAGS:\t\t%s\n" "${CFLAGS}"
	@printf "LDFLAGS:\t%s\n" "${LDFLAGS}"
	@printf "CC:\t\t%s\n" "${CC}"
	@printf "LD:\t\t%s\n" "${LD}"
	@printf "\nRun %s Makefile to tweak these settigs\n" "${EDITOR}"

update:
	@git pull

all: update help
