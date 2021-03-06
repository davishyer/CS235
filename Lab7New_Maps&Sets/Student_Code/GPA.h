#include "GPAInterface.h"
#include "StudentInterface.h"
#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;

class GPA : public GPAInterface
{
	public:
		GPA()
		{
			grades.insert(pair<string, double> ("A", 4.0));
			grades.insert(pair<string, double> ("A-", 3.7));
			grades.insert(pair<string, double> ("B+", 3.4));
			grades.insert(pair<string, double> ("B", 3.0));
			grades.insert(pair<string, double> ("B-", 2.7));
			grades.insert(pair<string, double> ("C+", 2.4));
			grades.insert(pair<string, double> ("C", 2.0));
			grades.insert(pair<string, double> ("C-", 1.7));
			grades.insert(pair<string, double> ("D+", 1.4));
			grades.insert(pair<string, double> ("D", 1.0));
			grades.insert(pair<string, double> ("D-", 0.7));
			grades.insert(pair<string, double> ("E", 0.0));
		};
		~GPA(void)
		{
			clear();
			grades.clear();
		};
		map<unsigned long long int, StudentInterface*> myMap;
		set<StudentInterface*, Comparator> mySet;
		map<string, double> grades;

		/*
		 * Returns the map storing the student information.
		 */
		map<unsigned long long int,StudentInterface*> getMap()
		{
			return myMap;
		}

		/*
		 * Returns the set storing the student information.
		 */
		set<StudentInterface*, Comparator> getSet()
		{
			return mySet;
		}

		/*
		 * Read in and parse through the given files. Each part of an entry in a
		 * file is given on a separate line in the file. Student ID is first, name is
		 * second, address is third, and phone is last. There are no blank lines between
		 * students. The following is an example file:
		 *
		 *	 5291738600
		 * 	 Dick B. Smith
		 * 	 879 Maple Road, Centralia, Colorado 24222
		 * 	 (312) 000-1000
		 * 	 925-173-8707
		 *	 Harry C. Anderson
		 *	 635 Main Drive, Midville, California 48444
		 * 	 (660) 050-2200
		 *
		 * If an invalid file name is given or if there is a missing entry for a student,
		 * return false. If the function returns false, then any changes made to the set or map
		 * should be undone.
		 *
		 * It will be necessary to overload the comparison operator in your Student class
		 * so that the students can be stored in the set alphabetically by first name.
		 *
		 * @param
		 *	file name of the student information to be stored in the map
		 * @param
		 *	file name of the student information to be stored in the set
		 *
		 * @return
		 *	false if an invalid filename is given or if there is a missing entry for a
		 *	student, otherwise true.
		 */
		bool importStudents(string mapFileName, string setFileName)
		{
			map<unsigned long long int, StudentInterface*> tempMap;
			ifstream in(mapFileName.c_str());
			if(!in.is_open())
			{
				return false;
			}
			while(!in.eof())
			{
				unsigned long long int i;
				string temporary;
				getline(in,temporary);
				stringstream ss;
				ss << temporary;
				ss >> i;
				string n;
				if(!getline(in,n))
				{
					mapClear(tempMap);			
					return false;
				}
				string a;
				if(!getline(in,a))
				{
					mapClear(tempMap);
					return false;
				}
				string p;
				if(!getline(in,p))
				{
					mapClear(tempMap);
					return false;
				}
				tempMap[i] = new Student(i, n, a, p);
			}
			in.close();

			set<StudentInterface*, Comparator> tempSet;
			ifstream inFile(setFileName.c_str());
			if(!inFile.is_open())
			{
				mapClear(tempMap);
				return false;
			}
			while(!inFile.eof())
			{
				if(!isdigit(inFile.peek()))
				{
					inFile.get();
				}
				else
				{
					unsigned long long int i;
					string temporary;
					getline(inFile,temporary);
					stringstream ss;
					ss << temporary;
					ss >> i;
					string n;
					if(!getline(inFile,n))
					{
						mapClear(tempMap);							
						setClear(tempSet);
						return false;
					}
					string a;
					if(!getline(inFile,a))
					{
						mapClear(tempMap);
						setClear(tempSet);
						return false;
					}
					string p;
					if(!getline(inFile,p))
					{
						mapClear(tempMap);
						setClear(tempSet);
						return false;
					}
					tempSet.insert(new Student(i, n, a, p));
				}
			}
			inFile.close();

			for ( std::map<unsigned long long int, StudentInterface*>::const_iterator current = tempMap.begin(); current != tempMap.end(); ++ current)
			{
			    myMap[current->first] = current->second;
			}

			tempMap.clear();

			std::copy(tempSet.begin(), tempSet.end(),std::inserter(mySet, mySet.begin() ) );

			tempSet.clear();

			return true;
		}

		/*
		 * Read in and parse through the given file. Each part of an entry in the file
		 * is given on a separate line in the file. Student ID is first, course is
		 * second, and grade is last. There are no blank lines between entries. The
		 * following is an example file:
		 *
		 * 	5291738860
		 * 	CHEM134
		 * 	A
		 * 	9251734870
		 * 	BOT180
		 * 	B
		 * 	9251733870
		 * 	PE273
		 * 	D+
		 * 	5291738760
		 * 	HIS431
		 *
		 * Compute the GPA by finding the average of all the grades with a matching student ID
		 * in the Grade file. If the given student ID has no matching grades in the Grade file,
		 * the GPA is 0.00.
		 *
		 * Use the following point values for each grade.
		 *
		 *		  A = 4.0  A- = 3.7
		 *	B+ = 3.4  B = 3.0  B- = 2.7
		 *	C+ = 2.4  C = 2.0  C- = 1.7
		 *	D+ = 1.4  D = 1.0  D- = 0.7
		 *		  E = 0.0
		 *
		 * Returns false if an invalid filename is given or if there is a missing entry for a
		 * student, otherwise true. You may assume that the student ID exists in your map or set.
		 */
		bool importGrades(string fileName)
		{
			ifstream in(fileName.c_str());
			if(!in.is_open())
			{
				return false;
			}
			while(!in.eof())
			{
				if(!isdigit(in.peek()))
				{
					in.get();
				}
				else
				{	
					unsigned long long int i;
					string temporary;
					getline(in,temporary);
					stringstream ss;
					ss << temporary;
					ss >> i;
					string c;
					if(!getline(in,c))
					{
						return false;
					}
					string g;
					if(!getline(in,g))
					{
						return false;
					}
					if(g.length() > 1)
					{
						if(g.at(1) == '-' || g.at(1) == '+')
						{
							g = g.substr(0, 2);
						}
						else
						{
							g = g.substr(0, 1);
						}
					}
					else
					{
						g = g.substr(0, 1);
					}
					double gpa = grades[g];
					if(myMap.find(i) != myMap.end())
					{
						myMap[i]->addGPA(gpa);
					}
					else
					{
						for(set<StudentInterface*, Comparator>::iterator iter = mySet.begin(); iter != mySet.end(); ++iter)
						{
							StudentInterface* holder = *iter;
							if(holder->getId() == i)
							{
								holder->addGPA(gpa);
								break;
							}
						}
					}
				}
			}
			in.close();
		}

		/*
		 * Read in and parse through the given file. The 'Query' file contains a list of
		 * student ID numbers. Each entry in the Query file is a student ID given on a
		 * line by itself. You are to compute and report the GPA for each of the students
		 * listed in the Query file. The following is an example Query file:
		 *
		 * 	5291738860
		 * 	9251733870
		 *
		 * For each student ID given in the Query file, use the student information stored in
		 * your set to compute the GPA for the student and create an output string which
		 * contains the student ID, GPA, and name. If the given student ID does not match any
		 * student, do not give any output for that student ID. Each line of the output string
		 * contains student ID, GPA, and name as shown:
		 *
		 * 	5291738860 3.85 Dick B. Smith
		 *	9251733870 2.42 Harry C. Anderson
		 *
		 * Return a string representation of the given query. If an invalid file name is given,
		 * then return an empty string. The precision of the GPA must be set to two decimal places.
		 */
		string querySet(string fileName)
		{
			ifstream in(fileName.c_str());
			if(!in.is_open())
			{
				return "";
			}
			string output;
			set<string> visits;
			while(!in.eof())
			{
				if(!isdigit(in.peek()))
				{
					in.get();
				}
				else
				{
					unsigned long long int i;
					string temporary;
					getline(in,temporary);
					stringstream ss;
					ss << temporary;
					ss >> i;
					if(visits.find(temporary) == visits.end())
					{
						visits.insert(temporary);
						for(set<StudentInterface*, Comparator>::iterator iter = mySet.begin(); iter != mySet.end(); ++iter)
						{
							StudentInterface* holder = *iter;
							if(holder->getId() == i)
							{
								if(output != "")
								{
									output += "\n";
								}
								stringstream s;
								s << i << " " << holder->getGPA() << " " << holder->getName();
								output += s.str();
								break;
							}
						}
					}
				}
			}
			output += "\n";
//			cout << "\n*****************************\n";
//			cout << output << endl;
			return output;
		}

		/*
		 * Read in and parse through the given file. The 'Query' file contains a list of
		 * student ID numbers. Each entry in the Query file is a student ID given on a
		 * line by itself. You are to compute and report the GPA for each of the students
		 * listed in the Query file. The following is an example Query file:
		 *
		 * 	5291738860
		 * 	9251733870
		 *
		 * For each student ID given in the Query file, use the student information stored in
		 * your map to compute the GPA for the student and create an output string which
		 * contains the student ID, GPA, and name. If the given student ID does not match any
		 * student, do not give any output for that student ID. Each line of the output string
		 * contains student ID, GPA, and name as shown:
		 *
		 * 	5291738860 2.85 Dick B. Smith
		 *	9251733870 2.42 Harry C. Anderson
		 *
		 * Return a string representation of the given query. If an invalid file name is given,
		 * then return an empty string. The precision of the GPA must be set to two decimal places.
		 */
		string queryMap(string fileName)
		{
			ifstream in(fileName.c_str());
			if(!in.is_open())
			{
				return "";
			}
			string output;
			set<string> visits;
			while(!in.eof())
			{
				unsigned long long int i;
				string temporary;
				getline(in,temporary);
				stringstream ss;
				ss << temporary;
				ss >> i;
				if(visits.find(temporary) == visits.end())
				{
					visits.insert(temporary);
					if(myMap.find(i) != myMap.end())
					{
						StudentInterface* holder = myMap[i];
						if(output != "")
						{
							output += "\n";
						}
						stringstream s;
						s << i << " " << holder->getGPA() << " " << holder->getName();
						output += s.str();
					}
				}
			}
			output += "\n";
			cout << "\n*****************************\n";
			cout << output << endl;
			return output;
		}

		/*
		 * Clears the students from the map and set.
		 */
		void clear()
		{
			typedef map<unsigned long long int, StudentInterface*>::iterator it_type;
			for(it_type iterator = myMap.begin(); iterator != myMap.end(); iterator++) 
			{
				StudentInterface* temp = iterator->second;
				delete temp;
			}
			
			set<StudentInterface*, Comparator>::iterator it;
			for (it = mySet.begin(); it != mySet.end(); ++it)
			{
				StudentInterface* temp = *it;
				delete temp;
			}
			mySet.clear();
			myMap.clear();
		}
		
		void mapClear(map<unsigned long long int, StudentInterface*> &tempMap)
		{
			typedef map<unsigned long long int, StudentInterface*>::iterator it_type;
			for(it_type iterator = tempMap.begin(); iterator != tempMap.end(); iterator++) 
			{
				StudentInterface* temp = iterator->second;
				delete temp;
			}
			tempMap.clear();
		}
		
		void setClear(set<StudentInterface*, Comparator> &tempSet)
		{
			set<StudentInterface*, Comparator>::iterator it;
			for (it = tempSet.begin(); it != tempSet.end(); ++it)
			{
				StudentInterface* temp = *it;
				delete temp;
			}
			tempSet.clear();
		}
			
};
