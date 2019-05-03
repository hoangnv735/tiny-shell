OBJS = main.o std.o bat.o datetime.o shell.o help.o
LIB = -lshlwapi

all:  ${OBJS} main run
.PHONY: run

main.o: main.c
	gcc -c main.c
bat.o: bat.c bat.h
	gcc -c bat.c
std.o: std.c std.h datetime.h
	gcc -c std.c
datetime.o: datetime.h
	gcc -c datetime.c
shell.o: shell.h
	gcc -c shell.c
help.o: help.h
	gcc -c help.c

main: ${OBJS}
	gcc -o tiny-shell ${OBJS} ${LIB}
run:
	.\tiny-shell
