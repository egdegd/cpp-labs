all: main board_test

main: bin/Board.o bin/View.o bin/main.o
	g++ bin/Board.o bin/View.o bin/main.o -o main
bin/main.o: src/main.cpp include/Board.h include/View.h
		g++ -c src/main.cpp -I include -o bin/main.o
bin/Board.o: src/Board.cpp include/Board.h
	g++ -c src/Board.cpp -I include -o bin/Board.o
bin/View.o: src/View.cpp include/Board.h include/View.h
	g++ -c src/View.cpp -I include -o bin/View.o

board_test: bin/Board.o bin/BoardTest.o bin/Test.o bin/test.o
	g++ bin/Board.o bin/BoardTest.o bin/Test.o bin/test.o -o board_test
bin/test.o: test/test.cpp include/BoardTest.h
	g++ -c test/test.cpp -I include -o bin/test.o
bin/BoardTest.o: test/BoardTest.cpp include/BoardTest.h include/Board.h
	g++ -c test/BoardTest.cpp -I include -o bin/BoardTest.o
bin/Test.o: test/Test.cpp include/Test.h
	g++ -c test/Test.cpp -I include -o bin/Test.o

clean:
	rm bin/*.o main board_test