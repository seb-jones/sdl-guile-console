CC=gcc

CFLAGS=`pkgconf --cflags sdl2 guile-2.2`

LIBS=`pkgconf --libs sdl2 guile-2.2`

OPTIONS=-Wall -g -O0

a.out:	code/*.c
	${CC} ${OPTIONS} code/main.c ${CFLAGS} ${LIBS}
