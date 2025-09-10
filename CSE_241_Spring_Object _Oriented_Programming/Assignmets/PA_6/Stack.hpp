#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

using namespace std;

template<typename T>
class Stack {

	private:
		vector<T> List;

	public:
		Stack();

		Stack(const Stack<T>& copy);

		Stack(Stack<T>&& copy);

		Stack<T>& operator=(const Stack<T>& assign);

		~Stack();

		void push(const T& new_data);

		T pop();

		vector<T> get_List() const;
		
		T& operator[](size_t index);

};


#endif 
