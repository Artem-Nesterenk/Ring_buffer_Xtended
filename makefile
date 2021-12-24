all:
	gcc -g -Wall main.c ring_buff.c -o main && ./main