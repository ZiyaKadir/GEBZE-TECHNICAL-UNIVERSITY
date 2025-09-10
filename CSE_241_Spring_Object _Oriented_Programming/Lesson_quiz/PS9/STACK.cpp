#include "STACK.hpp"

template<class T>
Stack<T>::Stack() : top(nullptr)
{
}

template<class T>
Stack<T>::Stack(const Stack<T>& aStack)
{
    if (aStack.isEmpty())
        top = nullptr;
    else
    {
        Node<T>* temp = aStack.top;
        Node<T>* end = nullptr; // points to end of new stack
        end = new Node<T>(temp->getData(), nullptr);
        top = end;

        temp = temp->getLink(); // move temp to next node
        while (temp != nullptr)
        {
            end->setLink(new Node<T>(temp->getData(), nullptr));
            end = end->getLink();
            temp = temp->getLink();
        }
    }
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rightSide)
{
    if (this == &rightSide)
        return *this;
    else
    {
		// if it is not emphty delete one by one 
        if (!isEmpty()) 
        {
            Node<T>* temp; 
            while (top != nullptr)
            {
                temp = top;
                top = top->getLink();
                delete temp;
            }
        }

		// if it is empht equal null than exit 
        if (rightSide.isEmpty())
            top = nullptr;
        else
        {
            Node<T>* temp = rightSide.top; 
            Node<T>* end = nullptr; 
            end = new Node<T>(temp->getData(), nullptr);
            top = end;
 

            temp = temp->getLink(); 
            while (temp != nullptr)
            {
                end->setLink(new Node<T>(temp->getData(), nullptr));
                end = end->getLink();
                temp = temp->getLink();
            }
        }

        return *this;
    }
}

template<class T>
Stack<T>::~Stack()
{
    Node<T>* temp; 
    while (top != nullptr)
    {
        temp = top;
        top = top->getLink();
        delete temp;
    }
}

template<class T>
void Stack<T>::push(T stackFrame)
{
    top = new Node<T>(stackFrame, top);
}

template<class T>
T Stack<T>::pop() throw(PopEmptyStackException)
{
    if (isEmpty())
        throw PopEmptyStackException(); // Throw exception if stack is empty

    T value = top->getData();
    Node<T>* temp = top;
    top = top->getLink();
    delete temp;
    return value;
}

template<class T>
bool Stack<T>::isEmpty() const
{
    return top == nullptr;
}