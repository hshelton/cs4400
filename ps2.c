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

//We know wheter the result should be negative or positive for all subtraction operations
//with any positive or negative combination of x and y. If the result after subtraction 
//is not what is mathematically expected, overflow has occured, and it is not safe to do 
//that operation. 
int tsub_ok (int x, int y)
{

	int z = x-y;
	int result;
	
	
	if (x >= 0)
	{
		
		if(y >= 0)
		{
		
	
			result = z <=x ? 1 : 0;

		}
		else
		{
			
			result = z > x ? 1 : 0;
					
		}
	}
	else
	{

		if (y >=0)
		{
			result = z <=x ? 1 : 0;
		}
		
		
		else
		{
			result = z > x ? 1 : 0;

		}
		
	}
	return result;
}


int main ()
{

	//int max = 2147483647;
	
	int x = - 2147483647;
	int y = -2;
	printf("%s \n", int2bin(x-y));
	printf("%d \n", tsub_ok(x,y));

	
	
}
