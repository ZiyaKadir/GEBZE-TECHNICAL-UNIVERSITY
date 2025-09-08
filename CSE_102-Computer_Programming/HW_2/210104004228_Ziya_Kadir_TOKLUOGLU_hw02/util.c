#include <stdio.h>
#include "util.h"
#include <math.h>

/* Example decision tree - see the HW2 description */
int dt0(int t, double p, double h, int s, int w) {
    int r = 0;
    if (t>35 && w!=3) r = 1;
    else if (t<=35 && s==0) r = 1;
    return r;
}


/* Provide your implementations for all the requested functions here */

char dt1a (float pl1a, float pw1a, float sl1a, float sw1a){

if (pl1a < 2.45){
	return 's';
}
else
{
	if (pw1a<1.75) {
		if (pl1a<4.95) {
			if (pw1a<1.65) return 'e';
        		else return 'v';
      		}
      		else return 'v';
	}
	else return 'v';

}
}
char dt1b (float pl1b,float pw1b,float sl1b,float sw1b) {
if (pl1b < 2.55) return 's';
else{
    if (pw1b < 1.69) {
      if (pl1b < 4.85) return 'e';
      else return 'v';
    }
    else return 'v';
  }
}

double dt2a(float x1a ,float x2a ,float x3a ,int x4a ,int x5a) {
	if (x1a<31.5){
		if (x2a>-2.5) return 5;
    		else{
     			 if ((x2a-0.1)<=x1a && x1a<=(x2a+0.1)) return 2.1;
			 else return -1.1;
      		}
  	}

  	else{
      		if (-1<=x3a && x3a<=2) return 1.4;
      
      		else{
       	if (x4a&&x5a) return -2.23;
        	else return 11;
		}
	}
}

double dt2b(float x1b ,float x2b ,float x3b ,int x4b ,int x5b) {
if (x1b > 12 && x1b < 22) {
	if (x3b > (5/3)) return -2;
   	else{
   		if ((x1b-0.1)<=x3b && x3b<=(x1b+0.1)) return 1.01;      		
      		else return -8;
	}
}
else{
	if (x4b && x5b) return -1;
	else{
        	if (-1 <= x2b && x2b <= 2) return -(1/7);
        	else return sqrt(2)/3;
	}
}
}

double dt3a(double speed, double weight, double eng_vol, int exs_turbo, int type_engine){

double fuel_consumption_p100 = 0; /* fuel consumption per 100 kilometer */

	if(type_engine == 1){
		fuel_consumption_p100 += 2.5;
		if(weight < 1500){
			fuel_consumption_p100 += 0.5;
			if(eng_vol < 1200){
				fuel_consumption_p100 += 1.2;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0)
				{
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.7;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				
				}
			
			}
		}
		else{
			fuel_consumption_p100 += 0.8;
			if(eng_vol < 1200){
				fuel_consumption_p100 += 1.2;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.7;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0)
					fuel_consumption_p100 += 1.1;
				{
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				
				}
			
			}
		}
	}
else if (type_engine == 0){
		fuel_consumption_p100 += 3.0;
	if(weight < 1500){
		fuel_consumption_p100 += 0.5;
			if(eng_vol < 1200){
				fuel_consumption_p100 += 1.2;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.7;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				
				}
			
			}
		}
		else{
			fuel_consumption_p100 += 0.8;
			if(eng_vol < 1200){
				fuel_consumption_p100 += 1.2;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.7;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
				else if (exs_turbo == 0){
				fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.3;
					}
					else{
						fuel_consumption_p100 += 0.5;
					} 
				}
			}
		}
	}
return (fuel_consumption_p100);
}
double dt3b(double speed, double weight, double eng_vol, int exs_turbo, int type_engine){

double fuel_consumption_p100 = 0; /* fuel consumption per 100 kilometer */

	if(type_engine == 1){
		fuel_consumption_p100 += 2.5;
		if(weight < 2000){
			fuel_consumption_p100 += 0.6;
			if(eng_vol < 1000){
				fuel_consumption_p100 += 1.0;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0)
				{
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.5;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				
				}
			
			}
		}
		else{
			fuel_consumption_p100 += 0.9;
			if(eng_vol < 1000){
				fuel_consumption_p100 += 1.0;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.5;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0)
					fuel_consumption_p100 += 1.1;
				{
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				
				}
			
			}
		}
	}
else if (type_engine == 0){
		fuel_consumption_p100 += 3.0;
	if(weight < 2000){
		fuel_consumption_p100 += 0.6;
			if(eng_vol < 1000){
				fuel_consumption_p100 += 1.0;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.5;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				
				}
			
			}
		}
		else{
			fuel_consumption_p100 += 0.9;
			if(eng_vol < 1000){
				fuel_consumption_p100 += 1.0;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0){
					fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				
				}
			}
			else{
				fuel_consumption_p100 += 1.5;
				if(exs_turbo == 1){
					fuel_consumption_p100 += 0.6;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
				else if (exs_turbo == 0){
				fuel_consumption_p100 += 1.1;
					if(speed < 150){
						fuel_consumption_p100 += 0.4;
					}
					else{
						fuel_consumption_p100 += 0.6;
					} 
				}
			}
		}
	}
return (fuel_consumption_p100);
}
