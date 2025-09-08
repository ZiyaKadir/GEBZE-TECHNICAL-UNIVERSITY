#include <stdio.h>
#include "util.h"
#include <stdlib.h>



void generate_sequence (int xs, int currentlen, int seqlen, int *seq){

  currentlen++;
  seq[currentlen-1]=xs; /* the number assigned to seq[] index*/
   /* implementing valid function*/
  if(xs%2==1) xs= 3*xs+1;
  else if(xs%2==0) xs /=2;

  if(currentlen==seqlen) return;
  else return generate_sequence(xs,currentlen,seqlen,seq); /* the all numbers assigned to integer array with recursion*/
}

void check_loop_iterative(void (*f)(int xs, int currentlen,int seqlen,int *seq),int xs, int seqlen, int *loop, int *looplen){

    int i;
    int start, end,check; /*start end last index*/
    int *ls=&start,*le=&end; /* adress of the start end last index assigned to pointer valiable*/
    int *seq=(int*)malloc(seqlen*sizeof(int)); /* allocation with approperiate field*/
    f(xs,0,seqlen,seq);
    if(*looplen==seqlen/2){ /* this help only one time print the array of seq*/
    printf("\nSequence:{");
    for(i=0; i<seqlen-1;i++) printf("%d, ",seq[i]);
    printf("%d}\n",seq[i]);
    }
    if(*looplen>=2){ /* controling the how long length of the loop of seq array*/
      printf("\nChecking if there is a loop of length %d...\n",*looplen);
      check=has_loop(seq,seqlen,*looplen,ls,le);
      if (check==0){
        (*looplen)--;
        free(seq);
        check_loop_iterative(generate_sequence, xs,seqlen,loop,looplen); /* if the not found again control*/
      }
      else if(check==1){
         printf("\nLoop detected with a length of %d.\n",*looplen);
         printf("The indexes of the loop's first occurance: %d (first digit), %d (last digit)\n",*ls,*le);

         int temp=(*looplen);

         for(i=0; i<*looplen;i++){
           loop[i]=seq[seqlen-temp];
          temp--;
         }
         free(seq);
         return;
       }
    }

}

int has_loop(int *arr, int n, int looplen, int *ls, int *le){


/* ---------------------------------------------- */
/* control the last digit end previous length of loop times the seq array */
/* and the control the previous of them each time and all equal return 1 else return 0*/
/*------------------------------------------------*/ 
    int i;
    int temp=n;
    int temp2=n;
    int k;
    int control=0;
    int l=looplen;
    for(i=0; i<looplen; i++){
      if(arr[n-1-looplen]==arr[n-1]){
          n--;
      }
      else return 0;
    }
    i=0;
    k=n;
    n=temp;
      while(i<looplen) {

        if(arr[n-1-looplen]==arr[temp-1]){
            n--;
            temp--;
            control++;
        }
        else break;

        i++;
        if (i==looplen){
          temp=temp2;
          i=0;
        }

      }
      /* the assigned the last and start index of the loop */
      n=temp2;
      (*le)=n-(control/looplen)*looplen;
      (*ls)=n-(control/looplen)*looplen-looplen;

    return 1;
}

void hist_of_firstdigits(void (*f)(int xs, int currentlen,int seqlen,int *seq), int xs, int seqlen, int *h, int digit){

    int *seqa;
    seqa=(int*)calloc(seqlen,sizeof(int));

    f(xs,0,seqlen,seqa);

    /*the first digit of the number of [digit(index)] seq */
    while(seqa[digit]>=10){
      seqa[digit] /= 10;
    }
    /* inrease the appropriate index of the hist */
    h[seqa[digit]-1]++;
    free(seqa);
    if (digit<seqlen-1)hist_of_firstdigits(generate_sequence,xs,seqlen,h,digit+1);
}
