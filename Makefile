CC=g++
CFLAGS= -Iinc -g
LFLAGS= -lGL -lSDL2 -lGLEW
SRCDIR=src
OBJDIR=obj
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(patsubst %.cpp,%.o,$(SRC)))
BIN=game

default: $(BIN)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ -c $(CFLAGS) $<

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

run:
	./$(BIN)

clean:
	rm $(BIN) $(OBJ)

.PHONY=clean
