OBJS = main.o std.o bat.o
HEADER = std.h bat.h	
LIB = -lshlwapi
all:  ${OBJS} main run
.PHONY: run
main.o: main.c
	gcc -c main.c 
bat.o: bat.c bat.h
	gcc -c bat.c 
std.o: std.c std.h
	gcc -c std.c 

main: ${OBJS}
	gcc -o tiny-shell ${OBJS} ${LIB}
run:
	.\tiny-shell