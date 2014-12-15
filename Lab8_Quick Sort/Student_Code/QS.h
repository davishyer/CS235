#pragma once
#include <iostream>
//#include <array>
#include <string>
#include <sstream>
#include "QSInterface.h"
using namespace std;


class QS : public QSInterface
{
private:
	int *myArray;
	int Size;
	int position;
	int length;

	void recursion(int x, int y, int z)
	{
		if((x + 1) != z)			//check if array is size 1
		{
			z--;
			if(x + 1 == z)			//check if array is size 2
			{
				if(myArray[x] > myArray[z])
				{
					int temp = myArray[x];
					myArray[x] = myArray[z];
					myArray[z] = temp;
				}
			}
			else
			{
				int newer = medianOfThree(x,z);
				int thisOne = partition(x, z, newer);
				recursion(x, z, thisOne);
			}
		}

		if((z + 1) != y)			//check if array is size 1
		{
			z++;
			if(y - 1 == z)			//check if array is size 2
			{
				if(myArray[z] > myArray[y])
				{
					int temp = myArray[z];
					myArray[z] = myArray[y];
					myArray[y] = temp;
				}
			}
			else
			{
				int newest = medianOfThree(z, y);
				int here = partition(z, y, newest);
				recursion(z, y, here);
			}
		}

	}

	public:
		QS()
		{
			Size = 0;
			position = 0;
			myArray = NULL;
			length = 0;
		}
		~QS()
		{
			clear();
		}

		/*
		 * sortAll()
		 *
		 * Sorts elements of the array.  After this method is called, every
		 * element in the array is less than or equal to the following element.
		 *
		 * Does nothing if the array is empty.
		 */
		void sortAll()
		{
			if(Size == 0 || position == 0)
			{
				return;
			}
			int x = 0;
			int y = Size - 1;
			int z = medianOfThree(x, y);
			int index = partition(x, y, z);
			recursion(x, y, index);
		}

		/*
		 * medianOfThree()
		 *
		 * Performs median-of-three pivot selection from among the values in
		 * the array between the two given indices. Median-of-three pivot
		 * selection will sort the first, middle, and last elements in a given
		 * array with respect to each other. After this method is called,
		 * data[first] <= data[middle] <= data[last], where middle =
		 * (first + last)/2.
		 *
		 * Returns -1 if the array is empty, if either of the given integers
		 * is out of bounds, or if the first integer is not less than the second
		 * integer.
		 *
		 * @param left
		 * 		the left boundary for the subarray from which to find a pivot
		 * @param right
		 * 		the right boundary for the subarray from which to find a pivot
		 * @return
		 *		the index of the pivot; -1 if provided with invalid input
		 */
		int medianOfThree(int left, int right)
		{
			if(Size == 0)
			{
				return -1;
			}
			if(left < 0 || right < 0 || left > (Size - 1) || right > (Size - 1))
			{
				return -1;
			}
			if(left > right || left == right)
			{
				return -1;
			}
			int med = (left + right) / 2;
			int temp;
			while(!(myArray[left] <= myArray[med] && myArray[left] <= myArray[right] && myArray[med] <= myArray[right]))
			{
				if(myArray[med] < myArray[left])
				{
					temp = myArray[left];
					myArray[left] = myArray[med];
					myArray[med] = temp;
				}
				if(myArray[med] > myArray[right])
				{
					temp = myArray[right];
					myArray[right] = myArray[med];
					myArray[med] = temp;
				}
			}
			return med;
		}

		/*
		 * Partitions a subarray around a pivot value selected according to
		 * median-of-three pivot selection.
		 *
		 * The values which are smaller than the pivot should be placed to the left
		 * of the pivot; the values which are larger than the pivot should be placed
		 * to the right of the pivot.
		 *
		 * Does nothing and returns -1 if the array is null, if either of the
		 * given integers is out of bounds, or if the first integer is not less than
		 * the second integer, or if the pivot is not between the two boundaries.
		 *
		 * @param left
		 * 		the left boundary for the subarray to partition
		 * @param right
		 * 		the right boundary for the subarray to partition
		 * @param pivotIndex
		 * 		the index of the pivot in the subarray
		 * @return
		 *		the pivot's ending index after the partition completes; -1 if
		 * 		provided with bad input
		 */
		int partition(int left, int right, int pivotIndex)
		{
			//CONDITION CHECKS
			if(myArray == NULL)
			{
				return -1;
			}
			if(left < 0 || right < 0 || left > (getSize() - 1) || right > (getSize() - 1))
			{
				return -1;
			}
			if(left > right || left == right)
			{
				return -1;
			}
			if(left > pivotIndex || right < pivotIndex)
			{
				return -1;
			}
			if(Size == 1)
			{
				return pivotIndex;
			}


			int number = myArray[pivotIndex];
			int place = pivotIndex;
			//LEFT CHECK
			if(left < pivotIndex)
			{
				for(int i = left; i < place; i++)
				{
					if(myArray[i] > number)
					{
						int temp = myArray[i];
						for(int j = i; j <= 100; j++)
						{
							myArray[j] = myArray[(j + 1)];
							if(j == place)
							{
								break;
							}

						}
						myArray[place] = temp;
						place--;
						i--;
					}
				}
			}
			//RIGHT CHECK
			if(right > pivotIndex)
			{
				for(int i = right; i > place; i--)
				{
					if(myArray[i] < number)
					{
						int temp = myArray[i];
						for(int j = i; j >= -100; j--)
						{
							myArray[j] = myArray[(j - 1)];
							if(j == place)
							{
								break;
							}
						}
						myArray[place] = temp;
						place++;
						i++;
					}
				}
			}
			return place;
		}

		/*
		 * Gets the array of values and puts them into a string. For example: if my array
		 *  * looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
		 *  * with no trailing comma.
		 *
		 * Does nothing and returns null, if the array is null or empty.
		 *
		 * @return
		 *		the string representation of the current array
		 */
		string getArray()
		{
			if(Size == 0 || length == 0)
			{
				return "";
			}
			if(length == 1)
			{
				stringstream s;
				s << myArray[0];
				string caseOne;
				s >> caseOne;
				return caseOne;
			}
			string output = "";

			string temp = "";
			for(int i = 0; i < length - 1; i++)			//add all but last number to a string with commas between
			{
				stringstream ss;
				ss << myArray[i];
				ss >> temp;
				temp = temp + ",";
				output = output + temp;
			}
			stringstream final;
			final << myArray[length - 1];
			final >> temp;
			output = output + temp;
			return output;
		}

		/*
		 * Gets the current size of the current array.
		 *
		 * @return
		 * 		the current size
		 */
		int getSize()
		{
			return Size;
		}

		/*
		 * Adds the given value to the array.
		 */
		void addToArray(int value)
		{
			if(Size == 0)
			{
				return;
			}
			myArray[position] = value;
			position++;
			length++;
		}

		/*
		 * Creates an array of with the given size.
		 *
		 * Returns false if the given value is non-positive, true otherwise.
		 *
		 * @param
		 *		size of array
		 * @return
		 *		true if the array was created, false otherwise
		 */
		bool createArray(int size)
		{
			if(size < 0)				//reject bad input
			{
				return false;
			}
			if(myArray != NULL)			//if an array already exists, delete it
			{
				clear();
			}
			myArray = new int[size];
			Size = size;
			position = 0;
			length = 0;
			return true;
		}

		/*
		 * Clears the array.
		 */
		void clear()
		{
			delete[] myArray;
			myArray = NULL;
			Size = 0;
		}
};

