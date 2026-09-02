CC := gcc
build:
	@$(CC) -O2 main.c -o konax11 -lX11 -lImlib2
