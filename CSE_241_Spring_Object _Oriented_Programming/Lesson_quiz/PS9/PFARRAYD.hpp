#ifndef PFARRAYDH
#define PFARRAYDH

#include<string>

using std::string;

class Exception
{
};
class OutOfRange: public Exception
{
	public:
	
	OutOfRange(string thisMessage,int thisIndex);
	
	string getMessage()const;
	int getIndex()const;
	
	private:
	string message;
	int index;
};
//Objectsofthisclassarepartiallyfilledarraysofdoubles.
class PFArrayD
{
	public:
	PFArrayD();
	//Initializeswithacapacityof50.
	PFArrayD(int capacityValue);
	PFArrayD(const PFArrayD& pfaObject);
	void addElement(double element);
	//Precondition:Thearrayisnotfull.
	//Postcondition:Theelementhasbeenadded.
	bool full()const;
	//Returnstrueifthearrayisfull,falseotherwise.
	int getCapacity()const;
	int getNumberUsed()const;
	void emptyArray();
	//Emptiesthearray.
	double&operator[](int index)throw(OutOfRange);
//Readandchangeaccesstoelements0throughnumberUsed−1.
	PFArrayD& operator=(const PFArrayD& rightSide);
	~PFArrayD();
	
	private:
	
	double *a;//foranarrayofdoubles.
	int capacity;//forthesizeofthearray.
	int used;//forthenumberofarraypositionscurrentlyinuse.
};
#endif//PFARRAYDH