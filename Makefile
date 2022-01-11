SRC = src/fetch.c
CC ?= cc
CFLAGS = -O2 -std=c99 -Wall -Wextra
LDFLAGS = -lpthread

all: archfetch

build:
	$(FILES) 
	$(CC) $(CFLAGS) -O $(NAME) $(FILES)

clean:
	rm -rf archfetch

install:
	$(SRC) src/color.h
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o archfetch
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp archfetch $(DESTDIR)$(PREFIX)/bin
	chmod 777 $(DESTDIR)$(PREFIX)/bin/archfetch

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/bin/archfetch

.PHONY: all clean install uninstall