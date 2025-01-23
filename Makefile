CC = gcc
CFLAGS = -Wall

SRCS = main.c funkcje.c
OBJS = $(SRCS:.c=.o)

EXEC = gra

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

rebuild: clean all