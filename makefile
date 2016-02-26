p1: main.o Lexer.o Token.o TreeNode.o Parser.o
	g++ main.o Lexer.o Token.o TreeNode.o Parser.o -o p1

main.o: main.cpp
	g++ -c main.cpp
	
Lexer.o: Lexer.cpp
	g++ -c Lexer.cpp
	
Token.o: Token.cpp
	g++ -c Token.cpp
	
TreeNode.o: TreeNode.cpp
	g++ -c TreeNode.cpp
	
Parser.o: Parser.cpp
	g++ -c Parser.cpp

clean:
	rm -f *.o p1
