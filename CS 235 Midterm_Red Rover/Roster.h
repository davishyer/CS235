/*
 * Davis Hyer
 * CS 235 Spring 2014 Midterm
 */
#include "Person.h"
#include "LinkedList.h"
#include <cstdlib>

using namespace std;

class Roster
{
public:
	Person roster;
	Person teamOne;
	Person teamTwo;
//*************************************************************************************************************
	bool create(string file_name)
	{
		ifstream create(file_name.c_str());
		if(create.is_open())
		{
			string name;
			int strength;
			int speed;
			while(!create.eof())								//As long as we can read in a new player
			{
				create >> name;
				create >> strength;
				create >> speed;
				roster.addNew(name, strength, speed);			//create the new player with the info
			}
			return true;										//file was read in
		}
		return false;											//file was not read in
	}
//*************************************************************************************************************
	void view()
	{
		if(roster.getSize() == 0)								//roster is empty
		 {
			 cout << "\nRoster Empty\n";
		 }
		 else
		 {
			 for(int i = 0; i < roster.getSize(); i++)
			 {
				 cout <<  roster.getName(i) << endl;			//display the name for each player
			 }
		 }
	}
//*************************************************************************************************************
	void divideTeams()
	{
		if(roster.getSize() < 4)						//check for too few players
		{
			cout << "\nToo few players\n";
			return;
		}
		teamOne.empty();								//clear the teams
		teamTwo.empty();
		if((roster.getSize() % 2) == 0)					//CASE: even number of players
		{
			while(roster.getSize() != 0)
			{
				string n = roster.getName(0);
				teamOne.addNew(n, roster.getStrength(n), roster.getSpeed(n));
				roster.erase(n);
				n = roster.getName(0);
				teamTwo.addNew(n, roster.getStrength(n), roster.getSpeed(n));
				roster.erase(n);
			}
		}
		else											//CASE: odd number of players
		{
			while(roster.getSize() != 1)
			{
				string n = roster.getName(0);
				teamOne.addNew(n, roster.getStrength(n), roster.getSpeed(n));
				roster.erase(n);
				n = roster.getName(0);
				teamTwo.addNew(n, roster.getStrength(n), roster.getSpeed(n));
				roster.erase(n);
			}
		}
	}
//*************************************************************************************************************
	void view1()					//Display team one
	{
		if(teamOne.getSize() == 0)			//the team is empty
		 {
			 cout << "\nTeam 1 Empty\n";
		 }
		 else
		 {
			 cout << "Team 1:\n";
			 for(int i = 0; i < teamOne.getSize(); i++)
			 {
				 string n = teamOne.getName(i);
				 cout << "\t" << n << " " << teamOne.getStrength(n) << " " << teamOne.getSpeed(n) << endl;			//display the name of the players in team 1
			 }
		 }
	}
//*************************************************************************************************************
	void view2()					//Display team two
	{
		if(teamTwo.getSize() == 0)		//the team is empty
		 {
			 cout << "\nTeam 2 Empty\n";
		 }
		 else
		 {
			 cout << "Team 2:\n";
			 for(int i = 0; i < teamTwo.getSize(); i++)
			 {
				 string n = teamTwo.getName(i);
				 cout << "\t" << n << " " << teamTwo.getStrength(n) << " " << teamTwo.getSpeed(n) << endl;			//display the name of the players in team 2
			 }
		 }
	}
//*************************************************************************************************************
	void autoPlay()
	{
		while(teamOne.getSize() > 1 && teamTwo.getSize() > 1)				//continue play until there is a winner
		{
			int n = rand() % teamOne.getSize();
			string runner = teamOne.getName(n);
			n = rand() % teamTwo.getSize();
			string at = teamTwo.getName(n);
//-----------------------------------------------------------------------------------------------------------------------------------------------
			//TEAM ONE RUNNING
			if(teamTwo.tailCase(at))					//running at the tail
			{
				if((teamOne.getStrength(runner) + teamOne.getSpeed(runner)) > (teamTwo.getStrength(at) + teamTwo.strLeft(at)))//runner gets thru
				{
					if(teamTwo.getStrength(at) > teamTwo.strLeft(at))		//tail is the stronger
					{
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);
					}
					else			//tail is the weaker
					{
						at = teamTwo.getName(teamTwo.getSize() - 2);
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);

					}

					if(teamTwo.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 1!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					at = teamTwo.prev(at);
					teamTwo.taken(runner, at, teamOne.getStrength(runner), teamOne.getSpeed(runner));
					teamOne.erase(runner);
					if(teamOne.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
			}
			else
			{
				if((teamOne.getStrength(runner) + teamOne.getSpeed(runner)) > (teamTwo.getStrength(at) + teamTwo.strRight(at)))//runner gets thru
				{
					if(teamTwo.getStrength(at) > teamTwo.strRight(at))		//at is the stronger
					{
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);
					}
					else				//at is the weaker
					{
						at = teamTwo.next(at);
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);
					}
					if(teamTwo.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 1!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					teamTwo.taken(runner, at, teamOne.getStrength(runner), teamOne.getSpeed(runner));
					teamOne.erase(runner);
					if(teamOne.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
			}

			view1();	//display team one after turn
			view2();	//display team two after turn

			//Reassign variables
			n = rand() % teamTwo.getSize();
			runner = teamTwo.getName(n);
			n = rand() % teamOne.getSize();
			at = teamOne.getName(n);
//----------------------------------------------------------------------------------------------------------------------------------------------
			//TEAM TWO RUNNING
			if(teamOne.tailCase(at))					//running at the tail
			{
				if((teamTwo.getStrength(runner) + teamTwo.getSpeed(runner)) > (teamOne.getStrength(at) + teamOne.strLeft(at)))//runner gets thru
				{
					if(teamOne.getStrength(at) > teamOne.strLeft(at))		//tail is the stronger
					{
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);
					}
					else			//tail is the weaker
					{
						at = teamOne.getName(teamOne.getSize() - 2);
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);

					}

					if(teamOne.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					at = teamOne.prev(at);
					teamOne.taken(runner, at, teamTwo.getStrength(runner), teamTwo.getSpeed(runner));
					teamTwo.erase(runner);
					if(teamTwo.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\n\nWinner: Team 1!\n\n";
						return;
					}
				}
			}
			else
			{
				if((teamTwo.getStrength(runner) + teamTwo.getSpeed(runner)) > (teamOne.getStrength(at) + teamOne.strRight(at)))//runner gets thru
				{
					if(teamOne.getStrength(at) > teamOne.strRight(at))		//at is the stronger
					{
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);
					}
					else				//at is the weaker
					{
						at = teamOne.next(at);
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);
					}
					if(teamOne.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					teamOne.taken(runner, at, teamTwo.getStrength(runner), teamTwo.getSpeed(runner));
					teamTwo.erase(runner);
					if(teamTwo.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 1!\n";
						return;
					}
				}
			}
			view1();	//display team one after turn
			view2();	//display team two after turn
		}
	}
//*************************************************************************************************************
	void userPlay()
	{
		while(teamOne.getSize() > 1 && teamTwo.getSize() > 1)
		{
			//TEAM 1 RUNNING-----------------------------------------------------------------------------------
			cout << "Team 1: ";
			for(int i = 0; i < teamOne.getSize(); i++)
			{
				string n = teamOne.getName(i);
				cout << n << " ";			//display the name of the players in team 2
			}
			string choice;
			cout << "\n\tPick: ";	//prompt for a choice
			while(!(cin >> choice))	//case of invalid format
			{
				cout << "\n\tPick: ";
				cin >> choice;
			}
			if(!teamOne.nameExists(choice))	//ensuring the name is valid
			{
				cout << "\n\tPick: ";
				while(!(cin >> choice))	//case of invalid format
				{
					cout << "\n\tPick: ";
					cin >> choice;
				}
			}
			string runner = choice;
			cout << "Team 2: ";
			for(int i = 0; i < teamTwo.getSize(); i++)
			{
				string n = teamTwo.getName(i);
				cout <<  n << " ";			//display the name of the players in team 2
			}
			cout << "\n\tPick: ";	//prompt for a choice
			while(!(cin >> choice))	//case of invalid format
			{
				cout << "\n\tPick: ";
				cin >> choice;
			}
			if(!teamTwo.nameExists(choice))	//ensuring the name is valid
			{
				cout << "\n\tPick: ";
				while(!(cin >> choice))	//case of invalid format
				{
					cout << "\n\tPick: ";
					cin >> choice;
				}
			}
			string at = choice;
			if(teamTwo.tailCase(at))
			{
				if((teamOne.getStrength(runner) + teamOne.getSpeed(runner)) > (teamTwo.getStrength(at) + teamTwo.strLeft(at))) //runner gets thru
				{
					if(teamTwo.getStrength(at) > teamTwo.strLeft(at))		//tail is the stronger
					{
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);
					}
					else			//tail is the weaker
					{
						at = teamTwo.getName(teamTwo.getSize() - 2);
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);

					}

					if(teamTwo.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 1!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					at = teamTwo.prev(at);
					teamTwo.taken(runner, at, teamOne.getStrength(runner), teamOne.getSpeed(runner));
					teamOne.erase(runner);
					if(teamOne.getSize() == 1)		//if this move ends the game, end autoPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
			}
			else
			{
				if((teamOne.getStrength(runner) + teamOne.getSpeed(runner)) > (teamTwo.getStrength(at) + teamTwo.strRight(at)))//runner gets thru
				{
					if(teamTwo.getStrength(at) > teamTwo.strRight(at))		//at is the stronger
					{
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);
					}
					else				//at is the weaker
					{
						at = teamTwo.next(at);
						teamOne.taken(at, runner, teamTwo.getStrength(at), teamTwo.getSpeed(at));
						teamTwo.erase(at);
					}
					if(teamTwo.getSize() == 1)		//if this move ends the game, end userPlay
					{
						cout << "\nWinner: Team 1!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					teamTwo.taken(runner, at, teamOne.getStrength(runner), teamOne.getSpeed(runner));
					teamOne.erase(runner);
					if(teamOne.getSize() == 1)		//if this move ends the game, end userPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
			}

			//TEAM 2 RUNNING---------------------------------------------------------------------------
			cout << "Team 2: ";
			for(int i = 0; i < teamTwo.getSize(); i++)
			{
				string n = teamTwo.getName(i);
				cout <<  n << " ";			//display the name of the players in team 2
			}
			cout << "\n\tPick: ";	//prompt for a choice
			while(!(cin >> choice))	//case of invalid format
			{
				cout << "\n\tPick: ";
				cin >> choice;
			}
			if(!teamTwo.nameExists(choice))	//ensuring the name is valid
			{
				cout << "\n\tPick: ";
				while(!(cin >> choice))	//case of invalid format
				{
					cout << "\n\tPick: ";
					cin >> choice;
				}
			}
			runner = choice;
			cout << "Team 1: ";
			for(int i = 0; i < teamOne.getSize(); i++)
			{
				string n = teamOne.getName(i);
				cout << n << " ";			//display the name of the players in team 2
			}
			cout << "\n\tPick: ";	//prompt for a choice
			while(!(cin >> choice))	//case of invalid format
			{
				cout << "\n\tPick: ";
				cin >> choice;
			}
			if(!teamOne.nameExists(choice))	//ensuring the name is valid
			{
				cout << "\n\tPick: ";
				while(!(cin >> choice))	//case of invalid format
				{
					cout << "\n\tPick: ";
					cin >> choice;
				}
			}
			at = choice;
			if(teamOne.tailCase(at))
			{
				if((teamTwo.getStrength(runner) + teamTwo.getSpeed(runner)) > (teamOne.getStrength(at) + teamOne.strLeft(at))) //runner gets thru
				{
					if(teamOne.getStrength(at) > teamOne.strLeft(at))		//tail is the stronger
					{
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);
					}
					else			//tail is the weaker
					{
						at = teamOne.getName(teamOne.getSize() - 2);
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);

					}

					if(teamOne.getSize() == 1)		//if this move ends the game, end userPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					at = teamOne.prev(at);
					teamOne.taken(runner, at, teamTwo.getStrength(runner), teamTwo.getSpeed(runner));
					teamTwo.erase(runner);
					if(teamTwo.getSize() == 1)		//if this move ends the game, end userPlay
					{
						cout << "\nWinner: Team 1!\n";
						return;
					}
				}
			}
			else
			{
				if((teamTwo.getStrength(runner) + teamTwo.getSpeed(runner)) > (teamOne.getStrength(at) + teamOne.strRight(at)))//runner gets thru
				{
					if(teamOne.getStrength(at) > teamOne.strRight(at))		//at is the stronger
					{
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);
					}
					else				//at is the weaker
					{
						at = teamOne.next(at);
						teamTwo.taken(at, runner, teamOne.getStrength(at), teamOne.getSpeed(at));
						teamOne.erase(at);
					}
					if(teamOne.getSize() == 1)		//if this move ends the game, end userPlay
					{
						cout << "\nWinner: Team 2!\n";
						return;
					}
				}
				else			//runner gets stopped
				{
					teamOne.taken(runner, at, teamTwo.getStrength(runner), teamTwo.getSpeed(runner));
					teamTwo.erase(runner);
					if(teamTwo.getSize() == 1)		//if this move ends the game, end userPlay
					{
						cout << "\nWinner: Team 1!\n";
						return;
					}
				}
			}
		}
	}
//*************************************************************************************************************
	void shuffle()					//randomly reinserts random players
	{
		for(int i = 0; i < (2 * roster.getSize()); i++)//number of shuffles will be equal to twice the size of the roster
		{
			int n = rand() % roster.getSize();		//get player to shuffle
			string shuff = roster.getName(n);
			int m = rand() % roster.getSize();		//get player to insert after
			while(n == m)							//if they are the same player, reassign second until they differ
			{
				m = rand() % roster.getSize();
			}
			string after = roster.getName(m);
			roster.erase(shuff);					//remove the player to be reinserted
			roster.taken(shuff, after, roster.getStrength(shuff), roster.getSpeed(shuff));	//insert the player after the insertion player
		}
	}

};
