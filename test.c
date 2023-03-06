#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "BigInteger.h"

int main()
{

    { // testing the createBigInteger()
        BigInteger bigInt = createBigInteger();
        assert(bigInt != NULL);
        assert(bigInt->sign == 0);
        assert(bigInt->size == 0);
        assert(bigInt->head == NULL);
        assert(bigInt->str == NULL);
        bigIntegerFree(bigInt);
    }

    { // testing bigInt to string
        BigInteger bigInt = bigIntegerCreateFromString("12345");
        bigInt = bigIntegerAdd(bigInt, bigIntegerCreateFromString("1"));
        const char *string = bigIntegerToString(bigInt);
        assert(strcmp(string, "12346") == 0);
        bigIntegerFree(bigInt);
    }

    { // clone function test
        BigInteger bigInt1 = bigIntegerCreateFromString("12345");
        BigInteger bigInt2 = bigIntegerClone(bigInt1);
        const char *string1 = bigIntegerToString(bigInt1);
        const char *string2 = bigIntegerToString(bigInt2);
        assert(strcmp(string1, string2) == 0);
        bigIntegerFree(bigInt1);
        bigIntegerFree(bigInt2);
    }

    { // count() test
        BigInteger bigInt = bigIntegerCreateFromString("12345678910123456789");
        assert(count(bigInt) == 20);
        bigIntegerFree(bigInt);
    }

    { // makeEmpty() tests
        BigInteger bigInt = bigIntegerCreateFromString("12345");
        makeEmpty(bigInt);
        assert(bigInt->sign == 0);
        assert(bigInt->size == 0);
        assert(bigInt->head == NULL);
        assert(bigInt->str == NULL);
        bigIntegerFree(bigInt);
    }

    { // isEmpty() tests
        BigInteger bigInt = bigIntegerCreateFromString("12345");
        assert(isEmpty(bigInt) == 0);
        makeEmpty(bigInt);
        assert(isEmpty(bigInt) == 1);
        bigIntegerFree(bigInt);
    }

    { // Testing add

        BigInteger a = bigIntegerCreateFromString("1234");
        BigInteger b = bigIntegerCreateFromString("-999");
        BigInteger c = bigIntegerAdd(a, b);
        assert(c != NULL);
        assert(strcmp(bigIntegerToString(c), "235") == 0);
        bigIntegerFree(a);
        bigIntegerFree(b);
        bigIntegerFree(c);
    }

    { // testing subtract
        BigInteger a = bigIntegerCreateFromString("1234");
        BigInteger b = bigIntegerCreateFromString("-999");
        BigInteger c = bigIntegerSubtract(a, b);
        assert(c != NULL);
        assert(strcmp(bigIntegerToString(c), "2233") == 0);
        bigIntegerFree(a);
        bigIntegerFree(b);
        bigIntegerFree(c);
    }

    { // testing multiply
        BigInteger a = bigIntegerCreateFromString("123456");
        BigInteger b = bigIntegerCreateFromString("-999");
        BigInteger c = bigIntegerMultiply(a, b);
        assert(c != NULL);
        assert(strcmp(bigIntegerToString(c), "-123332544") == 0);
        bigIntegerFree(a);
        bigIntegerFree(b);
        bigIntegerFree(c);
    }

    { // testing divide and mod functions

        // Test case 1: simple division and modulo
        BigInteger a = bigIntegerCreateFromString("1111");
        BigInteger b = bigIntegerCreateFromString("10");
        BigInteger resultDivide = bigIntegerDivide(a, b);
        BigInteger resultMod = bigIntegerMod(a, b);
        assert(bigIntegerCompare(bigIntegerCreateFromString("111"), resultDivide) == 0);
        assert(bigIntegerCompare(bigIntegerCreateFromString("1"), resultMod) == 0);
        bigIntegerFree(a);
        bigIntegerFree(b);
        bigIntegerFree(resultDivide);
        bigIntegerFree(resultMod);

        // Test case 2: division by zero
        a = bigIntegerCreateFromString("1111");
        b = bigIntegerCreateFromString("0");
        resultDivide = bigIntegerDivide(a, b);
        resultMod = bigIntegerMod(a, b);
        assert(resultDivide == NULL);
        assert(resultMod == NULL);
        bigIntegerFree(a);
        bigIntegerFree(b);

        // Test case 3: division of negative numbers
        a = bigIntegerCreateFromString("-1234567890");
        b = bigIntegerCreateFromString("12345");
        resultDivide = bigIntegerDivide(a, b);
        resultMod = bigIntegerMod(a, b);
        assert(bigIntegerCompare(bigIntegerCreateFromString("-100005"), resultDivide) == 0);
        assert(bigIntegerCompare(bigIntegerCreateFromString("-6165"), resultMod) == 0);

        bigIntegerFree(a);
        bigIntegerFree(b);
        bigIntegerFree(resultDivide);
        bigIntegerFree(resultMod);
        //Test case 4: large number division
        a = bigIntegerCreateFromString("1234567891234567891");
        b = bigIntegerCreateFromString("1234567891234567891");
        resultDivide = bigIntegerDivide(a, b);
        resultMod = bigIntegerMod(a, b);
        assert(bigIntegerCompare(bigIntegerCreateFromString("1"), resultDivide) == 0);
        assert(bigIntegerCompare(bigIntegerCreateFromString("0"), resultMod) == 0);

        bigIntegerFree(a);
        bigIntegerFree(b);
        bigIntegerFree(resultDivide);
        bigIntegerFree(resultMod);
    }

	printf("All tests passed! \n");

    return 0;
}