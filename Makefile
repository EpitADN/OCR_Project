# Simple Makefile

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -O2 $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS= $(shell pkg-config --libs gtk+-2.0) -lm
EXEC = OCR_Graphical_UI
SRC= main.c Backprop.c SaveAndLoad.c Layer.c Trainer.c Transition.c Node.c Network.c UI.c
OBJ= $(SRC:.c=.o)

all: ${EXEC}

OCR_Graphical_UI : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: Network.h UI.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf	${EXEC}

# END Makefile
