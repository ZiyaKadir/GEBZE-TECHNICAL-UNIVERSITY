#ifndef _UTIL_H_
#define _UTIL_H_

#define CLOSE_ENOUGH 0.001



/* Example decision tree - see the HW2 description */
int dt0(int t, double p, double h, int s, int w);

char dt1a(float pl1a,float pw1a,float sl1a,float sw1a);
char dt1b(float pl1b,float pw1b,float sl1b,float sw1b);

double dt2a(float x1a,float x2a,float x3a,int x4a,int x5a);
double dt2b(float x1b,float x2b,float x3b,int x4b,int x5b);
double dt3a(double speed, double weight, double eng_vol, int exs_turbo, int type_engine);
double dt3b(double speed, double weight, double eng_vol, int exs_turbo, int type_engine);

#endif /* _UTIL_H_ */
