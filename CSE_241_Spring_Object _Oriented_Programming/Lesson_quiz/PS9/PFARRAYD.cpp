#include "PFARRAYD.hpp"

OutOfRange::OutOfRange(string thisMessage, int thisIndex)
{
    message = thisMessage;
    index = thisIndex;
}

string OutOfRange::getMessage() const
{
    return message;
}

int OutOfRange::getIndex() const
{
    return index;
}

PFArrayD::PFArrayD()
{
    capacity = 50;
    used = 0;
    a = new double[capacity];
}

PFArrayD::PFArrayD(int capacityValue)
{
    capacity = capacityValue;
    used = 0;
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject)
{
    capacity = pfaObject.capacity;
    used = pfaObject.used;
    a = new double[capacity];
    for (int i = 0; i < used; i++)
        a[i] = pfaObject.a[i];
}
int PFArrayD::getCapacity()const{
	return capacity;
}
int PFArrayD::getNumberUsed()const{
	return used;
}
void PFArrayD::emptyArray(){
	used = 0;
}
bool PFArrayD::full()const{
	return(capacity == used);
}

void PFArrayD::addElement(double element)
{
    if (used >= capacity)
        throw OutOfRange("Array is full throw exception", used);
    a[used] = element;
    used++;
}

double& PFArrayD::operator[](int index) throw(OutOfRange)
{
    if (index < 0 || index >= used)
        throw OutOfRange("you probably exceed the boundries of the array.", index);
    return a[index];
}


PFArrayD& PFArrayD::operator=(const PFArrayD& rightSide)
{
    if (this != &rightSide)
    {
        delete[] a;
        capacity = rightSide.capacity;
        used = rightSide.used;
        a = new double[capacity];
        for (int i = 0; i < used; i++)
            a[i] = rightSide.a[i];
    }
    return *this;
}

PFArrayD::~PFArrayD()
{
    delete[] a;
}
