CC = gcc
make:
	$(CC) -o test ./src/mem.c ./src/answer/answer.c ./src/num-gen/gen.c ./src/utils/utils.c
