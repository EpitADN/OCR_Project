# Simple Makefile

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS= -lm
EXEC = OCR
SRC= main.c Node.c Layer.c Transition.c Network.c Backprop.c Trainer.c SaveAndLoad.c
OBJ= $(SRC:.c=.o)

all: ${EXEC}

OCR : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	mkdir Saves

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf	${EXEC}
	rm -rf Saves/

# END Makefile
