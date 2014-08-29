
//Hayden Shelton CS4400 Fall 2014
#include <stdio.h>

	int main ()
	{
		printf("%d \n", stringLength("1"));
		printf("%d \n", stringLength("to"));
		printf("%d \n", stringLength("tri"));
		printf("%d \n", stringLength("four"));		
		printf("%d \n", stringLength("fives"));
		printf("%d \n", stringLength("0123456789"));
		
		return 0;
	}

	//return number of characters in a string
	int stringLength (char* input)
	{
		int i = 0;
		while(input[i] != '\0')
		{
			i++;
		}
		return i;
	}
