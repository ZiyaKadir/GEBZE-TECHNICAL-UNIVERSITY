#include <iostream>


using namespace std;




class Vector2D{

	public:

	Vector2D();
	Vector2D(int x_coor, int y_coor); // x and y coordinate


	int GetX()const;
	int GetY()const;

	void SetX(int number);
	void SetY(int number);

	friend int operator*(const Vector2D& vector1, const Vector2D& vector2);

	private:

	int X;
	int Y;

};

int main(){

	Vector2D v1(11,2), v2(7,3), v3(8,3), v4(5,6);

	cout << "(" << v1.GetX() << "," << v1.GetY() << ") * (" 
	<< v2.GetX() << "," << v2.GetY() << ") = " <<
	v1 * v2 << endl;

	cout << "(" << v2.GetX() << "," << v2.GetY() << ") * (" 
	<< v3.GetX() << "," << v3.GetY() << ") = " <<
	v2 * v3 << endl;

	cout << "(" << v3.GetX() << "," << v3.GetY() << ") * (" 
	<< v4.GetX() << "," << v4.GetY() << ") = " <<
	v3 * v4 << endl;


	return 0;
}

Vector2D::Vector2D(){
	X = 0;
	Y = 0;
}

Vector2D::Vector2D(int x_coor, int y_coor){
	X = x_coor;
	Y = y_coor;

}

int Vector2D::GetX()const{
	return X;

}
int Vector2D::GetY()const{
	return Y;
}

void Vector2D::SetX(int number){
	X = number;
}

void Vector2D::SetY(int number){
	Y = number;
}


int operator*(const Vector2D& vector1, const Vector2D& vector2){

	int sum = (vector1.GetX()*vector2.GetX()) +(vector1.GetY()*vector2.GetY());
	return sum; 
}