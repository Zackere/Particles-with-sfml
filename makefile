CC=clang
SFML=/usr/local
CFLAGS=-Wall -Werror -pedantic -std=c++11
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lc++ -lpthread -lm
TARGET=sfml-app
FILES=main.o particle.o

${TARGET}: ${FILES}
	${CC} ${FILES} -o ${TARGET} -L${SFML}/lib ${LFLAGS}

main.o: main.cpp
	${CC} -c main.cpp -I${SFML}/include ${CFLAGS}

particle.o: particle.h particle.cpp
	${CC} -c particle.cpp ${CFLAGS}

.PHONY: clean

clean:
	-rm -f ${TARGET} ${FILES}
