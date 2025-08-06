CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Isrc/lib

SRCS = src/main.c src/lib/linkedList.c src/lib/utils.c

OBJS = $(SRCS:src/%.c=build/%.o)

TARGET = build/main

all: $(TARGET)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf build

.PHONY: all clean
