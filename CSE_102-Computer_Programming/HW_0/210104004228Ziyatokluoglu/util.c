#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = (n1*d2) - (n2*d1);
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*n2;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = d1*n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
	
	int Gcd= 1; /* greatest common divisor */
	int i=1;
	int sign_n = 1; /* integer's sign of numerator (positive or negative)*/
	int sign_d = 1; /* integer's sign of denominator (positive or negative) */
	
	if (*n < 0) /*to find Gcd, negative integer convert to positive */
	{
		sign_n = -1;
		*n *= -1;
	}
	if (*d < 0) /*to find Gcd, negative integer convert to positive */
	{
		sign_d = -1;
		*d *= -1;
	}
	while(i <= *n || i <= *d) /* control the biggest divider for each number(common) and assign to Gcd*/
	{
		if ( *n%i == 0 && *d%i == 0)
		{
			Gcd = i;
		}	
	i++;
	}
	*n = *n/(sign_n*Gcd);  /* to simplfy, diveded by Gcd and sign (to given correct sign to integer) */
	*d = *d/(sign_d*Gcd);	/* to simplfy, diveded by Gcd and sign (to given correct sign to integer) */
	if( *d < 0) 
	{
		*d *= -1;
		*n *= -1;
	}
		
} /* end fraction_simplify */
