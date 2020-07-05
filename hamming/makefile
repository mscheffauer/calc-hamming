# file: Makefile

PROGRAM = hamming
ARGUMENTS =
EFLAGS =
CC = gcc
CFLAGS = -pedantic -Wall -Wextra -std=c18 -ggdb $(EFLAGS)

LD = gcc
LDFLAGS = -lm


CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

all: depend $(PROGRAM)

$(PROGRAM): $(OFILES)
	$(LD) -o $@ $(OFILES) $(LDFLAGS)

.PHONY: run debug

clean: 
	rm -f $(OFILES)
	
run: $(PROGRAM)
	./$(PROGRAM) $(ARGUMENTS) && rm -f $(OFILES) && rm -f .depend 
	
debug: $(PROGRAM)
	gdb $(PROGRAM) $(ARGUMENTS)

DEPENDFILE = .depend

depend:
	$(CC) $(CFLAGS) -MM $(CFILES) > $(DEPENDFILE)

-include $(DEPENDFILE)
