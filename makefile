CFLAGS = -Wall -g

all:
	cc ex1.c -o ex1
	cc ex3.c -o ex3
	cc ex4.c -o ex4
	cc ex5.c -o ex5
	cc ex6.c -o ex6
	cc ex7.c -o ex7
	cc ex8.c -o ex8
	cc ex9.c -o ex9
	cc ex10.c -o ex10
	cc ex14.c -o ex14
	cc ex15.c -o ex15
	cc ex16.c -o ex16
	cc ex17.c -o ex17
	cc ex18.c -o ex18

ex1:
	cc ex1.c -o ex1

ex3:
	cc ex3.c -o ex3

clean:
	rm -f ex1
	rm -f ex3
	rm -f ex4
	rm -f ex5
	rm -f ex6
	rm -f ex7
	rm -f ex8
	rm -f ex9
	rm -f ex10
	rm -f ex14
	rm -f ex15
	rm -f ex16
	rm -f ex17
	rm -f ex18
