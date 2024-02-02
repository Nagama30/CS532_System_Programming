# Sample Makefile to compile C programs

CC = gcc
CFLAGS = -Wall -g #replace -g with -O when not debugging

DEPS = Makefile
OBJS = file_copy.o
EXECS = file_copy

all: $(EXECS)
	./$(EXECS) arg1 arg2

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(EXECS)