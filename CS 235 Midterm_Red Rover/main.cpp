/*
 * Davis Hyer
 * CS 235 Spring 2014 Midterm
 */
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "Person.h"
#include "Roster.h"

using namespace std;

void menu()
{
	cout << "\n1. Create Roster\n2. View Roster\n3. Shuffle Roster\n4. Create Teams\n5. View Teams\n6. User Play\n7. Auto Play\n8. Quit\n\n";
	return;
}



int main()
{
	int choice = 0;
	while(choice != 8)
	{
		menu();
		if(cin >> choice)
		{
			if(choice == 1)								// Create Roster
			{
				string file;
				cout << "\nEnter name of file to import: ";
				cin >> file;
				if(!(create(file)))
				{
					cout << "\nInvalid Filename\n";
				}
			}
			else if(choice == 2)						// View Roster
			{
				view();
			}
			else if(choice == 3)						// Shuffle Roster
			{
				shuffle();
			}
			else if(choice == 4)						// Create Teams
			{
				divideTeams();
			}
			else if(choice == 5)						// View Teams
			{
				view1();
				view2();
			}
			else if(choice == 6)						// User Play
			{
				userPlay();
			}
			else if(choice == 7)						// Auto Play
			{
				autoPlay();
			}
			else										// Invalid Number
			{
				cout << "\nInvalid Number\n";
				continue;
			}
		}
		else
		{
			cout << "\nInvalid Character\n";
			continue;
		}
	}

	cout << "\n\n~~~~~~~~\nQUITTING\n~~~~~~~~\n";
	return 0;
}
