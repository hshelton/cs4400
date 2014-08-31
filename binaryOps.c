#include <stdio.h>
#include <limits.h>





void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = b[i] & (1<<j);
            byte >>= j;
            printf("%u", byte);
        }
    }
    puts("");
}




int main ()
{

	int x = 10;	
	int test2= ~0;
	int test3=256;

	printf("%d \n", atLeastOneZero(x));
	
	printf("%d \n", LSBContainsOne(test3));
	
	printf("%d \n", MSBContainsZero((test3)));
	return 0;

}



//A. Any bit of x equals 1
int atLeastOneOne (int x)
{
	return x&&1;
}
//B. Any bit of x equals 0
int atLeastOneZero(int x)
{
	//if there are any zeros the logical value of res will be true
	int res = x ^ (~0);
	
	return res &&1 ;
	
}
//C. Any bit in the LSB equals 1
int LSBContainsOne (int x)
{
	//ignore all bits but those from the least significant byte
	int shifted = (x) <<24;

	return shifted &&1;
}

//D. Any bit in the MSB equals 0
int MSBContainsZero (int x)
{
	//get most significant byte (code from pg 121 Computer Systems Textbook)
	int shift_val = (sizeof(int)-1)<<3;
	int xright = x >>shift_val;
	int xBit = xright & 0xFF;
	
	int notXBit = ~xBit;
	int max = ~0;
	
	//XOR maximum value with not xBit, if the result of this has a logical value of 1,
	// then there must have been a zero in the xBit
	int res = notXBit ^ max;
	
	return !res &&1;
}


int int_shifts_are_arithmetic()
{
	
	//max is largest possible integer (111111...)
	int max = ~0;
	int shifted = (max)>>1;
	//bitwise XOR shifted with max
	
	int res = shifted ^ max;
	//if the machine uses arithmetic right shifts, then all the bits in res will be zero
	return !res &&1;

}
