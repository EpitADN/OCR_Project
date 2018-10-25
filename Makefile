# Simple Makefile

CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS= -lm
EXEC = OCR
SRC= main.c Backprop.c SaveAndLoad.c Layer.c Trainer.c Transition.c Node.c Network.c
OBJ= $(SRC:.c=.o)

all: ${EXEC}

OCR : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	mkdir Saves

main.o: Trainer.h SaveAndLoad.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf	${EXEC}
	rm -rf Saves

# END Makefile