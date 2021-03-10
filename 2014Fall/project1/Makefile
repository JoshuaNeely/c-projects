INCLUDES_DIR = ./
OBJECT_FILE_DIR = obj
LIBS = -lm

CC = gcc
CFLAGS = -I. -Wall

_DEPS = readToken.h token.h
DEPS = $(patsubstr %,$(INCLUDES_DIR)/%,$(_DEPS))

_OBJ = main.o readToken.o
OBJ = $(patsubst %,$(OBJECT_FILE_DIR)/%,$(_OBJ))


$(OBJECT_FILE_DIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean
clean:
	rm -f $(OBJECT_FILE_DIR)/*.o *~ core $(INCLUDES_DIR)/*~
