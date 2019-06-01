_EXE = grafo

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
BIN_DIR = bin

ASTYLE = $(shell which astyle)
        
EXE = $(BIN_DIR)/$(_EXE)

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = $(shell which cc)
CPPFLAGS += -I$(INC_DIR)     # -I is a preprocessor flag, not a compiler flag
CFLAGS += -Wall -O2          # some warnings about bad code
LDFLAGS +=                   # Left empty if no libs are needed (-L diretorio das static lib)
LDLIBS +=                    # Left empty if no libs are needed (-lm -lpthread...)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXE)

format:
	$(ASTYLE) $(SRC_DIR)/*.c $(INC_DIR)/*.h 
