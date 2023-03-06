test.exe : test.c BigInteger.h BigInteger.o
	gcc -std=c99 -o test.exe test.c BigInteger.o

BigInteger.o : BigInteger.c BigInteger.h
	gcc -c -std=c99 BigInteger.c
