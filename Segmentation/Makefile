# Simple Makefile

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS= `pkg-config --libs sdl` -lSDL_image -lm
EXEC = OCR_ImageProcess
SRC= main_Segmentation.c Load_Image.c Segmentation.c
OBJ= $(SRC:.c=.o)

all: ${EXEC}

OCR_ImageProcess : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main_Segmentation.o: Load_Image.h Segmentation.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf	${EXEC}

# END Makefile
