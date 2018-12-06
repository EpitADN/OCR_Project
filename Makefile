# Simple Makefile edited by Griffures

#
# Compilater variables ---------------------------------
#

CC=			gcc

CFLAGS=		-Wall -Wextra -std=c99 -O2 -D_GNU_SOURCE
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-2.0)

LDFLAGS =		-lm
SDL_LDFLAGS = 	$(shell pkg-config --libs sdl) -lSDL_image
GTK_LDFLAGS =	$(shell pkg-config --libs gtk+-2.0)

#
# Classes declaration ----------------------------------
#

DIR =	Sources/
EXEC_Classes = 	NeuralNetwork Interface ImageProcess UserInterface


EXC_NR = 	NetworkManager
DIR_NR = 	$(DIR)NeuralNetwork/
SRC_NR = 	$(filter-out $(addprefix $(DIR_NR),$(addsuffix .c,$(EXC_NR))),$(wildcard $(DIR_NR)*.c))

EXC_IT =	ResourceManager SingleCharOCR BetterManager mainTests
DIR_IT = 	$(DIR)Interface/
SRC_IT = 	$(filter-out $(addprefix $(DIR_IT),$(addsuffix .c,$(EXC_IT))),$(wildcard $(DIR_IT)*.c))

EXC_IP = 	mainSegmentation
DIR_IP = 	$(DIR)ImageProcess/
SRC_IP = 	$(filter-out $(addprefix $(DIR_IP),$(addsuffix .c,$(EXC_IP))),$(wildcard $(DIR_IP)*.c))

EXC_UI =	mainUI
DIR_UI = 	$(DIR)UserInterface/
SRC_UI = 	$(filter-out $(addprefix $(DIR_UI),$(addsuffix .c,$(EXC_UI))),$(wildcard $(DIR_UI)*.c))


OBJ_NR = 	$(SRC_NR:.c=.o)
OBJ_IT = 	$(SRC_IT:.c=.o)
OBJ_IP = 	$(SRC_IP:.c=.o)
OBJ_UI = 	$(SRC_UI:.c=.o)

#
# Targets declaration ----------------------------------
#

all: ${EXEC_Classes}

# NeuralNetwork	----------------------------------------


NeuralNetwork : $(EXC_NR)

NetworkManager : $(OBJ_NR) $(DIR_NR)NetworkManager.o
	$(CC) -o $@ $^ $(LDFLAGS)


# Interface		----------------------------------------

Interface : $(EXC_IT)

ResourceManager : $(OBJ_IT) $(OBJ_NR) $(DIR_IT)ResourceManager.o
	$(CC) -o $@ $^ $(LDFLAGS) $(SDL_LDFLAGS)

SingleCharOCR : $(OBJ_IT) $(OBJ_NR) $(DIR_IT)SingleCharOCR.o
	$(CC) -o $@ $^ $(LDFLAGS) $(SDL_LDFLAGS)

BetterManager : $(OBJ_IT) $(OBJ_NR) $(DIR_IT)BetterManager.o
	$(CC) -o $@ $^ $(LDFLAGS) $(SDL_LDFLAGS)

mainTests : #NADA

# ImageProcess	----------------------------------------

ImageProcess : $(EXC_IP)

mainSegmentation : $(OBJ_IP) $(DIR_IP)mainSegmentation.o
	$(CC) -o $@ $^ $(LDFLAGS) $(SDL_LDFLAGS)

# UserInterface	----------------------------------------

UserInterface : $(EXC_UI)

mainUI : $(OBJ_NR) $(OBJ_UI) $(DIR_UI)mainUI.o
	$(CC) -o $@ $^ $(LDFLAGS) $(GTK_LDFLAGS)


#
# Objects:	 	----------------------------------------
#

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(GTK_CFLAGS)

#
# Nettoyage:	 ----------------------------------------
#

clean:
	rm -rf $(foreach class,$(EXEC_Classes),$(DIR)$(class)/*.o)

cclean: clean
	rm -rf .idea/
	rm -rf cmake-build-debug/
	rm -rf CMakeLists.txt

fclean: cclean clean 
	rm -rf ${EXC_NR} ${EXC_IT} ${EXC_IP} ${EXC_UI}

#
# END Makefile 	----------------------------------------
#