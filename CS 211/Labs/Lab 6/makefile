build: application.c TextAnalysis.o
	rm -f application.exe
	gcc -o application.exe application.c TextAnalysis.o

TextAnalysis.o: TextAnalysis.c TextAnalysis.h
	gcc -c TextAnalysis.c

run: application.exe
	./application.exe

valgrind: application.exe
	valgrind -s --tool=memcheck --leak-check=yes ./application.exe

clean: 
	rm -f application.exe

