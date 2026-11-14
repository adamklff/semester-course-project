CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic
CPPFLAGS = -Iinclude
SOURCES = src/main.c src/array_list.c src/linked_list.c
HEADERS = $(wildcard include/*.h)

login-review: $(SOURCES) $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(SOURCES)

clean:
	rm -f login-review

.PHONY: clean
