#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


#define BLOCKSIZE(header) (header & 0xFFFFFFF8)

void printInt(char * name, int value)
{
 printf(name);
 printf(": %i \n", value);
}

void * expiriment1()
{
 size_t size = 28;
    int newsize = ALIGN(size + SIZE_T_SIZE); /* calculate size needed to allocate */
    printInt("newsize", newsize);
    
    printf("old top of heap : 0x%8x \n", sbrk(0));
    void *p = sbrk(newsize); /*grow the heap by needed size */
    printf("p0 : 0x%8x \n", p);
    if (p == (void *)-1) /*if an error occured while growing the heap, return a null pointer */
	return NULL;

    else {
        *(size_t *)p = size;
 	printf("p1 : 0x%8x \n", p);
        void * returnValue= (void *)((char *)p + SIZE_T_SIZE);
 	  printf("returnValue : 0x%8x \n", returnValue);
	return returnValue;
    }

}

void expiriment2()
{
 int hdr = 0x00000019;
 int y = BLOCKSIZE(hdr);
 printf("block size : %d \n", y);

}

int main ()
{
printf("align 30 = % i \n", ALIGN(30));

printf("SIZE_T_SIZE = %i \n", SIZE_T_SIZE);

printf("RUNNING EXPIRIMENT 1 \n");
expiriment1();

printf("RUNNING EXPIRIMENT 2 \n");
expiriment2();



}
