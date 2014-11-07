/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following student struct
 */
student_t student =
{
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


char test_rotate1_descr[] = "test_rotate1 - 4way inner unrolling";
void test_rotate1(int dim, pixel *src, pixel *dst)
{
    int i, j, l, jj, idim;

    int limit = dim -3;

    /* perform 4 way loop unrolling (inner) and reduced calculations */
    for (i = 0; i < dim; i++)
    {
        l= dim -1 -i;
        idim = i*dim;
        for (j = 0; j < limit; j+=4)
        {
            jj=j;
            dst[(jj*dim +l)] = src[(idim + jj)];
            jj++;
            dst[(jj*dim +l)] = src[(idim + jj)];
            jj++;
            dst[(jj*dim +l)] = src[(idim + jj)];
            jj++;
            dst[(jj*dim +l)] = src[(idim + jj)];


        }



    }


}



/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = " Hayden's optimized rotate";

/* Computes the result of rotating the image src by 90 deg and stores the
 * result in destination image dst. dim is the dimension of the image */
void rotate(int dim, pixel *src, pixel *dst)
{
    int i, j, l, pos,  si;

    int limit = dim -7;

    /* perform 8 way loop unrolling, reduced loads, reduced calculations */
    for (i = 0; i < limit; i+=8)
    {
        l= dim -1 -i;

        for (j = 0; j < dim; j++)
        {
            si= i * dim + j;
            pos =(j * dim) + l;

            dst[pos--] =src[si];

            dst[pos--] = src[si + dim ];

            dst[pos--] = src[si + dim *2];

            dst[pos--] = src[si + dim *3];

            dst[pos--] = src[si + dim *4];

            dst[pos--] = src[si + dim *5];

            dst[pos--] = src[si + dim *6];

            dst[pos--] = src[si + dim *7];
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
    add_rotate_function(&test_rotate1, test_rotate1_descr);
    ;
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
typedef struct
{
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b)
{
    return (a < b ? a : b);
}
static int max(int a, int b)
{
    return (a > b ? a : b);
}

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
        for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++)
        {
            accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
            // "weighted" averge: add (i,j) pixel to sum twice
            if(ii == i && jj == j)
                accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
        }

    assign_sum_to_pixel(&current_pixel, sum);

    return current_pixel;
}
static pixel check_average(int dim, int i, int j, pixel *src)
{
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
    for(ii=top_left_i; ii <= bottom_right_i; ii++)
    {
        for(jj=top_left_j; jj <= bottom_right_j; jj++)
        {
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

static pixel avg3(int dim, int i, int j, pixel * src)
{
    pixel cp1;


    int redSum, greenSum, blueSum, pos, upleft, pos2;

    redSum = greenSum = blueSum = 0;
    upleft= RIDX((i-1),(j-1),dim);



    /* same row */
    pos = pos2 = upleft + dim;
    redSum += (int)src[pos2++].red;
    greenSum += (int)src[pos].green;
    blueSum += (int)src[pos++].blue;

    /* add i,j twice */
    redSum += (int)src[pos2++].red *2;
    greenSum += (int)src[pos].green *2;
    blueSum += (int)src[pos].blue *2;

    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2].green;
    blueSum += (int)src[pos2].blue;




    pos = pos2 = upleft;

    /* row above */
    redSum += (int) src[pos].red;
    greenSum += (int) src[pos2++].green;
    blueSum += (int) src[pos++].blue;

    redSum += (int) src[pos2++].red;
    greenSum += (int) src[pos].green;
    blueSum += (int)src[pos++].blue;

    redSum += (int)src[pos2].red;
    greenSum +=(int) src[pos2].green;
    blueSum += (int)src[pos2].blue;



    /* row below */
    pos= pos2 = upleft + dim*2;
    redSum += (int)src[pos].red;
    greenSum += (int)src[pos2++].green;
    blueSum += (int)src[pos++].blue;

    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2++].green;
    blueSum += (int)src[pos].blue;

    redSum += (int)src[pos2].red;

    greenSum += (int)src[pos2].green;

    blueSum += (int)src[pos2].blue;

    cp1.red = (unsigned char) (redSum/10);
    cp1.green = (unsigned char) (greenSum /10);
    cp1.blue = (unsigned char) (blueSum /10);




    return cp1;
}

/*
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

/* strategy was to reduce number of computations and method calls, ugly mess, but faster */
    int i, j, k, limit;
    k = dim-1;
    limit= k-1;
    pixel cp1;

    for (i = 1; i < k  ; i++)
    {

        /* line below is most of first column */

        j =0;
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
    for(ii=top_left_i; ii <= bottom_right_i; ii++)
    {
        for(jj=top_left_j; jj <= bottom_right_j; jj++)
        {
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
    cp1.red = (unsigned char) (sum0/num);
    cp1.green = (unsigned char) (sum1/num);
    cp1.blue = (unsigned char) (sum2/num);


    dst[i *dim] = cp1;




         /*main part */
        for (j = 1; j < limit; j+=2)
        {


             int redSum, greenSum, blueSum, pos, upleft, pos2;

/* this disgusting mess replaces two function calls to get average */
    redSum = greenSum = blueSum = 0;
    upleft= RIDX((i-1),(j-1),dim);



    /* same row */
    pos = pos2 = upleft + dim;
    redSum += (int)src[pos2++].red;
    greenSum += (int)src[pos].green;
    blueSum += (int)src[pos++].blue;

    /* add i,j twice */
    redSum += (int)src[pos2++].red *2;
    greenSum += (int)src[pos].green *2;
    blueSum += (int)src[pos].blue *2;
    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2].green;
    blueSum += (int)src[pos2].blue;

    pos = pos2 = upleft;
    /* row above */
    redSum += (int) src[pos].red;
    greenSum += (int) src[pos2++].green;
    blueSum += (int) src[pos++].blue;
    redSum += (int) src[pos2++].red;
    greenSum += (int) src[pos].green;
    blueSum += (int)src[pos++].blue;
    redSum += (int)src[pos2].red;
    greenSum +=(int) src[pos2].green;
    blueSum += (int)src[pos2].blue;

    /* row below */
    pos= pos2 = upleft + dim*2;
    redSum += (int)src[pos].red;
    greenSum += (int)src[pos2++].green;
    blueSum += (int)src[pos++].blue;
    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2++].green;
    blueSum += (int)src[pos].blue;
    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2].green;
    blueSum += (int)src[pos2].blue;
    cp1.red = (unsigned char) (redSum/10);
    cp1.green = (unsigned char) (greenSum /10);
    cp1.blue = (unsigned char) (blueSum /10);
 dst[i*dim +j] = cp1;

j++;
redSum = greenSum = blueSum = 0;
    upleft= RIDX((i-1),(j-1),dim);
    /* same row */
    pos = pos2 = upleft + dim;
    redSum += (int)src[pos2++].red;
    greenSum += (int)src[pos].green;
    blueSum += (int)src[pos++].blue;
    /* add i,j twice */
    redSum += (int)src[pos2++].red *2;
    greenSum += (int)src[pos].green *2;
    blueSum += (int)src[pos].blue *2;
    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2].green;
    blueSum += (int)src[pos2].blue;
    pos = pos2 = upleft;
    /* row above */
    redSum += (int) src[pos].red;
    greenSum += (int) src[pos2++].green;
    blueSum += (int) src[pos++].blue;
    redSum += (int) src[pos2++].red;
    greenSum += (int) src[pos].green;
    blueSum += (int)src[pos++].blue;
    redSum += (int)src[pos2].red;
    greenSum +=(int) src[pos2].green;
    blueSum += (int)src[pos2].blue;

    /* row below */
    pos= pos2 = upleft + dim*2;
    redSum += (int)src[pos].red;
    greenSum += (int)src[pos2++].green;
    blueSum += (int)src[pos++].blue;
    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2++].green;
    blueSum += (int)src[pos].blue;
    redSum += (int)src[pos2].red;
    greenSum += (int)src[pos2].green;
    blueSum += (int)src[pos2].blue;
    cp1.red = (unsigned char) (redSum/10);
    cp1.green = (unsigned char) (greenSum /10);
    cp1.blue = (unsigned char) (blueSum /10);
 dst[i*dim +j] = cp1;
 j--;

        }


        /* most of last column */


     num = 0;


    top_left_i = max(i-1, 0);
    top_left_j = max(j-1, 0);
    bottom_right_i = min(i+1, dim-1);
    bottom_right_j = min(j+1, dim-1);

    sum0 = sum1 = sum2 = 0;
    for(ii=top_left_i; ii <= bottom_right_i; ii++)
    {
        for(jj=top_left_j; jj <= bottom_right_j; jj++)
        {
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
    cp1.red = (unsigned char) (sum0/num);
    cp1.green = (unsigned char) (sum1/num);
    cp1.blue = (unsigned char) (sum2/num);

 dst[i *dim +k] = cp1;


    }

    /* first and last row */
    for(i = 0; i < dim ; i++)
    {

            int num = 0;
    int ii, jj;
    int sum0, sum1, sum2;
    int top_left_i, top_left_j;
    int bottom_right_i, bottom_right_j;
    int j = i;
    int i1 = 0;

    top_left_i = max(i1-1, 0);
    top_left_j = max(j-1, 0);
    bottom_right_i = min(i1+1, dim-1);
    bottom_right_j = min(j+1, dim-1);

    sum0 = sum1 = sum2 = 0;
    for(ii=top_left_i; ii <= bottom_right_i; ii++)
    {
        for(jj=top_left_j; jj <= bottom_right_j; jj++)
        {
            num++;
            sum0 += (int) src[RIDX(ii,jj,dim)].red;
            sum1 += (int) src[RIDX(ii,jj,dim)].green;
            sum2 += (int) src[RIDX(ii,jj,dim)].blue;
        }
    }
    // average is weighted, add pixel value at (i,j) again
    sum0 += (int) src[j].red;
    sum1 += (int) src[j].green;
    sum2 += (int) src[j].blue;
    num++;
    cp1.red = (unsigned char) (sum0/num);
    cp1.green = (unsigned char) (sum1/num);
    cp1.blue = (unsigned char) (sum2/num);

 dst[j] = cp1;



         dst[k*dim+i] = check_average(dim, k, i, src);
    }








}




/*
 * smooth - another test
 *
 */
char smooth3_descr[] = "using av3";
void smooth3(int dim, pixel *src, pixel *dst)
{
    int i, j, k, idim;
    k = dim-1;
    // smoothing of edge squares as a special case



    /* this will take care of most entries */

    for (i = 1; i < k  ; i++)
    {
        idim = i *dim;
        for (j = 1; j < k ; j++)
        {

            dst[idim + j] = avg3(dim, i, j, src);

        }
    }


    /* first column */
    for(i = 0; i < dim ; i++)
    {
        dst[RIDX(i, 0, dim)] = check_average(dim, i, 0, src);
    }
    // first row
    for(i = 0; i < dim ; i++)
    {
        dst[RIDX(0, i, dim)] = check_average(dim, 0, i, src);
    }


    /* last column */
    for(i = 0; i < dim ; i++)
    {
        dst[RIDX(i, k, dim)] = check_average(dim, i, k, src);
    }
    //bottom row
    for(i = 0; i < dim ; i++)
    {
        dst[RIDX(k, i, dim)] = check_average(dim, k, i, src);
    }




}

/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_smooth_functions()
{
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    add_smooth_function(&smooth3, smooth3_descr);
    /* ... Register additional test functions here */
}
