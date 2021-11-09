CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
CC = gcc
TCWIN = x86_64-w64-mingw32-


build:
	@mkdir -p bin
	@$(CC) pm.c $(CFLAGS) -o bin/pm
	@echo "CC	pm.c"
	@echo "EXE	pm"

buildwin:
	@mkdir -p bin
	@$(TCWIN)$(CC) pm.c $(CFLAGS) -o bin/pm.exe
	@echo "CC	pm.c"
	@echo "EXE	pm.exe"

clean:
	@rm -d -r bin
	@echo "CLEAN"
