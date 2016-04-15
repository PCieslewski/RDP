p1: main.o Lexer.o Token.o TreeNode.o Parser.o Standardizer.o
	g++ main.o Lexer.o Token.o TreeNode.o Parser.o Standardizer.o -o p1

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
	
Standardizer.o: Standardizer.cpp
	g++ -c Standardizer.cpp

clean:
	rm -f *.o p1
	rm -f -r diffresult
	
cl:
	rm -f *.o p1
	rm -f -r diffresult
	
test: p1 rpal
	chmod +x p1
	chmod +x rpal
	perl difftest.pl -1 "./rpal -ast -noout FILE" -2 "./p1 -ast FILE" -t tests/
