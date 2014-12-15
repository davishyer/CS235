#pragma once
#include <iostream>
#include <string>
#include <stack>
#include "ExpressionManagerInterface.h"
#include <vector>
#include <stack>
#include <sstream>


using namespace std;


class ExpressionManager : public ExpressionManagerInterface
{
	public:
		ExpressionManager(){}
		~ExpressionManager(){}
	private:
		bool isdigit(string c)
		{
			stringstream ss(c);
			int e;
			if(ss >> e)
			{
				if(ss.peek() == '.')
				{
					return false;
				}
				return true;
			}
			return false;
		}
		bool is_op(string c)
		{
			if(c == "+" || c == "-" || c == "*" || c == "/" || c == "%")
			{
				return true;
			}
			return false;
		}
		string eval_op(string op, vector<int> operands)
		{
			if(operands.empty())
			{
				return "invalid";
			}
			int size = operands.size();
			int rhs = operands[size - 1];
			operands.pop_back();
			if(operands.empty())
			{
				return "invalid";
			}
			size = operands.size();
			int lhs = operands[size - 1];
			operands.pop_back();
			int result = 0;
			if(op == "+")
			{
				result = lhs + rhs;
			}
			else if(op == "-")
			{
				result = lhs - rhs;
			}
			else if(op == "*")
			{
				result = lhs * rhs;
			}
			else if(op == "/")
			{
				if(rhs != 0)
				{
					result = lhs / rhs;
				}
				else
				{
					return "invalid";
				}
			}
			else if(op == "%")
			{
				result = lhs % rhs;
			}
			stringstream ss;
			ss << result;
			string x = ss.str();
			return x;
		}

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
		vector<char> parenth;
		char c;
		char item;
		unsigned d;
		for(unsigned i = 0; i < expression.size(); i++)
		{
			c = expression[i];
			if(c == '[' || c == '{' || c == '(')		//found an opening parenth
			{
				parenth.push_back(c);					//add the char to the vector
			}
			else if(c == ']' || c == '}' || c == ')')	//found a closing parenth
			{
				d = parenth.size();
				if(d == 0)
				{
					return false;
				}
				item = parenth[d - 1];					//set comparison to final char in vector
				parenth.pop_back();						//remove final char in vector
				if(c == ']')							//CASE: ]
				{
					if(item != '[')
					{
						parenth.clear();				//empty entire vector
						return false;					//if no match, expression is invalid
					}
				}
				else if(c == '}')						//CASE: }
				{
					if(item != '{')
					{
						parenth.clear();				//empty entire vector
						return false;					//if no match, expression is invalid
					}
				}
				else if(c == ')')						//CASE: )
				{
					if(item != '(')
					{
						parenth.clear();				//empty entire vector
						return false;					//if no match, expression is invalid
					}
				}
			}
			else
			{
			}
		}
		if(parenth.size() != 0)
		{
			parenth.clear();				//empty entire vector
			return false;					//expression is invalid
		}
		else
		{
			parenth.clear();
			return true;					// expression is valid
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
		if(isBalanced(postfixExpression))
		{
			string c;
			stringstream s;
			s << postfixExpression;
			while(s >> c)
			{
				if(!isdigit(c) && !is_op(c) && c != " ")
				{
					return "invalid";
				}
			}
			vector<string> output;
			string chara;
			stringstream ss;
			ss<< postfixExpression;
			while(ss >> chara)
			{
				if(is_op(chara))
				{
					if(output.size() < 2)
					{
						return "invalid";
					}
					string right = output[output.size() - 1];
					output.pop_back();
					string left = output[output.size() - 1];
					output.pop_back();
					string back = "( " + left + " " + chara + " " + right + " )";
					output.push_back(back);
				}
				else
				{
					output.push_back(chara);
				}
			}
			if(output.size() == 1)
			{
				return output[0];
			}

			return "invalid";
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
			string c;
			stringstream s;
			s << infixExpression;
			while(s >> c)
			{
				if(!isdigit(c) && !is_op(c) && c != "(" && c != ")" && c != " ")
				{
					return "invalid";
				}
			}

			istringstream infix(infixExpression);
			string next_char;
			string prev = "0";
			vector<string> output;
			vector<string> operands;
			while(infix >> next_char)
			{
				if(is_op(next_char) && output.empty())
				{
					return "invalid";
				}
				if(is_op(next_char) && is_op(prev))
				{
					return "invalid";
				}
				else if(next_char == ")" && is_op(prev))
				{
					return "invalid";
				}
				prev = next_char;
				if(isdigit(next_char))
				{
					output.push_back(next_char);
					output.push_back(" ");
				}
				else if(next_char == "(")
				{
					operands.push_back(next_char);
				}
				else if(next_char == ")")
				{
					if(operands.size() == 0)
					{
						return "invalid";
					}
					string oper = operands[operands.size() - 1];
					if(oper == "(")
					{
						operands.pop_back();
					}
					else if(is_op(oper))
					{
						output.push_back(oper);
						output.push_back(" ");
						operands.pop_back();
						operands.pop_back();
					}
					else
					{
						return "invalid";
					}
				}
				else if(is_op(next_char))
				{
					if(operands.empty())
					{
						operands.push_back(next_char);
					}
					else
					{
						string oper = operands[operands.size() - 1];
						if(is_op(oper))
						{
							if(next_char == "*" || next_char == "/" || next_char == "%")
							{
								if(oper == "*" || oper == "/" || oper == "%")
								{
									output.push_back(oper);
									output.push_back(" ");
									operands.pop_back();
									operands.push_back(next_char);
								}
								else
								{
									operands.push_back(next_char);
								}
							}
							else
							{
								output.push_back(oper);
								output.push_back(" ");
								operands.pop_back();
								operands.push_back(next_char);
							}
						}
						else
						{
							operands.push_back(next_char);
						}
					}
				}
				else
				{
					return "invalid";
				}
			}

			while(operands.size() != 0)
			{
				string oper = operands[operands.size() - 1];
				output.push_back(oper);
				output.push_back(" ");
				operands.pop_back();
			}
			output.pop_back();
			stringstream ss;
			for(unsigned i = 0; i < output.size(); i++)
			{
				ss << output[i];
			}
			string final = ss.str();
			return final;
		}
		infixExpression = "invalid";
		return infixExpression;
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
		istringstream tokens(postfixExpression);
		string next_char;
		vector<int> number;
		int e;
		string c;
		while(tokens >> next_char)
		{
			if(isdigit(next_char))
			{
				istringstream (next_char) >> e;
				number.push_back(e);
			}
			else if(is_op(next_char))
			{
				c = eval_op(next_char, number);
				if(c == "invalid")
				{
					return "invalid";
				}
				else
				{
					number.pop_back();
					number.pop_back();
					istringstream (c) >> e;
					number.push_back(e);
				}
			}
			else
			{
				return "invalid";
			}

		}
		if(number.size() == 1)
		{
			int a = number[0];
			stringstream ss;
			ss << a;
			string str = ss.str();
			return str;
		}
		else
		{
			return "invalid";
		}
	}


};
