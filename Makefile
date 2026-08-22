CC := gcc
build:
	@$(CC) main.c image.c -o konax11 -lX11 -lpng 
