# Simple Makefile edited by Griffures

CC=gcc
CFLAGS=	-Wall -Wextra -std=c99 -O2

EXEC = UserInterface ImageProcess NeuralNetwork 

LDFLAGS_UI = -lm $(shell pkg-config --libs gtk+-2.0)
LDFLAGS_IP = -lm $(shell pkg-config --libs sdl) -lSDL_image
LDFLAGS_NR = -lm

SRC_UI = $(wildcard Sources/UserInterface/*.c)
SRC_IP = $(wildcard Sources/ImageProcess/*.c)
SRC_NR = $(wildcard Sources/NeuralNetwork/*.c)

OBJ_UI = $(SRC_UI:.c=.o)
OBJ_IP = $(SRC_IP:.c=.o)
OBJ_NR = $(SRC_NR:.c=.o)

all: ${EXEC}

UserInterface : $(OBJ_NR) $(OBJ_UI)
	$(CC) -o $@ $^ $(LDFLAGS_UI)

ImageProcess : $(OBJ_IP)
	$(CC) -o $@ $^ $(LDFLAGS_IP)

NeuralNetwork : $(OBJ_NR)
	$(CC) -o $@ $^ $(LDFLAGS_NR)
	mkdir Saves

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf Sources/UserInterface/*.o
	rm -rf Sources/ImageProcess/*.o
	rm -rf Sources/NeuralNetwork/*.o

fclean: clean
	rm -rf	${EXEC}
	rm -rf Saves/*.bin

# END Makefile
