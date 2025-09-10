#include "Stack.hpp"

template<typename T>
Stack<T>::Stack(){}

template<typename T>
Stack<T>::Stack(const Stack<T>& copy) {
    List = copy.List;
}

template<typename T>
Stack<T>::Stack(Stack<T>&& copy){
    List = copy.List;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& assign) {
    if (this != &assign) {
        List = assign.List;
    }
    return *this;
}

template<typename T>
Stack<T>::~Stack(){

}

template<typename T>
void Stack<T>::push(const T& new_data) {

    List.push_back(new_data);
}

template<typename T>
vector<T> Stack<T>::get_List() const{
    return List;
}


template<typename T>
T Stack<T>::pop() {
    if (List.empty()) {
        //throw exception unutma
    }

    T popped_element = List.back();
    List.pop_back();
    return popped_element;
}

template<typename T>
T& Stack<T>::operator[](size_t index) {
    return List[index];
}
