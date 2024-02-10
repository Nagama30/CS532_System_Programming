# Sample Makefile to compile C programs

CC = gcc
CFLAGS = -Wall -g #replace -g with -O when not debugging

DEPS = Makefile
OBJS = njamadar_HW02.o
EXECS = njamadar_HW02

all: $(EXECS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

make run: $(EXECS)
	./$(EXECS) $(ARGS)

clean:
	rm -f $(OBJS) $(EXECS)