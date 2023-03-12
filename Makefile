# Makefile perustason harkkatyö 2023
HT: main.o funktiot.o
	gcc main.o funktiot.o -o HT
main.o: main.c funktiot.h
	gcc main.c -c -std=c99 -pedantic -Wall
funktiot.o: funktiot.c funktiot.h
	gcc funktiot.c -c -std=c99 -pedantic -Wall