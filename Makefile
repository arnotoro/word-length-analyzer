# Makefile Harjoitustyö - Arno Törö 12.3.2023
word_length_analyzer: HTPerustaso.o HTPerusKirjasto.o
	gcc HTPerustaso.o HTPerusKirjasto.o -o word_length_analyzer
HTPerustaso.o: HTPerustaso.c HTPerusKirjasto.h
	gcc HTPerustaso.c -c -std=c99 -pedantic -Wall
HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	gcc HTPerusKirjasto.c -c -std=c99 -pedantic -Wall