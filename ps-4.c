#include <stdlib.h>
#include <stdio.h>
int main ()
{

	printf(" 1, 1 : %d \n", loop(1, 1));
	printf(" 1, 2 : %d \n", loop(1, 2));
	printf(" 1, 4 : %d \n", loop(1, 4));
	printf(" 2, 1 : %d \n", loop(2, 1));
	
	return 0;
}



int switch3(int *p1, int * p2, mode_t action)
{
	int result = 0;
	
	switch(action){
		case MODE_A:
			result = *p1;
			*p1 = *p2;
			break;
		case MODE_B:
			*p1 = *p1 + *p2;
			result = *p2;
			break;
		case MODE_C:
			*p2 = 15;
			result = *p1;
			break;
		case MODE_D:
			*p2 = *p1;
			result = 17;
		case MODE_E:
			result = 17;
			break;
		default:
			result = -1;
	}
	
	return result;
	
}



int loop (int x, int n)
{
	int result = -1;
	int mask;
	for (mask = 1; mask !=0; mask = mask << (n%256))
	{
		result ^= x & mask;
		
	}
	return result;
	
	
}
