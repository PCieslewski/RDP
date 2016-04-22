p1: main.o Lexer.o Token.o TreeNode.o Parser.o Standardizer.o ControlUnit.o Flattener.o Enviornment.o CSEMachine.o
	g++ main.o Lexer.o Token.o TreeNode.o Parser.o Standardizer.o ControlUnit.o Flattener.o Enviornment.o CSEMachine.o -o p1

main.o: main.cpp
	g++ -c main.cpp
	
Lexer.o: Lexer.cpp Lexer.h
	g++ -c Lexer.cpp
	
Token.o: Token.cpp Token.h
	g++ -c Token.cpp
	
TreeNode.o: TreeNode.cpp TreeNode.h
	g++ -c TreeNode.cpp
	
Parser.o: Parser.cpp Parser.h
	g++ -c Parser.cpp
	
Standardizer.o: Standardizer.cpp Standardizer.h
	g++ -c Standardizer.cpp
	
ControlUnit.o: ControlUnit.cpp ControlUnit.h
	g++ -c ControlUnit.cpp
	
Flattener.o: Flattener.cpp Flattener.h
	g++ -c Flattener.cpp
	
Enviornment.o: Enviornment.cpp Enviornment.h
	g++ -c Enviornment.cpp
	
CSEMachine.o: CSEMachine.cpp CSEMachine.h
	g++ -c CSEMachine.cpp

clean:
	rm -f *.o p1 test LOL.txt
	rm -f -r diffresult
	
cl:
	rm -f *.o p1 test
	rm -f -r diffresult
	
testast: p1 rpal
	chmod +x p1
	chmod +x rpal
	perl difftest.pl -1 "./rpal -ast -noout FILE" -2 "./p1 -ast -noout FILE" -t tests/
	
testst: p1 rpal
	chmod +x p1
	chmod +x rpal
	perl difftest.pl -1 "./rpal -st -noout FILE" -2 "./p1 -st -noout FILE" -t tests/
	
testfull: p1 rpal
	chmod +x p1
	chmod +x rpal
	perl difftest.pl -1 "./rpal FILE" -2 "./p1 FILE" -t tests/
	
mainTest: 
	g++ -c mainTest.cpp
	g++ -c Flattener.cpp
	g++ -c ControlUnit.cpp
	g++ -c TreeNode.cpp
	g++ mainTest.o Flattener.o ControlUnit.o TreeNode.o -o test
