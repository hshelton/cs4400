/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
  "Hayden Shelton",     /* Student full name */
  "hshelton",    /* Student CADE login */
  "hayden.shelton@utah.edu",  /* Student email address */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
  int i, j;
  
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(j, dim-1-i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "4 way unrolling and reduced calculations";

/* Computes the result of rotating the image src by 90 deg and stores the
 * result in destination image dst. dim is the dimension of the image */
void test2_rotate(int dim, pixel *src, pixel *dst) 
{
  int i, j, k, k2, l, pos,  si;

  int limit = dim -7;
/* perform 8 way loop unrolling and create local varables to reduce loads */
  for (i = 0; i < limit; i+=8)
    {
		    for (j = 0;j < dim; j++)
		    {
				
		                k =i;
				l= dim -1 -i;
			        pos =(j * dim) + l;
				si= (k * dim) + j;
				
				dst[pos--] =src[si];
				
				
				si +=dim;
		
				dst[pos--] = src[si];
				
				
				si += dim;
				dst[pos--] = src[si];
			       
				
				si += dim;
				dst[pos--] = src[si];
			       
			       
				si += dim;
				dst[pos--] = src[si];
				
   			        
				si += dim;
				dst[pos--] = src[si];
				
				si += dim;
				
				dst[pos--] = src[si];
			        
				
				si += dim;
				dst[pos] = src[si];
	
			}

	}
	
	
	
  
}

/* 
 *  
 */
char test1_rotate_descr[] = "test1_rotate: test 4way unroll w/  i & j swapped";
void test1_rotate(int dim, pixel *src, pixel *dst) 
{

  int i, j, k, k2, l, pos,  si;

  int limit = dim -3;
  /* perform 4 way loop unrolling and reduced calculations */

      for (j = 0;j < dim; j++)
	{
	for(i =0; i <limit; i+=4)
        {
          l= dim -1 -i;
          pos =(i * dim) + l;
          si= (j * dim) + i;
          dst[pos--] =src[si];
          si +=dim;
          dst[pos--] = src[si];
          si += dim;
          dst[pos--] = src[si];
          si += dim;
          dst[pos--] = src[si];
        }
    }


}

char test2_rotate_descr[] = "test2_rotate: 8 way unrolling";
void rotate(int dim, pixel *src, pixel *dst) 
{
   int i, j, k, k2, l, pos,  si;

  int limit = dim -3;
/* perform 4 way loop unrolling and reduced calculations */
  for (i = 0; i < limit; i+=4)
    {
        for (j = 0;j < dim; j++)
        {              
        l= dim -1 -i;
        pos =(j * dim) + l;
        si= (i * dim) + j;
        dst[pos--] =src[si];
        si +=dim;
        dst[pos--] = src[si];
        si += dim;
        dst[pos--] = src[si];
        si += dim;
        dst[pos--] = src[si];
            
      }

  }
  
  
}



/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
  add_rotate_function(&naive_rotate, naive_rotate_descr);   
  add_rotate_function(&rotate, rotate_descr);   
  add_rotate_function(&test1_rotate, test1_rotate_descr);  
  add_rotate_function(&test2_rotate, test2_rotate_descr);
  /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
  int red;
  int green;
  int blue;
  int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
  sum->red = sum->green = sum->blue = 0;
  sum->num = 0;
  return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
  sum->red += (int) p.red;
  sum->green += (int) p.green;
  sum->blue += (int) p.blue;
  sum->num++;
  return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
  current_pixel->red = (unsigned char) (sum.red/sum.num);
  current_pixel->green = (unsigned char) (sum.green/sum.num);
  current_pixel->blue = (unsigned char) (sum.blue/sum.num);
  return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
  int ii, jj;
  pixel_sum sum;
  pixel current_pixel;
  
  
  
  initialize_pixel_sum(&sum);
  for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
    for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) {
      accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
      // "weighted" averge: add (i,j) pixel to sum twice
      if(ii == i && jj == j)
	accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
    }
  
  assign_sum_to_pixel(&current_pixel, sum);
  
  return current_pixel;
}
static pixel check_average(int dim, int i, int j, pixel *src) {
  pixel result;
  int num = 0;
  int ii, jj;
  int sum0, sum1, sum2;
  int top_left_i, top_left_j;
  int bottom_right_i, bottom_right_j;

  top_left_i = max(i-1, 0);
  top_left_j = max(j-1, 0);
  bottom_right_i = min(i+1, dim-1); 
  bottom_right_j = min(j+1, dim-1);

  sum0 = sum1 = sum2 = 0;
  for(ii=top_left_i; ii <= bottom_right_i; ii++) {
    for(jj=top_left_j; jj <= bottom_right_j; jj++) {
      num++;
      sum0 += (int) src[RIDX(ii,jj,dim)].red;
      sum1 += (int) src[RIDX(ii,jj,dim)].green;
      sum2 += (int) src[RIDX(ii,jj,dim)].blue;
    }
  }
  // average is weighted, add pixel value at (i,j) again
  sum0 += (int) src[RIDX(i,j,dim)].red;
  sum1 += (int) src[RIDX(i,j,dim)].green;
  sum2 += (int) src[RIDX(i,j,dim)].blue;
  num++;
  result.red = (unsigned char) (sum0/num);
  result.green = (unsigned char) (sum1/num);
  result.blue = (unsigned char) (sum2/num);
  
  return result;
}
/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg2(int dim, int i, int j, pixel *src) 
{

  pixel cp1;
  pixel cp2;
  pixel result;
  int redSum, greenSum, blueSum, num;
  
  redSum = greenSum = blueSum = 0;
        
	cp1 = src[RIDX(i-1, j-1, dim)];
	cp2 = src[RIDX(i-1, j, dim)];
	
	redSum+= (int)cp1.red;
	greenSum +=(int)cp1.green;
	blueSum+= (int)cp1.blue;
	redSum+= (int)cp2.red;
        greenSum +=(int)cp2.green;
        blueSum+= (int)cp2.blue;

        cp1 = src[RIDX(i-1, j+1, dim)];
        cp2 = src[RIDX(i,j-1, dim)];

        redSum+= (int)cp1.red;
        greenSum +=(int)cp1.green;
        blueSum+= (int)cp1.blue;
        redSum+= (int)cp2.red;
        greenSum +=(int)cp2.green;
        blueSum+= (int)cp2.blue;

	cp1 = src[RIDX(i, j, dim)];
        cp2 = src[RIDX(i, j+1, dim)];

	/* add i,j twice */
        redSum+= (int)(cp1.red *2);
        greenSum +=(int)(cp1.green *2);
        blueSum+= (int)(cp1.blue *2);

        redSum+= (int)cp2.red;
        greenSum +=(int)cp2.green;
        blueSum+= (int)cp2.blue;

	
	cp1 = src[RIDX(i+1, j-1, dim)];
        cp2 = src[RIDX(i+1, j, dim)];

        redSum+= (int)cp1.red;
        greenSum +=(int)cp1.green;
        blueSum+= (int)cp1.blue;
        redSum+= (int)cp2.red;
        greenSum +=(int)cp2.green;
        blueSum+= (int)cp2.blue;
	
	cp1 = src[RIDX(i+1, j+1, dim)];

	redSum+= (int)cp1.red;
        greenSum +=(int)cp1.green;
        blueSum+= (int)cp1.blue;

       
	 	
	result.red = (unsigned char) (redSum/10);
	result.blue = (unsigned char) (blueSum /10);
	result.green = (unsigned char) (greenSum /10);
	
	return result;
  

}


/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
  int i, j;
  
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "Hayden's Optimized smooth";
void smooth(int dim, pixel *src, pixel *dst) 
{
	
  int i, j, k;
  k = dim-1;
   // smoothing of edge squares as a special case 
  // row 
  for(i = 0; i < dim ; i++)
  {
	  dst[RIDX(0, i, dim)] = avg(dim, 0, i, src);
  }
  
    /* first column */
  for(i = 0; i < dim ; i++)
  {
	  dst[RIDX(i, 0, dim)] = avg(dim, i, 0, src);
  }
  
     /* last colum */
  for(i = 0; i < dim ; i++)
  {
	  dst[RIDX(i, dim-1, dim)] = avg(dim, i, dim-1, src);
  }
  
  //bottom row
    for(i = 0; i < dim ; i++)
  {
	  dst[RIDX(dim-1, i, dim)] = avg(dim, dim-1, i, src);
	
  }
  
  for (i = 1; i < k  ; i++)
    for (j = 1; j < k ; j++)
    {
      dst[RIDX(i, j, dim)] = avg2(dim, i, j, src);
      
  }
  
   // int i, j;
  
 // for (i = 0; i < dim; i++)
  //  for (j = 0; j < dim; j++)
    //  dst[RIDX(i, j, dim)] = check_average(dim, i, j, src);

}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
  add_smooth_function(&smooth, smooth_descr);
  add_smooth_function(&naive_smooth, naive_smooth_descr);
  /* ... Register additional test functions here */
}
