#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>

/* code referenced from https://www.cs.purdue.edu/homes/fahmy/cs503/mmap.txt 
 * Given an input file hello.txt that consists of "Hello, world!\n", change
 * it to "Jello, world!\n" using mmap
 * 
 * */
int main(int argc, char * argv[])
{
 int fdin, fdout;
 char *src, *dst;

mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

/* open file from command line arg */
fdin = open(argv[1], O_RDWR);
	
fdout = open ("temp3242.txt", O_RDWR | O_CREAT | O_TRUNC, mode);
		
/* throw a J in the temp file */
if(write(fdout, "J", 1) <1)
printf("write error ");

/* map source of char to copy */
 if ((src = mmap (0, 1, PROT_READ, MAP_SHARED, fdout, 0))
   == (caddr_t) -1)
   printf ("mmap error for input \n");
   
/* map first byte of dst */
 if ((dst = mmap (0, 1, PROT_READ | PROT_WRITE,
   MAP_SHARED, fdin, 0)) == (caddr_t) -1)
	printf ("mmap error for output \n");

	 /* this copies the J from temp to hello.txt */
	memcpy (dst, src, 1);
	
	/* remove temp */
	remove("temp3242.txt");
return 0;	
}
