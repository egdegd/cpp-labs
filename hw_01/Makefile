main: bin/main.o bin/bmp.o
	gcc bin/main.o bin/bmp.o -std=c99 -Wall -Werror -o main

bin/main.o: src/main.c include/bmp.h
	gcc -c src/main.c -std=c99 -Wall -Werror -I include -o bin/main.o

bin/bmp.o: src/bmp.c include/bmp.h
	gcc -c src/bmp.c -std=c99 -Wall -Werror -I include -o bin/bmp.o

clean:
	rm bin/*.o main