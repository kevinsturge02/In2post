#ifndef STACK_H
#define STACK_H
#include <vector>
#include <iostream>
namespace cop4530 
{
	template <typename T>
	class Stack
	{
	

	public:
		Stack(); //zero argument constructor
		~Stack();//destructor
		Stack(const Stack<T>& rhs);//copy constructor
		Stack(Stack<T>&&); //move constructor
		Stack<T>& operator=(const Stack& rhs); //copy assignment operator
		Stack<T> operator=(Stack<T>&& rhs); //move assingnent operator.
		
		bool empty() const; //returns true if empty
		void clear();//clears stack by deleting all elements
		void push(const T& x); // adds x to the stack, copy version.
		void push(T&& x); // adds x to the stack, move version.
		void pop(); //deletes top element of stack.
		T& top(); //returns reference to the top element
		const T& top() const; //returns const reference to the top element
		int size() const; //returns size of the stack
		
		void print(std::ostream& os, char ofc = ' ') const; //prints elements of stack to ostream os
	private:
		std::vector<T> elements; //internal vector of all elements in the stack.
	};
	
	template <typename T>
	std::ostream& operator<< (std::ostream& os, const Stack<T>& a);

	template <typename T>
	bool operator==(const Stack<T>& lhs, const Stack<T>&rhs);


	template <typename T>
	bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs);

	template <typename T>
	bool operator<=(const Stack<T>& a, const Stack<T>& b);


#include "stack.hpp"

}

#endif