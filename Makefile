# Minggw
OBJS = main.o std.o bat.o datetime.o shell.o help.o path.o process.o directory.o run.o
LIB = -I..\include -lshlwapi -lpsapi

all:  ${OBJS} main run
.PHONY: run

main.o: main.c
	g++ -c main.c
bat.o: bat.c bat.h
	g++ -c bat.c
std.o: std.c std.h datetime.h
	g++ -c std.c
datetime.o: datetime.c datetime.h
	g++ -c datetime.c
shell.o: shell.c shell.h
	g++ -c shell.c
help.o: help.c help.h
	g++ -c help.c
path.o: path.c path.h
	g++ -c path.c
process.o: process.c process.h
	g++ -c process.c
directory.o: directory.c directory.h
	g++ -c directory.c
run.o: run.c run.h
	g++ -c run.c

main: ${OBJS}
	g++ -o tiny-shell ${OBJS} ${LIB}
run:
	.\tiny-shell

clean:
	del *.o
