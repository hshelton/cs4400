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

/* basic constants and macros for manipulating the free list */

#define WSIZE 4 /* word size (bytes) */
#define DSIZE 8 /* doubleword size (bytes) */
#define CHUNKSIZE (1<<12) /* initial heap size (bytes) */
#define OVERHEAD 8 /* overhead of header & footer (bytes) */

#define MAX(x, y) ((x) > (y)? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(size_t*)(p))
#define PUT(p, val) (*(size_t*)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char*)(bp) - WSIZE)
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given a free block ptr bp, compute address of its pred pointer */
#define PDRP(bp) (HDRP(bp)+4)

/* Given a free block ptr bp, compute address its successor */
#define SCRP(bp) (HDRP(bp)+8)



/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(((char*)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE(((char*)(bp) - DSIZE)))

/* the first free block in the list */
static size_t freeHead;
static size_t freeTail;


static char* heap_listp ;

static void* coalesce(void* bp);
static void* find_fit(size_t asize);
static void place(void* bp, size_t asize);
static void* extend_heap(size_t words);

/* before calling mm_malloc or mm_free, the allocator must initialize
 the heap by calling mm_init */
int mm_init(void) {
 /* create the initial empty heap – four words */
 if ((heap_listp = mem_sbrk(4*WSIZE)) == NULL)
    return -1;

 PUT(heap_listp, 0); /* alignment padding */
 PUT(heap_listp+WSIZE, PACK(OVERHEAD, 1)); /* prologue header */
 PUT(heap_listp+DSIZE, PACK(OVERHEAD, 1)); /* prologue footer */
 PUT(heap_listp+WSIZE+DSIZE, PACK(0, 1)); /* epilogue header */
 heap_listp += DSIZE; /* move heap_listp past prologue's header */

 void* heapStart;
 /* extend the empty heap with a free block of CHUNKSIZE bytes */
 if (heapStart = extend_heap(CHUNKSIZE/WSIZE) == NULL)
    return -1;

    /* set predecessor and successor to null */
    size_t successor = SCRP(heapStart);
    PUT(successor, NULL);

    size_t predecessor = PDRP(heapStart);
    PUT(predecessor, NULL);


 return 0;
}


void mm_free(void* bp) {
 size_t size = GET_SIZE(HDRP(bp));
 PUT(HDRP(bp), PACK(size, 0));
 PUT(FTRP(bp), PACK(size, 0));

 coalesce(bp);
}

static void* coalesce(void* bp) {
 size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
 size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

 size_t size = GET_SIZE(HDRP(bp));

    /* if previous and next are allocated do nothing */
    if (prev_alloc && next_alloc)

    {
    return bp;
    }


/* if next is not allocated */
 else if (prev_alloc && !next_alloc) {
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size ,0));
    /* this node's successor is the next node's */
    size_t oldSucc = SCRP(NEXT_BLKP(bp));
    PUT(SCRP(bp), oldSucc);

    return(bp);
 }

 else if (!prev_alloc && next_alloc) {
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));

    size_t oldSucc = SCRP(PREV_BLKP(bp));
    PUT(SCRP(PREV_BLKP(bp)), oldSucc);

    return(PREV_BLKP(bp));
 }
 else {
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
    GET_SIZE(FTRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    return(PREV_BLKP(bp));
 }
}

void* mm_malloc(size_t size) {
 size_t asize; /* adjusted block size */
 size_t extendsize; /* amount to extend heap if no fit */
 char* bp;

 /* Ignore spurious requests */
 if (size <= 0)
    return NULL;

 /* Adjust block size to include overhead and alignment reqs */
 if (size <= DSIZE)
    asize = DSIZE + OVERHEAD;
 else
    asize = DSIZE * ((size + (OVERHEAD) + (DSIZE-1)) / DSIZE);

 /* Search the free list for a fit */
 if ((bp = find_fit(asize)) != NULL) {
    place(bp, asize);
    return bp;
 }
 /* No fit found. Get more memory and place the block */
 extendsize = MAX(asize,CHUNKSIZE);
 if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
    return NULL;
 place(bp, asize);
 return bp;
}

static void* find_fit(size_t asize) {
 void* bp;

 /* first fit search */
 for(bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
    if(!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
    return bp;
    }
 }
 return NULL; /* no fit */
}
static void place(void* bp, size_t asize) {

 size_t csize = GET_SIZE(HDRP(bp));

 if((csize - asize) >= (DSIZE + OVERHEAD)) { /* if new free block */
    PUT(HDRP(bp), PACK(asize, 1)); /* would be at least */
    PUT(FTRP(bp), PACK(asize, 1)); /* as big as min */
    bp = NEXT_BLKP(bp); /* block size, split */
    PUT(HDRP(bp), PACK(csize-asize, 0));
    PUT(FTRP(bp), PACK(csize-asize, 0));
 }
 else { /* else, do not split */
    PUT(HDRP(bp), PACK(csize, 1));
    PUT(FTRP(bp), PACK(csize, 1));
 }
}

void* mm_realloc(void *ptr, size_t size)
{
    if(ptr == NULL)
    return mm_malloc(size);

    if (size == 0)
    {
    mm_free(ptr);
    return mm_malloc(size);
    }

    /*

– contents	of	the	new	block	are	the	same	as	those	of	the	old
ptr	block,	up	to	the	minimum	of	the	old	and	new	size
*/
    /*just free pointer and call mm_malloc for now */
    /*
    mm_free(ptr);
    return mm_malloc(size) */

    /* otherwise, we have a previously allocated chunk of memory, if it's big enough reuse it */

    size_t oldHeader= HDRP(ptr);
    if(GET_SIZE(oldHeader)>= size)
    {
    /* update size of resused header */
    PUT(HDRP(ptr), PACK(size, 1));
    PUT(FTRP(ptr), PACK(size, 1));
    return ptr;
    }
    else
    {
     size_t sz = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(sz, 0));
    PUT(FTRP(ptr), PACK(sz, 0));

        return mm_malloc(size);
    }




}

/* extend the heap by CHUNKSIZE bytes and creates the initial free block */
static void* extend_heap(size_t words)
{
    char * bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words %2) ? (words +1) * WSIZE : words * WSIZE;

    if((long) (bp = mem_sbrk(size)) ==-1 )
        return NULL;
    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0)); /*Free block header */
    PUT(FTRP(bp), PACK(size, 0)); /* Free block Footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0,1)); /* New epilogue header */

    /* coalesce if the previous block was free */
    return coalesce (bp);






}

