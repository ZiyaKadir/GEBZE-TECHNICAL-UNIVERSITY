#include "Set.hpp"

template<class T>
Set<T>::Set() {
    elements = new T[8];
    size = 0;
    capacity = 8;
}

template<class T>
Set<T>::~Set() {
    delete[] elements;
}

template<class T>
void Set<T>::add(T value) {
    if (contains(value)) {
        return;
    }

    if (size == capacity) {
        T* newElements = new T[2 * capacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity *= 2;
    }

    elements[size++] = value;
}

template<class T>
bool Set<T>::contains(T value) {
    for (int i = 0; i < size; i++) {
        if (elements[i] == value) {
            return true;
        }
    }
    return false;
}

template<class T>
T* Set<T>::getArray() {
    T* array = new T[size];
    for (int i = 0; i < size; i++) {
        array[i] = elements[i];
    }
    return array;
}

template<class T>
int Set<T>::getSize() {
    return size;
}
