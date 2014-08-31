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

	
	return 0;

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
