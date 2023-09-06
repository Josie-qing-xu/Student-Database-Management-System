CC = gcc
CC_FLAGS = -g -ansi -pedantic -W -Wall
OUT_EXE = student
FILES = main.c functions.c 

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core *.exe $(OUT_EXE)

rebuild: clean build