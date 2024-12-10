build:
	rm -f app.exe
	gcc main.c -o app.exe

run:
	./app.exe

valgrind:
	rm -f app.exe
	gcc -g main.c -o app.exe
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./app.exe -f

build_test:
	rm -f test.exe
	gcc tests/test.c -o test.exe

run_test:
	./test.exe