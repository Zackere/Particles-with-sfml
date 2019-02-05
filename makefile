CC=clang++
CFLAGS=-Wall -Werror -pedantic -std=c++14 #-fsanitize=shift,integer-divide-by-zero,unreachable,vla-bound,null,return,signed-integer-overflow,address
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SFML=/usr/local
TARGET=sfml-app
FILES=main.o particle.o


${TARGET}: ${FILES}
	${CC} ${FILES} -o ${TARGET} -L${SFML}/lib ${LFLAGS} ${CFLAGS}

main.o: main.cpp
	${CC} -c main.cpp -I ${SFML}/include 

particle.o: particle.h particle.cpp
	${CC} -c particle.cpp

.PHONY: clean

clean:
	-rm -f ${TARGET} ${FILES}
