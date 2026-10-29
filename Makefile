CC := gcc
build:
	@$(CC) -O2 -g main.c -o konax11 -lX11 -lImlib2
