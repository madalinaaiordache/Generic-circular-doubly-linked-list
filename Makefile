#Iordache Madalina, 313CA

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=main

build: $(TARGETS)

main: main.c
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
