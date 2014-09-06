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

int main ()
{
	
	println(int2bin(255));
	unsigned int u = 
	hexToInt("FF");
	
	return 0;
}
