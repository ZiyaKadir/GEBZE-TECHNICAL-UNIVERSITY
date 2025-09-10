#ifndef _SET_
#define _SET_

template<class T>
class Set {
private:
    T* elements;
    int size;
    int capacity;

public:
    Set();
    ~Set();
    void add(T value);
    bool contains(T value);
    T* getArray();
    int getSize();
};

#endif
