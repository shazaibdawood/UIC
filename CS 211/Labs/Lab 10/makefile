build:
	rm -f main.exe 
	gcc main.c -lm -o main.exe

run:
	./main.exe

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./main.exe
