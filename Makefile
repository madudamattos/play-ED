compila:
	clear
	gcc -o main *.c 

valgrind:
	make compila
	valgrind ./main

roda:
	make compila
	./main