
TARGET = main

CC = gcc
CFLAGS= -Wall

RM = rm

DEPS = $(wildcard *.h)
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

run: $(TARGET)
	./$<

clean:
	$(shell find . -type f -name '*.o' -exec $(RM) {} \;)
	$(shell find . -type f -executable -exec $(RM) {} \;)


