#include <stdio.h>

int main ()
{
	int num = 10;
	int* ptr = &num; //int pointer ptr is pointing to the memory address of num
	*ptr = 3; //contents of memory address of ptr is now 3
	int * ptr1, *ptr2; //you have to declare multiple pointers this way
	
	float rates[100]; //rates is an array of 100 floats (rates is now a pointer to the first address of the chunk
	//of memory where rates begins. (rates is allocated to sizeof(float) * 100
	float *ptr;
	ptr = rates; /*needs no & */
	
	//dynamically allocated memory
	int x = count_of_bytes_given_by_user;
	int* my_array = malloc(x);
	//my_array is the address of the first element. my_array+1 is adress of second
	
	float nums [] = {1.2, 1.3, 5.6};
	float* p1 = nums;
	float *p2 = p1+2;
	//value of p2 = 5.6
	//p1 is less than 
	
	int x = 16;
	float result = x/4.0; //x is converted to 16.0 before the division occurs
	
	//types only get promoted to those that support higher precision (for the most part)
	
	float a, b;
	int c, d;
	
	b = 1.0;
	c = -5;
	d = 2;
	
	a = b * (c/d); // a is -2.0
	a = b * ((float) c /d ); // a is -2.5
	a = b/c * d; // a is -0.4
	a = (int) (b/c) * d; // a is 0.0
	//numbers are rounded down by default 
	
	
	
	
	
	
	//printf("%f \n", test);
	
	
	
	
	
	
	
	
	
}
