#include <stdio.h>
#include "stdafx.h"
#include <iostream>


int main ()
{
	
	int test = 17;
	int notX = ~test;
	int w = sizeof(test <<3);
	
	int operand = 0<<w;
	
	std::cout<< std::bitset<32>(w);


	
	return 0;
	
	
}



void printInt(int input)
{
	
	
	printf("%d \n", input);	
	
}
