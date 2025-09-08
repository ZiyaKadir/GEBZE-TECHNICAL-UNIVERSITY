#include<stdio.h>
#include<math.h>

#define pi 3.14

typedef enum{
    Triangle = 1,
    Quadrilateral,
    Circle,
    Pyramid,
    Cylinder

}Shapes;

typedef enum{
    Area = 1,
    Perimeter,
    Volume
}Calculators;

int calculate (int (*s)(), int (*t)());
int select_shape();

int select_calc ();

int calc_triangle(int a);

int calc_quadrilateral(int a);

int calc_circle(int a);

int calc_pyramid(int a) ;

int calc_cylinder(int a);

double take_float(void);

int main(){
  printf("Welcome to the geometric calculator!\n");
  int control;
  do{
    control = calculate(select_shape,select_calc);
  }while(control == -38);
    return 0;
}



int select_shape(){
    int shape;
    do{
    printf("Select a shape to calculate\n");
    printf("------------------------------\n");
    printf("1. Triangle\n");
    printf("2. Quadrilateral\n");
    printf("3. Circle\n");
    printf("4. Pyramid\n");
    printf("5. Cylinder\n");
    printf("0. Exit\n");
    printf("------------------------------\n");
    printf("Input: ");
    shape = take_float();
    if (!(shape > -1 && shape <6)) printf("ERROR ! Please enter a valid entry\n");
  }while(!(shape > -1 && shape <6));
    return shape;
}

int select_calc(){
    int calc;
    do{
    printf("Select calculater\n");
    printf("---------------------\n");
    printf("1. Area\n");
    printf("2. Perimeter\n");
    printf("3. Volume\n");
    printf("0. Exit\n");

    printf("Input: ");
    calc = take_float();
    if (!(calc > -1 && calc <4)) printf("ERROR ! Please enter a valid entry\n");
  }while(!(calc > -1 && calc <4));

    return calc;
}

int calculate (int (*s)(), int (*t)()){
    /* return -2 for controlling valid triangle and quadrilateral */
    /* return -38 for maintain the program */
    /* return -5 for exitting the program */
    int shape, calc, control;
    shape=s();
    if(shape == 0) return -5;
  switch (shape)
  {
  case Triangle:
    calc =t();
    if(calc == 0) return -5;
    do {
      if (control == -2) calc=t();
      control = calc_triangle(calc);
    }while (control == -2);
    if(control == -1) return -38;

      break;

  case Quadrilateral:
  calc =t();
  if(calc == 0) return -5;
  do {
    if (control == -2) calc=t();
    control = calc_quadrilateral(calc);
  }while (control == -2);
  if(control == -1) return -38;

    break;
  case Circle:
    calc =t();
    if(calc == 0) return -5;
    control=calc_circle(calc);
    if(control == -1) return -38;
      break;

  case Pyramid:
    calc =t();
    if(calc == 0) return -5;
    control=calc_pyramid(calc);
    if(control == -1) return -38;
      break;

  case Cylinder:
    calc =t();
    if(calc == 0) return -5;
    control=calc_cylinder(calc);
    if(control == -1) return -38;
      break;

  default:
      break;
  }
}

int calc_triangle(int type){

    if (type==Volume){
      printf("ERROR ! You cannot calculate the volume of a triangle.Please try again.\n");
     return -1;
    }

    printf("\nPlease enter three sides of Triangle\n");

    int flag;/* to control all sides are valid together */

    double f_side=0; /*first side of Triangle*/
    double s_side=0; /*secomd side of Triangle*/
    double t_side=0; /*third side of Triangle*/


  do { /* taking the sides of Triangle and controlling they are valid*/
    flag=1;
    f_side=take_float();
    if (f_side == -1 && flag==1){
       printf("ERROR Please enter a valid entry\n");
       flag=0;
       continue;
     }
    s_side=take_float();
    if (s_side == -1 && flag ==1){
       printf("ERROR Please enter a valid entry\n");
       flag=0;
        continue;
     }
    t_side=take_float();
    if (t_side == -1 && flag==1) {
       printf("ERROR Please enter a valid entry\n");
       flag=0;
        continue;
     }
     if(f_side < 0 || s_side < 0 || t_side < 0){
        printf("ERROR Please enter a valid entry\n");
        flag=0;
        continue;
     }
     else if((f_side+s_side) <= t_side || (f_side+t_side) <= s_side || (s_side+t_side) <= f_side){
       printf("ERROR ! Please enter a valid triangle\n");
       return -2;
     }

  }while(flag==0);

    if (type == Area){/*calculate area of triangle*/
      /*Heron's Formula*/
      double s,sum;
      double area;
      s= (f_side+s_side+t_side)/2.0;
      sum = s*(s-f_side)*(s-s_side)*(s-t_side);
      area = sqrt(sum);
      printf("Area of TRIANGLE : %.2lf\n",area);
        }
    else if(type == Perimeter){/* calculate perimeter of triangle*/
      double Perimeter = f_side+s_side+t_side;
      printf("%.2lf\n",Perimeter);
    }
    return -1;
}

int calc_quadrilateral(int type){

  if (type==Volume){
    printf("ERROR ! You cannot calculate the volume of a quadrilateral.Please try again.\n");
    return -1;
  }
  printf("\nPlease enter four sides of Quadrilateral\n");

  int flag;/* to control all sides are valid together */

  double f_side=0;   /*first side of Quadrilateral*/
  double s_side=0;   /*secomd side of Quadrilateral*/
  double t_side=0;   /*third side of Quadrilateral*/
  double fo_side=0;  /*fourth side of Quadrilateral*/


  do { /* taking the sides of quadrilateral and controlling they are valid*/
  flag=1;
  f_side=take_float();
  if (f_side == -1 && flag==1){
     printf("ERROR Please enter a valid entry\n");
     flag=0;
     continue;
   }
  s_side=take_float();
  if (s_side == -1 && flag ==1){
     printf("ERROR Please enter a valid entry\n");
     flag=0;
      continue;
   }
  t_side=take_float();
  if (t_side == -1 && flag==1) {
     printf("ERROR Please enter a valid entry\n");
     flag=0;
      continue;
   }
   fo_side=take_float();
   if (fo_side == -1 && flag==1) {
      printf("ERROR Please enter a valid entry\n");
      flag=0;
       continue;
    }
   if(f_side < 0 || s_side < 0 || t_side < 0 || fo_side < 0){
      printf("ERROR Please enter a valid entry\n");
      flag=0;
      continue;
   }
   if ((f_side+s_side+t_side <= fo_side) || (f_side+s_side+fo_side) <= t_side || (f_side+t_side+fo_side) <= s_side || (s_side+t_side+fo_side) <= f_side) {
     printf("ERROR Please enter a valid QUADRILATERAL\n");
     return -2;
   }

  }while(flag==0);

  if (type == Area){/*Calculate the Area of quadrilateral*/
    /* Brahmagupta's Formula*/
    double s,sum;
    double area;
    s= (f_side+s_side+t_side+fo_side)/2;
    sum = (s-f_side)*(s-s_side)*(s-t_side)*(s-fo_side);
    area = sqrt(sum);
    printf("Area of QUADRILATERAL : %.2lf\n",area);
      }
  else if(type == Perimeter){/*Calculate the Perimeter of quadrilateral*/
    double Perimeter = f_side+s_side+t_side+fo_side;
    printf("Perimeter of QUADRILATERAL : %.2lf\n",Perimeter);
  }
  return -1;
}

int calc_circle(int type){
  if (type==Volume){
    printf("ERROR ! You cannot calculate the volume of a Circle. Please try again.");
    return -1;
  }

  printf("\nPlease enter the radius of Circle\n");

  int flag; /* to control radius are valid */

  double radius=0;   /*radius of Circle*/

  do { /* taking radius of Circle*/
  flag=1;
  radius=take_float();
  if (radius == -1 && flag==1){
     printf("ERROR Please enter a valid entry\n");
     flag=0;
     continue;
   }

   if(radius < 0){
      printf("ERROR Please enter a valid entry\n");
      flag=0;
      continue;
   }

  }while(flag==0);

  if (type == Area){/*to calculate a Area of Cırcle */
    double Area= pi * pow(radius,2);
    printf("Area of CIRCLE: %.2lf\n",Area);
      }
  else if(type == Perimeter){/* to calculate a perimeter of Cırcle*/
    double Perimeter = (double)(2*pi*radius);
    printf("Perimeter of CIRCLE%.2lf\n",Perimeter);
  }
  return -1;
}

int calc_pyramid(int type){

  if (type == Volume) printf("\nPlease enter the base side and height of a Pyramid: \n");
  else if (type == Area) printf("\nPlease enter the base side and slant height of a Pyramid:\n");
  else if (type == Perimeter) printf("\nPlease enter the base side and slant height of a Pyramid:\n");
  int flag;

  double base =0; /*base side of Pyramid*/
  double height=0;/*height of Pyramid for volume and also slant height of Pyramid for Area and Perimeter */


  do { /* taking the base side and height or slant height*/
  flag=1;
  base=take_float();
  if (base == -1 && flag==1){
     printf("ERROR Please enter a valid entry\n");
     flag=0;
     continue;
   }
  height=take_float();
  if (height == -1 && flag ==1){
     printf("ERROR Please enter a valid entry\n");
     flag=0;
      continue;
   }
   if(base < 0 || height < 0){
      printf("ERROR Please enter a valid entry\n");
      flag=0;
      continue;
   }

   }while(flag==0);

  if (type == Area){/*to calculate a Area of Pyramid*/

    double base_a = pow(base,2);
    double Lateral_a = 2*base*height;
    double Surface_a = base_a+Lateral_a;
    printf("Base Surface Area of a PYRAMID: %.2lf\n" ,base_a);
    printf("Lateral Surface Area of a PYRAMID: %.2lf\n", Lateral_a);
    printf("Surface Area of a PYRAMID: %.2lf\n", Surface_a);
    }
  else if(type == Perimeter){/*to calculate a Perimeter of Pyramid*/
    double perimeter= 4*base;
    printf("The perimeter of PYRAMID: %.2lf\n", perimeter);
  }
  else if(type == Volume){/*to calculate a Volume of Pyramid*/
    double volume = (pow(base,2)*height)/3;
    printf("Volume of a PYRAMID: %.2lf\n",volume);
  }
  return -1;
}

int calc_cylinder(int type){
  printf("\nPlease enter the radius and height of a Pyramid: \n");

  int flag;

  double radius=0; /*radius of cyclinder*/
  double height=0;/*height of cyclinder*/


  do { /* taking radius and height*/
  flag=1;
  radius=take_float();
  if (radius == -1 && flag==1){
     printf("ERROR Please enter a valid entry\n");
     flag=0;
     continue;
   }
  height=take_float();
  if (height == -1 && flag ==1){
     printf("ERROR Please enter a valid entry\n");
     flag=0;
      continue;
   }
   if(radius < 0 || height < 0){
      printf("ERROR Please enter a valid entry\n");
      flag=0;
      continue;
   }

   }while(flag==0);

  if (type == Area){ /*to calculate a Area of Cylinder*/
    double base_a = pow(radius,2)*pi;
    double Lateral_a = 2*radius*pi*height;
    double Surface_a = 2*pi*radius*(radius+height);
    printf("Base Surface Area of a CYLINDER: %.2lf\n" ,base_a);
    printf("Lateral Surface Area of a CYCLINDER: %.2lf\n", Lateral_a);
    printf("Surface Area of a CYCLINDER: %.2lf\n", Surface_a);
      }
    else if(type == Perimeter){/* to calculate a Perimeter of Cylinder*/
      double perimeter= 2*pi*radius;
      printf("Base Surface Perimeter of a CYCLINDER: %.2lf\n", perimeter);
    }

  else if(type == Volume){ /*to calculate a Volume of Cylinder*/
    double volume = pow(radius,2)*pi*height;
    printf("Volume of a PYRAMID: %.2lf\n",volume);
  }
return -1;
}

double take_float(void){
int c_sign=1; /* checking sign of integer*/
int sign=1;   /*sign of integer*/
int c=1; /* the sign determine the number(which took from buffer) assigned integer or float part of number*/
double dividor=1; /* using to calculate float part of number*/
char control; /* to get the number as a integer */
int b=0; /* to control entering \n if first time \n the program ask again the user */
double number=0; /* the number is given by user */

    do{
      control=getchar();
      if(control == 10) continue;
      else if (control == '-' && c_sign){
        c_sign = 0;
         sign = -1;
         b++;
         continue;
      }
      else if (control == 46 && b > 0){
        c=0;
        continue;
      }
      else if (control >= 48 && control <= 57 && c)
      {
      number = number*10 + (control-48);
      c_sign = 0;
      b++;
      }

      else if(control >= 48 && control <= 57 && !c){
        dividor *= 10.0;
        number += (((control*1.0)-48.0)/dividor);
        continue;
      }
      else if (control != 10 && !(control >= 48 && control <= 57)){
          while(getchar() != 10);
          b++;
          return -1;
    }
  }while (control != 10 || b==0);

  return sign * number;
}
