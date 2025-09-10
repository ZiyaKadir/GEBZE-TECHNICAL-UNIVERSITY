#include<iostream>


using namespace std;


class Polynomial{

	public:

	Polynomial();
	Polynomial(const Polynomial& copy);
	Polynomial(const double* parameter,int size);
	~Polynomial();

	Polynomial& operator=(const Polynomial& assign);
	friend Polynomial operator+(const Polynomial poly1,const Polynomial poly2);
	friend Polynomial operator-(const Polynomial poly1,const Polynomial poly2);
	friend Polynomial operator*(const Polynomial poly1,const Polynomial poly2);

	int mySize()const;

	double& operator[](int index);
	const double& operator[](int index)const;


	private:

	int degree;
	double *coefficent;

};

double evaluate(const Polynomial poly,int number);

double power(double base, int exponent);

int main(){

	Polynomial empty;
	double one[] = {1};
	Polynomial One(one, 1);
	double quad[] = {3, 2, 1};
	double cubic[] = {1, 2, 0, 3};

	Polynomial q(quad, 3); // q is 3 + 2*x + x*x
	Polynomial c(cubic, 4);// c is 1 + 2*x + 0*x*x + 3*x*x*x
	Polynomial p = q; // test copy constructor
	Polynomial r;
	r = q;
	//test operator=
	r = c;
	cout << "Polynomial q " << endl;
	for(int i = 0; i < 3; i++){
	cout << "term with degree " << i
	<< " has coefficient " << q[i] << endl;
	}
	cout << "Polynomial c " << endl;
	for(int i = 0; i < 4; i++){
	cout << "term with degree " << i
	<< " has coefficient " << c[i] << endl;
	}
	cout << "value of q(2) is " << evaluate(q, 2) << endl;
	cout << "value of p(2) is " << evaluate(p, 2) << endl;
	cout << "value of r(2) is " << evaluate(r, 2) << endl;
	cout << "value of c(2) is " << evaluate(c, 2) << endl;
	r = q + c;
	cout << "value of (q + c)(2) is " << evaluate(r, 2) << endl;
	r = q - c;
	cout << "value of (q - c)(2) is " << evaluate(r, 2) << endl;
	r = q * c;
	cout << "size of q*c is " << r.mySize() << endl;
	cout << "Polynomial r (= q*c) " << endl;
	for(int i = 0; i < r.mySize(); i++)
	cout << "term with degree " << i
	<< " has coefficient " << r[i] << endl;
	cout << "value of (q * c)(2) is " << evaluate(r, 2) << endl;


	return 0;
}

Polynomial::Polynomial() // Default constructer
{	
	degree = 0;
	coefficent = nullptr;

}
Polynomial::Polynomial(const Polynomial& copy) // Copy constructer
{
	degree = copy.degree;
	coefficent = new double[degree];
	for(int i=0; i < degree; i++){
		coefficent[i] = copy.coefficent[i];
	}
}
Polynomial::~Polynomial(){
	degree=0;
	delete[] coefficent;

}

Polynomial::Polynomial(const double* parameter, int size){

	degree = size;
	coefficent = new double[size];
	for(int i=0; i < degree; i++){
		coefficent[i] = parameter[i];
	}
}

int Polynomial::mySize()const{
	return degree;
}


// Polynomial& Polynomial::operator=(const Polynomial& assign){
// 	if (this != &assign){
// 		degree = assign.degree;
// 		delete[] coefficent;
// 		coefficent = new double[degree + 1];

// 		for (int i=0; i < degree; i++){
// 			coefficent[i] = assign.coefficent[i];
// 		}
// 	}
// 	return *this;
// }

//	why is not work ask teacher 

Polynomial& Polynomial::operator=(const Polynomial& assign){

	Polynomial sum;

	sum.degree = assign.degree;
	sum.coefficent = new double[assign.degree];
	for(int i=0; i < assign.degree; i++){
		sum.coefficent[i] = assign.coefficent[i];
	}

	return sum;

}

Polynomial operator+(const Polynomial poly1,const Polynomial poly2){

	Polynomial sum;

	int max_degree;

	if(poly1.degree > poly2.degree){
		max_degree = poly1.degree;
	}
	else{
		max_degree = poly2.degree;
	}
	sum.degree = max_degree;

	sum.coefficent = new double[max_degree];	
	for (int i=0; i < max_degree; i++){
		sum.coefficent[i] = poly1.coefficent[i] + poly2.coefficent[i];
	}

	return sum;

}

Polynomial operator-(const Polynomial poly1,const Polynomial poly2){

	Polynomial sum;

	int max_degree;

	if(poly1.degree > poly2.degree){
		max_degree = poly1.degree;
	}
	else{
		max_degree = poly2.degree;
	}
	sum.degree = max_degree;

	sum.coefficent = new double[max_degree];	
	for (int i=0; i < max_degree; i++){
		sum.coefficent[i] = poly1.coefficent[i] - poly2.coefficent[i];
	}

	return sum;
}
Polynomial operator*(const Polynomial poly1,const Polynomial poly2){

    Polynomial product;

    int max_degree = poly1.degree + poly2.degree -1;

    product.degree = max_degree;

    product.coefficent = new double[max_degree];

    for(int i = 0; i < max_degree; i++){
        product.coefficent[i] = 0;
    }

    for(int i = 0; i < poly1.degree; i++){
        for(int j = 0; j < poly2.degree; j++){
            product.coefficent[i+j] += poly1.coefficent[i] * poly2.coefficent[j];
        }
    }

    return product;
}


double& Polynomial::operator[](int index) {
    
	
	if (index >= 0 && index <= degree) {
        return coefficent[index];
    } 
	else{
    }
}


const double& Polynomial::operator[](int index)const{

	if (index >= 0 && index <= degree) {
        return coefficent[index];
    }
	else{
    }
}

double power(double base, int exponent) {
    if (exponent == 0) {
        return 1.0;
    } else if (exponent > 0) {
        return base * power(base, exponent - 1);
    } else {
        return 1.0 / power(base, -exponent);
    }
}


double evaluate(const Polynomial poly, int number){
	
	double result=0;
	for(int i=0; i < poly.mySize(); i++){
			result += power(number, i) * poly[i];
	}
	return result;
}
