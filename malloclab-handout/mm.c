/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "MallocBosses",
    /* First member's full name */
    "Hayden Shelton",
    /* First member's email address */
    "hayden.shelton@utah.edu",
    /* Second member's full name (leave blank if none) */
    "Vince Oveson",
    /* Second member's email address (leave blank if none) */
    "vince.oveson@utah.edu"
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define MAXSIZE 536870912

size_t heapStart;
size_t heapEnd;


/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{


    return 0;
}


/*
 * Original mm_init
 */
int mm_init_original(void)
{

    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 *
 *
 */
void *mm_malloc(size_t size)
{
    /* using block format of lecture slide */

}
/*
* Original mm_malloc
* note: size_t is basically just an unsigned integer
 */
void *mm_malloc_original(size_t size)
{
    int newsize = ALIGN(size + SIZE_T_SIZE); /* calculate size needed to allocate. round size to nearest 8, and add 8 - why the extra padding?*/
    void *p = mem_sbrk(newsize);  /*grow the heap by needed size */
    if (p == (void *)-1) /*if an error occured while growing the heap, return a null pointer */
	return NULL;

    else {
        *(size_t *)p = size; /*cast p to unsigned and set it to top of heap */
        return (void *)((char *)p + SIZE_T_SIZE); /*the heap is now grown by ALIGN(size) + 8 . Return a pointer to the top of the
        * heap + 8, presumably, the padding is to avoid overwiting data */
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{

}

/*
 * Original mm_free.
 */
void mm_free_original(void *ptr)
{

}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}

/*
 * original mm_realloc
 */
void *mm_realloc_original(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}

/*
* Heap Consistency Checker - might chck things such as:
* Is every block in the free list marked as free?
* Are there any contiguous blocks that somehow escaped coalescing?
* Is every free block actually in the free list?
* Do the pointers in the free list point to valid free blocks?
* Do any allocated blocks overlap?
* Do the pointers in a heap block point to valid heap addresses?
*/
int mm_check(void)
{





}













