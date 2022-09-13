SRC = src/fetch.c
CC ?= cc
CFLAGS=-g -O2 -std=c99 -Wall -Wextra
LDFLAGS=-lpthread

all: fastcpufetch

fastcpufetch: $(SRC) src/color.h
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o fastcpufetch

build: $(FILES) 
	$(CC) $(CFLAGS) -O $(NAME) $(FILES)

clean: 
	rm -rf fastcpufetch

install: fastcpufetch
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp fastcpufetch $(DESTDIR)$(PREFIX)/bin
	chmod 777 $(DESTDIR)$(PREFIX)/bin/fastcpufetch

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/bin/fastcpufetch

.PHONY: clean
