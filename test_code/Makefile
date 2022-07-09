#HEADERS = test.h headers.h

default: test

#test.o: test.c $(HEADERS)
test.o: test.c
	gcc -c test.c -o test.o

test: test.o
	gcc test.o -o test

clean:
	-rm -f test.o
	-rm -f test
