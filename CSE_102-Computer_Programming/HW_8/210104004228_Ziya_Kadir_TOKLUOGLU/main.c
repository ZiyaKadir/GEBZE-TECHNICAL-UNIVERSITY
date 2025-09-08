#include <stdio.h>
#include <stdlib.h>
#include "util.h"


int main() {

  int seqlen;
  int xs;
  int looplength;
  int control=0;
  int *cont=&control;
  int i,digit=0;

  printf("Please enter the sequence length:");
  scanf("%d",&seqlen);
  printf("Please enter the first element:");
  scanf("%d",&xs);

  int *loop = (int *) malloc(seqlen * sizeof(int));
  int *looplen;
  int *h=(int *)malloc(9*sizeof(int));
  looplen=&looplength;

  /* the begining of the looplen checking the half of the length of sequence*/
  *looplen=seqlen/2;

  check_loop_iterative(generate_sequence, xs,seqlen,loop,looplen);

  /*print the loop*/
  if((*looplen)>=2){
  printf("Loop:{");
  for(i=0; i<(*looplen)-1;i++) printf("%d, ",loop[i]);
  printf("%d}\n",loop[i]);
  }
  else printf("No loop found\n");

  /* print the histogram */
  hist_of_firstdigits(generate_sequence,xs,seqlen,h,digit);

  printf("\nHistaogram of the sequence:{");
  for(i=0; i<8;i++) printf("%d, ",h[i]);
  printf("%d}\n",h[i]);

    return 0;
}
