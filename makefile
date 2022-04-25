TARGET = bin/xoico

CC      = gcc
CFLAGS  = -Wall -O3 -std=c11 
LDFLAGS = -lm -lpthread -latomic

BETH_LIB = ../beth/lib
MAIN_SRC = src

INCLUDES = \
    -I ../beth/lib/bcore

SRCS = \
    $(wildcard $(BETH_LIB)/bcore/*.c) \
    $(wildcard $(MAIN_SRC)/*.c)

$(TARGET): $(SRCS)
	mkdir -p $(dir $(TARGET) )
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(TARGET)

