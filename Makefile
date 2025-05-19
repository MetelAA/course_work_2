CC = gcc
CFLAGS = -Wall -Wextra
SRCS = main.c help.c info.c parser.c base_validator.c canvas_entity_validator.c
OBJS = $(SRCS:.c=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf main.o help.o info.o parser.o base_validator.o canvas_entity_validator.o $(TARGET)

.PHONY: all clean