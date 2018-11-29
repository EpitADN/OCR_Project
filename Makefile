# Simple Makefile edited by Griffures

CC=gcc
CFLAGS=		-Wall -Wextra -std=c99 -O2

EXEC = 		NeuralNetwork ImageProcess UserInterface

LDFLAGS_NR = 	-lm
LDFLAGS_IP = 	-lm $(shell pkg-config --libs sdl) -lSDL_image
LDFLAGS_UI = 	-lm $(shell pkg-config --libs gtk+-2.0)

SRC_NR = 	$(wildcard Sources/NeuralNetwork/*.c)
SRC_IP = 	$(wildcard Sources/ImageProcess/*.c)
SRC_UI = 	$(wildcard Sources/UserInterface/*.c)

OBJ_NR = 	$(SRC_NR:.c=.o)
OBJ_IP = 	$(SRC_IP:.c=.o)
OBJ_UI = 	$(SRC_UI:.c=.o)

all: ${EXEC}

NeuralNetwork : $(OBJ_NR)
	$(CC) -o $@ $^ $(LDFLAGS_NR)

ImageProcess : $(OBJ_IP)
	$(CC) -o $@ $^ $(LDFLAGS_IP)

UserInterface : $(OBJ_NR) $(OBJ_UI)
	$(CC) -o $@ $^ $(LDFLAGS_UI)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf Sources/UserInterface/*.o
	rm -rf Sources/ImageProcess/*.o
	rm -rf Sources/NeuralNetwork/*.o

fclean: clean cclean
	rm -rf	${EXEC}
	rm -rf Saves/*.bin

cclean: clean
	rm -rf .idea/
	rm -rf cmake-build-debug/
	rm -rf CMakeLists.txt

# END Makefile
