#include "StudentInterface.h"
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Student : public StudentInterface
{
	public:
		unsigned long long int ID;
		string name;
		string address;
		string phone;
		double GPA;
		double grades;
		double classes;

		Student(void)
		{
			ID = 0;
			name = "";
			address = "";
			phone = "";
			GPA = 0.0;
			grades = 0.0;
			classes = 0.0;
		};
		Student(unsigned long long int id, string n, string a, string p)
		{
			ID = id;
			name = n;
			address = a;
			phone = p;
			GPA = 0.0;
			grades = 0.0;
			classes = 0.0;
		}
		~Student(void){};

		/*
		 * The student object will be put into string representation. Student info will be
		 * ordered ID, name, address, phone number, and GPA. Each piece of information will
		 * be on its own line. The GPA will not have a newline following it. For example,
		 *
		 * 123456789
		 * Ben Thompson
		 * 17 Russell St, Provo, UT 84606
		 * 3.12
		 *
		 * Returns a string representation of the student object.
		 */
		string toString()
		{
			string output = "";
			stringstream ss;
			ss << ID;
			output += ss.str();
			output += "\n" + name;
			output += "\n" + address;
			output += "\n" + phone;
			stringstream s;
			s << fixed << setprecision(2) << GPA;
			output += "\n" + s.str();
			return output;
		}

		void setID(unsigned long long int i)
		{
			ID = i;
		}
		unsigned long long int getId()
		{
			return ID;
		}
		void setName(string n)
		{
			name = n;
		}
		string getName()
		{
			return name;
		}
		void setAddress(string a)
		{
			address = a;
		}
		void setPhone(string p)
		{
			phone = p;
		}
		string getGPA()
		{
			stringstream ss;
			string temp;
			ss << fixed << setprecision(2) << GPA;
			ss >> temp;
			return temp;
		}
		void addGPA(double classGrade)
		{
			grades += classGrade;
			classes++;
			GPA = grades / classes;
		}
		void setGPA()
		{
			
		}
};
