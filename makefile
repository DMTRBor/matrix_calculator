mainmat: mainmat.o mymat.o utils.o mymat.h utils.h
	gcc -g -ansi -Wall -pedantic mainmat.o mymat.o utils.o -o mainmat -lm

mymat.o: mymat.c mymat.h
	gcc -c -g -ansi -Wall -pedantic mymat.c -o mymat.o
utils.o: utils.c mymat.h utils.h
	gcc -c -g -ansi -Wall -pedantic utils.c -o utils.o
