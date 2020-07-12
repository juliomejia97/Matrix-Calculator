# PROYECTO #1 - Makefile para generar 2 ejecutables
# 

all: pdispersa hdispersa

hdispersa: hilos.o 
	gcc hilos.o -o hdispersa -lpthread

hilos.o: hilos.c
	gcc -c hilos.c -lpthread

pdispersa: procesos.o
	gcc procesos.o -o pdispersa

procesos.o: procesos.c
	gcc -c procesos.c

clean: rm *.o pdispersa hdispersa
