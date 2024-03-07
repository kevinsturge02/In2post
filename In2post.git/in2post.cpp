#include <iostream>
#include <cstdlib>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;


void infix2postfix(const vector<string>& infix); //converts infix to post fix and does error checking
vector<string> input2vector(const string& choice); //converts the user input string into a vector of strings separated by whitespace
int precedence(string op); //compares operator precedence
bool isOperator(string str); //checks if a given string is a + - * / ( or ) 
void evaluatePostfix(const vector<string>& postfix); //evaluates numeric postfix expressions using a Stack.


int main() 
{
	while (true)
	{
		string choice;
		cout << "Enter infix expression (\"exit\" to quit): ";
		getline(cin, choice); //reads in user input and puts it into string choice
		
		if (cin.eof()) 
		{ 
            break; 
		}
		else if (choice == "exit") //checks for user wanting to exit
			return 0;
		else
		{
			vector<string> vec = input2vector(choice); // converts the choice string into a parsed vector of strings
		//	for (auto& str : vec)
		//		cout << str;
			cout << endl;
			infix2postfix(vec); //converts the vec vector into postfix and calls evaluator function from within if applicable.
		}
	}
}

bool isOperator(string str)
{
	if (str == "+" || str == "-" || str == "*" || str == "/" || str == "(" || str == ")") //if it's an operator
		return true;
	else
		return false;
}


int precedence(string op)
{
	if (op == "/" || op == "*")
		return 3;
	else if (op == "+" || op == "-")
		return 2;
	else
		return 1;

}


void infix2postfix(const vector<string>& infix) 
{
	Stack<string> s;
	vector<string> postfix;
	int openParens = 0, operandCount = 0, operatorCount = 0;

	for (size_t i = 0; i < infix.size(); ++i) 
	{
		

		if (infix[i] == "(") //error checks for mismatched parentheses
		{
			openParens++;
			s.push(infix[i]); //pushes open paren onto the stack
		}
		else if (infix[i] == ")") 
		{
			if (openParens == 0) //you cant have a closed paren before an open paren, this checks for that
			{
				cout << "Error: Infix expression has mismatched parens!" << endl;
				return;
			}
			openParens--; //decrements the open paren because the closed paren matched it
			while (!s.empty() && s.top() != "(") 
			{
				postfix.push_back(s.top()); //pushes everything between the two parens onto the evaluation vector 
				s.pop(); //removes from the conversion stack
			}
			s.pop(); //Pops the "("
		}
		else if (isOperator(infix[i]))
		{
			operatorCount++;
			while (!s.empty() && precedence(s.top()) >= precedence(infix[i])) 
			{
				postfix.push_back(s.top()); //pushes the top to the evaluation vector and pops from the stack.
				s.pop();
			}
			s.push(infix[i]); // adds operator to the stack
		}
		else 
		{ //Operand
			operandCount++;
			postfix.push_back(infix[i]);
		}

		
		if (i > 0) //checks for operator errors
		{
			bool isOp = isOperator(infix[i]), prevIsOp = isOperator(infix[i - 1]);
			
			if (isOp && prevIsOp && infix[i] != "(" && infix[i - 1] != ")") 
			{
				cout << "Error: Missing operands in the expression" << endl;
				return;
			}
			else if (!isOp && !prevIsOp && infix[i] != ")" && infix[i - 1] != "(") 
			{
				cout << "Error: Missing operators in the expression" << endl;
				return;
			}
		}
	}

	//empties the stack with a mismatched check
	while (!s.empty()) 
	{
		if (s.top() == "(") 
		{
			cout << "Error: Infix expression has mismatched parens!" << endl;
			return;
		}
		postfix.push_back(s.top());
		s.pop();
	}

	//final checks 
	if (operandCount - operatorCount != 1) 
	{
		if (operandCount <= operatorCount) 
		{
			cout << "Error: Missing operands in the expression" << endl;
			return;
		}
		else 
		{
			cout << "Error: Missing operators in the expression" << endl;
			return;
		}
	}

	cout << "Postfix expression: ";
	for (const string& str : postfix) 
	{
		cout << str << " ";
	}
	cout << endl;
	
	
	evaluatePostfix(postfix);
}

void evaluatePostfix(const vector<string>& postfix)
{
	Stack<double> operandStack;
	
	for (int i = 0; i < postfix.size(); i++)
	{
		if (!(isOperator(postfix[i])))
		{
			try 
			{
				operandStack.push(stold(postfix[i]));
			}
			catch (const std::invalid_argument& e)
			{
				cout << "Postfix evaluation: ";
				for (int i = 0; i < postfix.size(); i++)
				cout << postfix[i] << " ";
				
				cout << " = ";
				
				for (int i = 0; i < postfix.size(); i++)
					cout << postfix[i] << " ";
				cout << endl;
				return;
			}
		}
		else
		{
			double secondOp = operandStack.top();
			operandStack.pop();
			double firstOp = operandStack.top();
			operandStack.pop();

			double result = 0;
			if (postfix[i] == "+") 
				result = firstOp + secondOp;
			else if (postfix[i] == "-") 
				result = firstOp - secondOp;
			else if (postfix[i] == "*") 
				result = firstOp * secondOp;
			else if (postfix[i] == "/") 
				result = firstOp / secondOp;
			operandStack.push(result);

		}
	}
	cout << "Postfix evaluation: ";
	for (int i = 0; i < postfix.size(); i++)
		cout << postfix[i] << " ";

	cout << " = ";
	cout << operandStack.top() << endl;
}


vector<string> input2vector(const string& choice) //converts the input string into a vector of strings using space as the delimiter.
{
	vector<string> v; //creates the vector that it will return later
	int start = 0;
	int end = 0;
	char dl = ' ';

	while ((start = choice.find_first_not_of(dl, end)) != string::npos)
	{
		end = choice.find(dl, start);
		if (end == string::npos) 
			{
			v.push_back(choice.substr(start));
			break; 
			}
		v.push_back(choice.substr(start, end - start));
	}
	return v;
}
