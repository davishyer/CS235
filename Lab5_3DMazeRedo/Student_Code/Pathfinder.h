#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include "PathfinderInterface.h"

using namespace std;

class Pathfinder : public PathfinderInterface
{
	private:
	string move(int a, int b, int c)
	{
		stringstream ss;
		ss << "(" << a << ", " << b << ", " << c << ")";
		string final = ss.str();
		return final;
	}

	bool recursion(int x, int y, int z)
	{
		if(x == 4 && y == 4 && z == 4)
		{
			return true;
		}
		if(x < 4 && toSolveMaze[x + 1][y][z] == 1)
		{
			toSolveMaze[x][y][z] = 2;
			string last = move(x + 1, y, z);
			solution.push_back(last);
			if(recursion(x + 1, y, z))
			{
				return true;
			}
			solution.pop_back();
		}
		if(x > 0 && toSolveMaze[x - 1][y][z] == 1)
		{
			toSolveMaze[x][y][z] = 2;
			string last = move(x - 1, y, z);
			solution.push_back(last);
			if(recursion(x - 1, y, z))
			{
				return true;
			}
			solution.pop_back();
		}
		if(y < 4 && toSolveMaze[x][y + 1][z] == 1)
		{
			toSolveMaze[x][y][z] = 2;
			string last = move(x, y + 1, z);
			solution.push_back(last);
			if(recursion(x, y + 1, z))
			{
				return true;
			}
			solution.pop_back();
		}
		if(y > 0 && toSolveMaze[x][y - 1][z] == 1)
		{
			toSolveMaze[x][y][z] = 2;
			string last = move(x, y - 1, z);
			solution.push_back(last);
			if(recursion(x, y - 1, z))
			{
				return true;
			}
			solution.pop_back();
		}
		if(z < 4 && toSolveMaze[x][y][z + 1] == 1)
		{
			toSolveMaze[x][y][z] = 2;
			string last = move(x, y, z + 1);
			solution.push_back(last);
			if(recursion(x, y, z + 1))
			{
				return true;
			}
			solution.pop_back();
		}
		if(z > 0 && toSolveMaze[x][y][z - 1] == 1)
		{
			toSolveMaze[x][y][z] = 2;
			string last = move(x, y, z - 1);
			solution.push_back(last);
			if(recursion(x, y, z - 1))
			{
				return true;
			}
			solution.pop_back();
		}
		return false;
	}

	public:
		Pathfinder(){}
		~Pathfinder(){}
		int currMaze[5][5][5];
		int toSolveMaze[5][5][5];
		vector<string> solution;

		//Part 1-----------------------------------------------------------------------------------
		/*
		 * getMaze
		 *
		 * Returns a string representation of the current maze. Returns a maze of all 1s if no maze
		 * has yet been generated or imported.
		 *
		 * A valid string representation of a maze consists only of 125 1s and 0s (each separated
		 * by spaces) arranged in five 5x5 grids (each separated by newlines). A valid maze must
		 * also have 1s in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).
		 *
		 * Cell (0, 0, 0) is represented by the first number in the string representation of the
		 * maze. Increasing in x means moving toward the east, meaning cell (1, 0, 0) is the second
		 * number. Increasing in y means moving toward the south, meaning cell (0, 1, 0) is the
		 * sixth number. Increasing in z means moving downward to a new grid, meaning cell
		 * (0, 0, 1) is the twenty-sixth number. Cell (4, 4, 4) is represented by the last number.
		 *
		 * Returns:		string
		 *				A single string representing the current maze
		 */
		string getMaze()
		{
			if(currMaze[0][0][0] != 1 && currMaze[0][0][0] != 0)
			{
				for(int i = 0; i < 5; i++)
				{
					for(int j = 0; j < 5; j++)
					{
						for(int k = 0; k < 5; k++)
						{
							currMaze[i][j][k] = 1;
						}
					}
				}
			}
			stringstream ss;
			for(int i = 0; i < 5; i++)
			{
				for(int j = 0; j < 5; j++)
				{
					for(int k = 0; k < 5; k++)
					{
						ss << currMaze[k][j][i];
						ss << " ";
					}
					ss << "\n";
				}
				ss << "\n";
			}
			string maze = ss.str();
			return maze;
		}

		/*
		 * createRandomMaze
		 *
		 * Generates a random maze and stores it as the current maze.
		 *
		 * The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
		 * in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
		 * solvable or unsolvable, and this method should be able to produce both kinds of mazes.
		 */
		void createRandomMaze()
		{
			for(int i = 0; i < 5; i++)
			{
				for(int j = 0; j < 5; j++)
				{
					for(int k = 0; k < 5; k++)
					{
						currMaze[k][j][i] = rand() % 2;
					}
				}
			}

			currMaze[0][0][0] = 1;
			currMaze[4][4][4] = 1;
		}
		//-----------------------------------------------------------------------------------------

		//Part 2-----------------------------------------------------------------------------------
		/*
		 * importMaze
		 *
		 * Reads in a maze from a file with the given file name and stores it as the current maze.
		 * Does nothing if the file does not exist or if the file's data does not represent a valid
		 * maze.
		 *
		 * The file's contents must be of the format described above to be considered valid.
		 *
		 * Parameter:	file_name
		 *				The name of the file containing a maze
		 * Returns:		bool
		 *				True if the maze is imported correctly; false otherwise
		 */
		bool importMaze(string file_name)
		{
			ifstream import(file_name.c_str());
			if(import.is_open())
			{
				ifstream temp(file_name.c_str());
				temp.is_open();
				int t;
				int size = 0;
				while(temp >> t)
				{
					if((size == 0 && t != 1) || (size == 124 && t != 1))
					{
						temp.close();
						return false;
					}
					size++;
					if(t != 0 && t != 1)
					{
						temp.close();
						return false;
					}
				}
				if(size != 125)
				{
					temp.close();
					return false;
				}

				int s;
				for(int z = 0; z < 5; z++)
				{
					for(int y = 0; y < 5; y++)
					{
						for(int x = 0; x < 5; x++)
						{
							import >> s;
							currMaze[x][y][z] = s;
						}
					}
				}
				import.close();
				return true;
			}
			return false;
		}
		//-----------------------------------------------------------------------------------------

		//Part 3-----------------------------------------------------------------------------------
		/*
		 * solveMaze
		 *
		 * Attempts to solve the current maze and returns a solution if one is found.
		 *
		 * A solution to a maze is a list of coordinates for the path from the entrance to the exit
		 * (or an empty vector if no solution is found). This list cannot contain duplicates, and
		 * any two consecutive coordinates in the list can only differ by 1 for only one
		 * coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
		 * in the solution. Each string in the solution vector must be of the format "(x, y, z)",
		 * where x, y, and z are the integer coordinates of a cell.
		 *
		 * Understand that most mazes will contain multiple solutions
		 *
		 * Returns:		vector<string>
		 *				A solution to the current maze, or an empty vector if none exists
		 */
		vector<string> solveMaze()
		{
			for(int z = 0; z < 5; z++)
			{
				for(int y = 0; y < 5; y++)
				{
					for(int x = 0; x < 5; x++)
					{
						toSolveMaze[x][y][z] = currMaze[x][y][z];
					}
				}
			}
			solution.clear();
			solution.push_back(move(0, 0, 0));
			if(recursion(0, 0, 0))
			{
				return solution;
			}
			solution.clear();
			return solution;
		}
		//-----------------------------------------------------------------------------------------
};
