/*
 * =====================================================================================
 *
 *       Filename:  median.c
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  10.04.2019 18:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Patrick Erdmann
 *   Organization:  -
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

static int cmp_double (const void * a, const void * b)
{
    if (*(double*)a > *(double*)b) return 1;
    if (*(double*)a < *(double*)b) return -1;

    return 0;
}

double get_median(double array[], int size_array)
{
    qsort(array, size_array, sizeof(double), cmp_double);
    return array[size_array / 2];
}
