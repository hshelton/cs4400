#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

char * int2bin(int i)
{
    size_t bits = sizeof(int) * CHAR_BIT;

    char * str = malloc(bits + 1);
    if(!str) return NULL;
    str[bits] = 0;

    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&i;
    for(; bits--; u >>= 1)
    	str[bits] = u & 1 ? '1' : '0';

    return str;
}

void println (char * str)
{
	printf("%s \n", str);
	
	
}

int hexToInt( char * hex)
{
	char * end;
	//string to long
	long int li1 = strtol(hex, end, 16);
	printf("%ld \n", li1);
	return li1;
}



/*END OF HELPER FUNCITONS ************************** */
 






typedef unsigned packed_t; //packed two's complement number


int xbyte (packed_t word, int bytenum)
{
		println(int2bin(word));
	//get # of bits to shift over so that word[bytenum] is in slot 0
	int pos = bytenum <<3;

	
	//shift over by pos
	int relavantBytes = (word >> pos);
	
	//if the word is negative we need to do more work?

	//println(int2bin(sign));
	
	
}


int tsub_ok (int x, int y)
{
	
	
	
	
}

int divide_power2(int x, int k)
{
	
	return x >>k;
	
}






















int main ()
{
	int test = 65;
	int result = divide_power2(test, 3);
	printf("%d \n", result);
	
	return 0;
}
