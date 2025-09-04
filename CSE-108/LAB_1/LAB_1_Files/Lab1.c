#include <stdio.h>
#define PI 3.14

void Midpoint_calculation(int x1, int y1, int x2, int y2){

	float mid_x = (float)(x1 + x2)/2;
	float mid_y = (float)(y1 + y2)/2;

	printf("Midpoint: M(x,y) = (%.1f,%.1f)\n",mid_x, mid_y);
}

void Slope_calculation(int x1, int y1, int x2, int y2){
	
	float dif_x = (float)x2 - x1;
	float dif_y = (float)y2 - y1;

	float slope = dif_y / dif_x;

	printf("Slope: m = (%.1f) \n",slope);
}

void Area_calculation(int x1, int y1, int x2, int y2){

	float dif_x = (float)x2 - x1;
	float dif_y = (float)y2 - y1;

	float square_of_diameter = (dif_x * dif_x) + (dif_y * dif_y);

	float square_of_radius = (square_of_diameter / 4.0);

	float Area = square_of_radius * PI;

	printf("Area: A = %.1f \n " , Area);

}

int main(){

	int x1,y1,x2,y2;

	printf("x1:");
	scanf("%d",&x1);

	printf("y1:");
	scanf("%d",&y1);

	printf("x2:");
	scanf("%d",&x2);

	printf("y2:");
	scanf("%d",&y2);

	Midpoint_calculation(x1,y1,x2,y2);
	Slope_calculation(x1,y1,x2,y2);
	Area_calculation(x1,y1,x2,y2);



	return 0;
}