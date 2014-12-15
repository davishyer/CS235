#include "GPAInterface.h"
#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;

class GPA : public GPAInterface
{
	private:
		map<unsigned long long int, StudentInterface*> myMap;
		set<StudentInterface*, Comparator> mySet;

		bool validateFile(string filename)
		{
			ifstream reader;
			reader.open(filename.c_str());
			if(reader.fail())
			{
				return false;
			}
			unsigned long long int id;
			string name;
			string address;
			string phone;
			while(!reader.eof())
			{
				if(!isdigit(reader.peek()))
				{
					reader.get();
				}
				else
				{
					reader >> id;
					reader.get();
					if(!getline(reader, name) || !getline(reader, address) || !getline(reader, phone))
					{
						return false;
					}
				}
			}
			return true;
		}

		double convertLetter(string letter)
		{
			if(letter == "A")
			{
				return 4.0;
			}
			if(letter == "A-")
			{
				return 3.7;
			}
			if(letter == "B+")
			{
				return 3.4;
			}
			if(letter == "B")
			{
				return 3.0;
			}
			if(letter == "B-")
			{
				return 2.7;
			}
			if(letter == "C+")
			{
				return 2.4;
			}
			if(letter == "C")
			{
				return 2.0;
			}
			if(letter == "C-")
			{
				return 1.7;
			}
			if(letter == "D+")
			{
				return 1.4;
			}
			if(letter == "D")
			{
				return 1.0;
			}
			if(letter == "D-")
			{
				return 0.7;
			}
			if(letter == "E")
			{
				return 0.0;
			}
			return 0.0;
		}

		void giveGrade(unsigned long long int id, double grade)
		{
			if(myMap.find(id) != myMap.end())
			{
				myMap.find(id)->second->addGPA(grade);
			}
			else
			{
				for(set<StudentInterface*, Comparator>::iterator it = mySet.begin(); it != mySet.end(); ++it)
				{
					StudentInterface* temp = (*it);
					if(temp->getID() == id)
					{
						temp->addGPA(grade);
						break;
					}
				}
			}
		}

	public:
		GPA(void)
		{

		}
		~GPA(void)
		{
			clear();
		}

		/*
		 * getMap()
		 *
		 * Returns the map storing the student information.
		 * The key of the map should be the student ID.
		 */
		map<unsigned long long int,StudentInterface*> getMap()
		{
			return myMap;
		}

		/*
		 * getSet()
		 *
		 * Returns the set storing the student information.
		 */
		set<StudentInterface*,Comparator> getSet()
		{
			return mySet;
		}

		/*
		 * importStudents()
		 *
		 * Read in and parse through the given files. Each part of an entry in a
		 * file is given on a separate line in the file. Student ID is first, name is
		 * second, address is third, and phone is last. There are no blank lines between
		 * students. The following is an example file:
		 *
		 *	 5291738600
		 * 	 Dick B. Smith
		 * 	 879 Maple Road, Centralia, Colorado 24222
		 * 	 312-000-1000
		 * 	 9251738707
		 *	 Harry C. Anderson
		 *	 635 Main Drive, Midville, California 48444
		 * 	 660-050-2200
		 *
		 * If a valid file is given, the new Students should be added to the existing
		 * map and set.
		 *
		 * If an invalid file name is given or if there is a missing entry for a student,
		 * return false. Duplicate student ID numbers and duplicate students will not be
		 * tested for. There will never be a student that exists in the map and set. If
		 * the function returns false, then no changes should have been made to the
		 * existing map or set.
		 *
		 * The key of the map should be the student ID.
		 *
		 * Returns false if an invalid filename is given or if there is a missing entry for a
		 * student, otherwise true.
		 */
		bool importStudents(string mapFileName, string setFileName)
		{
			if(validateFile(mapFileName) && validateFile(setFileName))
			{
				ifstream readMap;
				readMap.open(mapFileName.c_str());
				unsigned long long int id;
				string name;
				string address;
				string phone;
				while(!readMap.eof())
				{
					if(!isdigit(readMap.peek()))
					{
						readMap.get();
					}
					else
					{
						readMap >> id;
						readMap.get();
						getline(readMap, name);
						getline(readMap, address);
						getline(readMap, phone);
						myMap[id] = new Student(id, name, address, phone);
					}
				}
				ifstream readSet;
				readSet.open(setFileName.c_str());
				while(!readSet.eof())
				{
					if(!isdigit(readSet.peek()))
					{
						readSet.get();
					}
					else
					{
						readSet >> id;
						readSet.get();
						getline(readSet, name);
						getline(readSet, address);
						getline(readSet, phone);
						mySet.insert(new Student(id, name, address, phone));
					}
				}
				return true;
			}
			return false;
		}

		/*
		 * importGrades()
		 *
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
		 *  	A-
		 *
		 * Compute the GPA by finding the average of all the grades with a matching student ID
		 * in the Grade file. The GPA is calculated by taking a Student's total sum GPA and
		 * dividing by the number of classes taken. If the given student ID has no matching
		 * grades in the Grade file, the GPA is 0.00. It is not necessary to store the course
		 * names so long as the total number of courses taken is counted.
		 *
		 * You may assume that the given student ID exists in the map or set.
		 *
		 * Use the following point values for each grade.
		 *
		 *		  A = 4.0  A- = 3.7
		 *	B+ = 3.4  B = 3.0  B- = 2.7
		 *	C+ = 2.4  C = 2.0  C- = 1.7
		 *	D+ = 1.4  D = 1.0  D- = 0.7
		 *		  E = 0.0
		 *
		 * Returns false if an invalid filename is given, otherwise true.
		 */
		bool importGrades(string fileName)
		{
			ifstream reader;
			reader.open(fileName.c_str());
			if(!reader.fail())
			{
				unsigned long long int id;
				string Class;
				string letter;
				while(!reader.eof())
				{
					if(!isdigit(reader.peek()))
					{
						reader.get();
					}
					else
					{
						reader >> id;
						reader.get();
						getline(reader, Class);
						getline(reader, letter);
						giveGrade(id, convertLetter(letter));
					}
				}
				return true;
			}

			return false;
		}

		/*
		 * querySet()
		 *
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
		 * 	5291738860 2.85 Dick B. Smith
		 *	9251733870 3.00 Harry C. Anderson
		 *
		 * Return a string representation of the given query. If an invalid file name is given,
		 * then return an empty string. The precision of the GPA will be rounded to two decimal places.
		 * There will be a trailing new line.
		 */
		string querySet(string fileName)
		{
			ifstream reader;
			reader.open(fileName.c_str());
			string output = "";
			if(!reader.fail())
			{
				unsigned long long int id;
				while(!reader.eof())
				{
					if(!isdigit(reader.peek()))
					{
						reader.get();
					}
					else
					{
						reader >> id;
						reader.get();
						for(set<StudentInterface*, Comparator>::iterator it = mySet.begin(); it != mySet.end(); ++it)
						{
							StudentInterface* temp = *it;
							if(temp->getID() == id)
							{
								stringstream ss;
								ss << id;
								output += ss.str() + " ";
								output += temp->getGPA() + " ";
								output += temp->getName() + "\n";
							}
						}
					}
				}
			}
			
			cout << "\n*****************************************\n";
			cout << output << endl;
			return output;
		}

		/*
		 * queryMap()
		 *
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
		 *	9251733870 3.00 Harry C. Anderson
		 *
		 * Return a string representation of the given query. if an ivalid file name is given,
		 * then return an empty string. The precision of the GPA will be rounded to two decimal places.
		 * There will be a trailing new line.
		 */
		string queryMap(string fileName)
		{
			ifstream reader;
			string output = "";
			reader.open(fileName.c_str());
			unsigned long long int id;
			if(!reader.fail())
			{
				while(!reader.eof())
				{
					if(!isdigit(reader.peek()))
					{
						reader.get();
					}
					else
					{
						reader >> id;
						reader.get();
						if(myMap.find(id) != myMap.end())
						{
							StudentInterface* temp = myMap.find(id)->second;
							stringstream ss;
							ss << id;
							output += ss.str() + " ";
							output += temp->getGPA() + " ";
							output += temp->getName() + "\n";
						}
					}
				}
			}
			return output;
		}

		/*
		 * Clears the students from the map and set.
		 */
		void clear()
		{
			for(map<unsigned long long int, StudentInterface*>::iterator it = myMap.begin(); it != myMap.end(); ++it)
			{
				delete it->second;
			}
			for(set<StudentInterface*, Comparator>::iterator it = mySet.begin(); it != mySet.end(); ++it)
			{
				delete (*it);
			}
			myMap.clear();
			mySet.clear();
		}
};
