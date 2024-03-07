#ifndef STACK_HPP
#define STACK_HPP

using namespace cop4530;

//=====================constructors and assignment operators
template <typename T>
Stack<T>::Stack() //zero param
{
	elements;
}

template <typename T>
Stack<T>::~Stack() //destructor
{
	//nothing needed due to std::vector() having its own destructor.	
}

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs) //copy constructor
{
	elements = rhs.elements;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& rhs) //move constructor
{
	elements = std::move(rhs.elements);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //copy assignment operator
{
	Stack<T> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template <typename T>
Stack<T> Stack<T>::operator=(Stack&& rhs) //move assignment operator
{
	elements = rhs.elements;
	return *this;

}

//=================================== member functions
template <typename T>
bool Stack<T>::empty() const //returns true if stack is empty, false otherwise
{
	return(elements.empty());
}


template <typename T>
void Stack<T>::clear() //deletes all elements
{
	elements.clear();
}

template <typename T>
void Stack<T>::push(const T& x) //adds x to stack copy version
{
	elements.push_back(x);
}

template <typename T>
void Stack<T>::push(T&& x) //adds x to stack move version
{
	elements.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop() //deletes top of stack
{
	if (!elements.empty())
		elements.pop_back();
	else
		std::cout << "empty stack" << std::endl;
}

template <typename T>
T& Stack<T>::top() //returns top of stack
{
	return elements.back();
}

template <typename T>
const T& Stack<T>::top() const //const version of top for const references to keep const consistency
{
	return elements.back();
}

template <typename T>
int Stack<T>::size() const //returns size of stack
{
	return elements.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
	if (empty())
	{
		os << "Stack is empty. " << std::endl;
		return;
	}

	for (int i = 0; i < elements.size(); i++)
	{
		os << elements[i] << ofc;
	}
	os << std::endl;
}
//==================== non member functions ========================

template <typename T>
std::ostream& cop4530::operator<< (std::ostream& os, const Stack<T>& a) //ostream operator overload
{
	a.print(os);
	return os;
}

template<typename T>
bool cop4530::operator==(const Stack<T>& lhs, const Stack<T>& rhs) //equality operator overload
{
	if (lhs.size() != rhs.size()) {
		return false;
	}

	Stack<T> lhs_copy = lhs;
	Stack<T> rhs_copy = rhs;

	while (!lhs_copy.empty() && !rhs_copy.empty()) {
		if (lhs_copy.top() != rhs_copy.top()) {
			return false;
		}
		lhs_copy.pop();
		rhs_copy.pop();
	}

	return lhs_copy.empty() && rhs_copy.empty();
}


template <typename T>
bool cop4530::operator!=(const Stack<T>& lhs, const Stack<T>& rhs) 
{
	return !(lhs == rhs);
}

template<typename T>
bool cop4530::operator<=(const Stack<T>& a, const Stack<T>& b)
{
	if (a.size() > b.size()) {
		return false;
	}

	Stack<T> a_copy = a;
	Stack<T> b_copy = b;

	while (!a_copy.empty() && !b_copy.empty()) {
		if (a_copy.top() > b_copy.top()) 
		{
			return false;
		}
		a_copy.pop();
		b_copy.pop();
	}

	return a_copy.empty();
}

#endif