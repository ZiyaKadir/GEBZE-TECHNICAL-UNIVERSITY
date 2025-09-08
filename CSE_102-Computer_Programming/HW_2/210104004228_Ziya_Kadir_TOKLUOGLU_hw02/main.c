#include <stdio.h>
#include "util.h"


int main() {

    /* Ask for the problem selection (1,2,3) .....  */
    
    int sel_part; /* selection part */
    int cont_sel = 1; /* controller selection */
    do {
    printf("please select your problem\n");
    printf(" 1-Problem 1 \n 2-Problem 2 \n 3-Problem 3\n");
    scanf("%d", &sel_part);
    
    if (sel_part < 4 && sel_part > 0) cont_sel = 0;
    else printf("Please, make sure you choose the right problem\n");
    
    }while(cont_sel == 1);
    
    /* Get the input from the user for the first problem, i.e., to test dt1a and dt1b */
    if (sel_part == 1)
{
    	float pl, pw, sl, sw;
    	char dta, dtb; /* first and second decision tree for P1 */
    	
    	printf("Please enter pl: ");
    	scanf("%f", &pl);
    	printf("Please enter pw: ");
    	scanf("%f", &pw);
    	printf("Please enter sl: ");
    	scanf("%f", &sl);
    	printf("Please enter sw: ");
    	scanf("%f", &sw);
    
    dta = dt1a(pl, pw, sl, sw);
    dtb = dt1b(pl, pw, sl, sw);
    
    /* Compare performances and print results */
    
    if (dta == dtb){
    
    	if (dta =='s') printf("setosa\n");
    	else if (dta =='v') printf("virginica\n");
    	else printf("versicolor\n");
    }
    else {
    	if (dta == 's'){
    	printf("dta : setosa\n");
    		if(dtb == 'v') printf("dtb : virginica\n");
    		else printf("dtb : versicolor");
    	}
    	else if (dta == 'v'){
    	printf("dta : virginica\n");
    		if(dtb == 's') printf("dtb : setosa\n");
    		else printf("dtb : versicolor");    	
    	}
    	else{
    	printf("dta : versicolor\n");
    		if(dtb == 's') printf("dtb : setosa");
    		else if(dtb == 'v') printf("dtb : virginica\n");
    	}
    }
}

    /* Get the input from the user for the second problem, i.e., to test dt2a and dt2b */
    else if(sel_part == 2)
{
   float x1,x2,x3;
   int x4,x5;
   double dta,dtb;
   double diff; /* difference between dta and dtb */ 
   
   printf("Please enter x1 : ");
   scanf("%f",&x1);
   printf("Please enter x2 : ");
   scanf("%f",&x2);
   printf("Please enter x3 : ");
   scanf("%f",&x3);
   printf("Please enter x4 : ");
   scanf("%d",&x4);
   printf("Please enter x5 : ");
   scanf("%d",&x5);
   
   dta=dt2a(x1,x2,x3,x4,x5);
   dtb=dt2b(x1,x2,x3,x4,x5);
   
   diff = dta - dtb;
   if (diff < 0) diff *= -1;
  
    /* Compare performances and print results */
    
    if (diff < CLOSE_ENOUGH) printf("%lf\n", (dta+dtb) / 2);
    else if (dta == dtb) printf("%lf \n", dta);
    else printf("%lf,%lf\n", dta, dtb);
    
}
    /* Get the input from the user for the third problem, i.e., to test dt3a and dt3b */
	else if(sel_part == 3)
{
	printf("Welcome the calculater consumption fuel of your car:");
	double dta, dtb;
	double speed, weight, eng_vol; /* speed, weight of car and engine volume */ 
	int exs_turbo, type_engine;/* exsistence of turbo and type of engine  (gasoline or diesel)*/

	printf("Please enter speed :");
	scanf("%lf",&speed);
	printf("Please enter weight :");
	scanf("%lf",&weight);
	printf("Please enter engine volume :");
	scanf("%lf", &eng_vol);
	printf("Please enter if turbo exists \n0:not exist\n1:exist\n:");
	scanf("%d",&exs_turbo);
	printf("Please enter type of engine (gasoline or diesel) \n0:gasoline \n1:diesel\n:");
	scanf("%d",&type_engine);

dta = dt3a(speed, weight, eng_vol, exs_turbo, type_engine);
dtb = dt3b(speed, weight, eng_vol, exs_turbo, type_engine);

	/* Compare performances and print results */

	if (dta == dtb) printf("same result from dta, dtb\n dta:%lf, dtb:%lf\n",dta ,dtb);
	else printf("different result from dta ,dtb\n dta:%lf dtb:%lf\n",dta ,dtb);
}


    return 0;
}
