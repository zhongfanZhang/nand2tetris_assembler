CPPFLAGS: -std=c++11

all: assembler

assembler: main.o parser.o code.o SymbolTable.o
			g++ -o assembler main.o parser.o code.o SymbolTable.o

main.o: main.cpp parser.h code.h SymbolTable.h
	g++ -std=c++11 -c main.cpp

parser.o: parser.cpp parser.h
	g++ -c parser.cpp

code.o: code.cpp code.h
	g++ -c code.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	g++ -std=c++11 -c SymbolTable.cpp

clean:
	rm *.o && rm assembler
