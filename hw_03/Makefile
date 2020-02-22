all: huffman huff_test

huffman: bin/huffman.o bin/HuffmanArchiver.o bin/main.o
	g++ bin/huffman.o bin/HuffmanArchiver.o bin/main.o -o huffman
bin/main.o: src/main.cpp src/HuffmanArchiver.h 
		g++ -c src/main.cpp -o bin/main.o
bin/huffman.o: src/huffman.cpp src/huffman.h
	g++ -c src/huffman.cpp -o bin/huffman.o
bin/HuffmanArchiver.o: src/huffman.h src/HuffmanArchiver.cpp src/HuffmanArchiver.h
		g++ -c src/HuffmanArchiver.cpp -o bin/HuffmanArchiver.o

huff_test: bin/HuffmanArchiver.o bin/huffman.o bin/autotest.o bin/huffman_test.o bin/test.o
	g++ bin/HuffmanArchiver.o bin/huffman.o bin/autotest.o bin/huffman_test.o bin/test.o -o huff_test
bin/test.o: test/test.cpp test/huffman_test.h
	g++ -c test/test.cpp -o bin/test.o
bin/huffman_test.o: test/huffman_test.cpp test/huffman_test.h src/HuffmanArchiver.h
	g++ -c test/huffman_test.cpp -I src -o bin/huffman_test.o
bin/autotest.o: test/autotest.cpp test/autotest.h
	g++ -c test/autotest.cpp -o bin/autotest.o

clean:
	rm bin/* huffman huff_test