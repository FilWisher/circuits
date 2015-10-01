CC = gcc
LIBS = -L/usr/lib -lc
CFLAGS = -std=c99 -pedantic

all: options s p

options:
	@echo build options:
	@echo "CC = $(CC) $(CFLAGS)"

s:
	@echo CC -o $@
	@$(CC) -o $@ $@.c $(LIBS) $(CFLAGS)
	
p:
	@echo CC -o $@
	$(CC) -o $@ $@.c $(LIBS) $(CFLAGS)

clean:
	@echo cleaning
	@rm -f s p $(OBJ)
