#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stdlib.h>

using namespace std;


class ExpressionManager : public ExpressionManagerInterface
{
private:

	bool isOp(string x)
	{
		if(x == "+" || x == "-" || x == "*" || x == "/" || x == "%")
		{
			return true;
		}
		return false;
	}

	int evaluate(int l, int r, string o)
	{
		if(o == "+")
		{
			return l + r;
		}
		if(o == "-")
		{
			return l - r;
		}
		if(o == "*")
		{
			return l * r;
		}
		if(o == "/")
		{
			if(r == 0)
			{
				return -1000;
			}
			return l / r;
		}
		if(o == "%")
		{
			return l % r;
		}
		return 0;
	}

public:
		ExpressionManager(){}
		~ExpressionManager(){}

	/*
	* Checks whether an expression is balanced on its parentheses
	*
	* - The given expression will have a space between every number or operator
	*
	* @return true if expression is balanced
	* @return false otherwise
	*/

	bool isBalanced(string expression)
	{
		stack<string> myStack;
		stringstream ss(expression);
		string next;
		while(ss >> next)
		{
			if(next == "(" || next == "{" || next == "[")
			{
				myStack.push(next);
			}
			else if(next == ")" || next == "}" || next == "]")
			{
				if(!myStack.empty())
				{
					string temp = myStack.top();
					if(next == ")" && temp != "(")
					{
						return false;
					}
					else if(next == "]" && temp != "[")
					{
						return false;
					}
					else if(next == "}" && temp != "{")
					{
						return false;
					}
					myStack.pop();
				}
				else
				{
					return false;
				}
			}
		}
		if(myStack.empty())
		{
			return true;
		}
		return false;
	}

	/**
	 * Converts a postfix expression into an infix expression
	 * and returns the infix expression.
	 *
	 * - The given postfix expression will have a space between every number or operator.
	 * - The returned infix expression must have a space between every number or operator.
	 * - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
	 * - Check lab requirements for what will be considered invalid.
	 *
	 * return the string "invalid" if postfixExpression is not a valid postfix expression.
	 * otherwise, return the correct infix expression as a string.
	 */
	string postfixToInfix(string postfixExpression)
	{
		stack<string> myStack;
		stringstream ss(postfixExpression);
		string next;
		while(ss >> next)
		{
			if(isdigit(next[0]))
			{
				for(int i = 1; i < next.size(); i++)
				{
					if(!isdigit(next[i]))
					{
						return "invalid";
					}
				}
				myStack.push(next);
			}
			else if(isOp(next))
			{
				if(myStack.size() < 2)
				{
					return "invalid";
				}
				string R = myStack.top();
				myStack.pop();
				string L = myStack.top();
				myStack.pop();
				string output = "( " + L + " " + next + " " + R + " )";
				myStack.push(output);
			}
			else
			{
				return "invalid";
			}
		}
		if(myStack.size() == 1)
		{
			return myStack.top();
		}
		return "invalid";
	}

	/*
	 * Converts an infix expression into a postfix expression
	 * and returns the postfix expression
	 *
	 * - The given infix expression will have a space between every number or operator.
	 * - The returned postfix expression must have a space between every number or operator.
	 * - Check lab requirements for what will be considered invalid.
	 *
	 * return the string "invalid" if infixExpression is not a valid infix expression.
	 * otherwise, return the correct postfix expression as a string.
	 */
	string infixToPostfix(string infixExpression)
	{
		if(isBalanced(infixExpression))
		{
			stack<string> myStack;
			stringstream ss(infixExpression);
			string output = "";
			string prev = "a";
			string next;
			while(ss >> next)
			{
				if(isOp(next) && isOp(prev))
				{
					return "invalid";
				}
				if(isOp(prev) && next == ")")
				{
					return "invalid";
				}
				if(isdigit(prev[0]) && isdigit(next[0]))
				{
					return "invalid";
				}
				prev = next;
				if(isdigit(next[0]))
				{
					for(int i = 1; i < next.length(); i++)
					{
						if(!isdigit(next[i]))
						{
							return "invalid";
						}
					}
					output += next + " ";
				}
				else if(isOp(next))
				{
					if(myStack.empty())
					{
						myStack.push(next);
					}
					else if(!isOp(myStack.top()))
					{
						myStack.push(next);
					}
					else
					{
						string top = myStack.top();
						if(next == "*" || next == "/" ||  next == "%")
						{
							if(top == "*" || top == "/" ||  top == "%")
							{
								output += top + " ";
								myStack.pop();
								myStack.push(next);
							}
							else
							{
								myStack.push(next);
							}
						}
						else
						{
							output += top + " ";
							myStack.pop();
							myStack.push(next);
						}
					}
				}
				else if(next == "(")
				{
					myStack.push(next);
				}
				else if(next == ")")
				{
					while(myStack.top() != "(")
					{
						output += myStack.top() + " ";
						myStack.pop();
					}
					myStack.pop();
				}
				else if(next != " ")
				{
					return "invalid";
				}
			}
			while(myStack.size() != 0)
			{
				if(output.length() == 0)
				{
					return "invalid";
				}
				output += myStack.top() + " ";
				myStack.pop();
			}
			output = output.substr(0, output.length() - 1);
			return output;
		}
		return "invalid";
	}

	/*
	 * Evaluates a postfix expression returns the result as a string
	 *
	 * - The given postfix expression will have a space between every number or operator.
	 * - Check lab requirements for what will be considered invalid.
	 *
	 * return the string "invalid" if postfixExpression is not a valid postfix Expression
	 * otherwise, return the correct evaluation as a string
	 */
	string postfixEvaluate(string postfixExpression)
	{
		stack<string> myStack;
		stringstream ss(postfixExpression);
		string next;
		while(ss >> next)
		{
			if(isdigit(next[0]))
			{
				myStack.push(next);
			}
			else if(isOp(next))
			{
				if(myStack.size() < 2)
				{
					return "invalid";
				}
				string R = myStack.top();
				myStack.pop();
				string L = myStack.top();
				myStack.pop();
				int r = atoi(R.c_str());
				int l = atoi(L.c_str());
				string result;
				int i = evaluate(l, r, next);
				if(i == -1000)
				{
					return "invalid";
				}
				stringstream s;
				s << i;
				s >> result;
				myStack.push(result);
			}
			else
			{
				return "invalid";
			}
		}
		if(myStack.size() == 1)
		{
			return myStack.top();
		}
		return "invalid";
	}
};
