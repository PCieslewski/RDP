p1: main.o Lexer.o Token.o
	g++ main.o Lexer.o Token.o -o p1

main.o: main.cpp
	g++ -c main.cpp
	
Lexer.o: Lexer.cpp
	g++ -c Lexer.cpp
	
Token.o: Token.cpp
	g++ -c Token.cpp

clean:
	rm -f *.o p1
