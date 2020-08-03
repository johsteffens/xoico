TARGET = xoite

CC      = gcc
CFLAGS  = -Wall -O3 -std=c11 
LDFLAGS = -lm -lpthread

BETH_SRCS = ../beth/lib
MAIN_SRCS = src

BETH_BCORE_SRCS = $(BETH_SRCS)/bcore

INCLUDES = \
    -I $(BETH_BCORE_SRCS)

SRCS = \
    $(wildcard $(BETH_BCORE_SRCS)/*.c) \
    $(wildcard $(MAIN_SRCS)/*.c)
    
HDRS = \
    $(wildcard $(BETH_BCORE_SRCS)/*.h) \
    $(wildcard $(MAIN_SRCS)/*.h)

$(TARGET): $(SRCS) $(HDRS)
ifeq ($(wildcard $(BETH_BCORE_SRCS)/*.c),)
	@echo "Sources of beth-library missing: $(BETH_BCORE_SRCS). Run in parent folder: git clone https://github.com/johsteffens/beth.git"
else
	$(CC) -o $@ $(SRCS) $(CFLAGS) $(INCLUDES) $(LDFLAGS) 
endif

.PHONY: clean

clean:
	rm -f $(TARGET)
