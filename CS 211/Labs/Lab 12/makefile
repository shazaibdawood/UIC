build: main.o Course.o OfferedCourse.o
	g++ -Wall -o main.exe main.o Course.o OfferedCourse.o

Course.o: Course.cpp Course.h
	g++ -c Course.cpp

OfferedCourse.o: OfferedCourse.cpp OfferedCourse.h
	g++ -c OfferedCourse.cpp

main.o: main.cpp Course.h OfferedCourse.h
	g++ -c main.cpp

run:
	./main.exe

clean:
	rm -f main.exe main.o Course.o OfferedCourse.o

