#include<iostream>
#include<string>
#include "Set.cpp"

using namespace std;

template<class T,class U> 
class Pair{
private:
    T first;
    U second;

public:
    Pair(T firstValue, U secondValue) : first(firstValue), second(secondValue) {}

    T getFirst() const {
		return first;
	}
    void setFirst(T newValue) 
	{ 
		first = newValue;
	}

    U getSecond() const{
		return second;
	}
    void setSecond(U newValue)
	{ 
		second = newValue;
	}
};

int main(){
    Pair<char,char> p('Z', 'Y');
    cout << "First is " << p.getFirst() << endl;
    p.setFirst('A');
    cout << "First changed to " << p.getFirst() << endl;
    cout << "The pair is: " << p.getFirst() << ", " << p.getSecond() << endl;

    Pair<int,string> p2(41, "Ziya");
    cout << "The pair is: " << p2.getFirst() << ", " << p2.getSecond() << endl;

    Pair<string,int> p3("Ziya", 41);
    cout << "The pair is: " << p3.getFirst() << ", " << p3.getSecond() << endl;

    return 0;
}
