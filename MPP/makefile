CC = gcc 
CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2

all: labyrinth

labyrinth: main.o scan.o safeMemory.o error.o overflow.o bitset.o bfs.o queue.o
	${CC} -o labyrinth $^

bfs.o: bfs.c bfs.h bitset.h queue.h
	${CC} ${CFLAGS} -c $<

bitset.o: bitset.c bitset.h
	${CC} ${CFLAGS} -c $<

error.o: error.c error.h
	${CC} ${CFLAGS} -c $<
	
main.o: main.c scan.h safeMemory.h error.h bitset.h bfs.h
	${CC} ${CFLAGS} -c $<

overflow.o: overflow.c overflow.h
	${CC} ${CFLAGS} -c $<

queue.o: queue.c queue.h
	${CC} ${CFLAGS} -c $<

safeMemory.o: safeMemory.c safeMemory.h
	${CC} ${CFLAGS} -c $<
	
scan.o: scan.c scan.h overflow.h safeMemory.h bitset.h
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o labyrinth