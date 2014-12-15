#include "QSInterface.h"
#include <sstream>
#include <cstddef>

using namespace std;

class QS : public QSInterface
{
	private:
		int size;
		int* values;
		int position;
		int length;

		void swap(int index1, int index2)
		{
			int temp = values[index1];
			values[index1] = values[index2];
			values[index2] = temp;
		}

		void recursion(int left, int right)
		{
			if(left >= right || left < 0 || right < 0)
			{
				return;
			}
			if(right - left == 1)
			{
				if(values[left] > values[right])
				{
					swap(left, right);
				}
				return;
			}
			int pivot = partition(left, right, medianOfThree(left, right));
			recursion(left, (pivot - 1));
			recursion((pivot + 1), right);
		}

	public:
		QS()
		{
			this->size = 0;
			position = 0;
			values = NULL;
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
			recursion(0, this->size - 1);
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
			int pivot = -1;
			if(values != NULL && left >= 0 && right >= 0 && left < length && right < length && left < right)
			{
				pivot = (right + left) / 2;
				if(values[left] > values[pivot])
				{
					swap(left, pivot);
				}
				if(values[pivot] > values[right])
				{
					swap(pivot, right);
				}
				if(values[left] > values[pivot])
				{
					swap(left, pivot);
				}
			}
			return pivot;
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
			int pivot = -1;
			if(values != NULL && left >= 0 && right >= 0 && left < length && right < length && left < right)
			{
				if(left >= pivotIndex || right <= pivotIndex)
				{
					return pivot;
				}

				int pivotValue = values[pivotIndex];
				swap(pivotIndex, right);
				int i = left;
				int j = right - 1;
				while(i < j)
				{
					while(!(values[i] > pivotValue))
					{
						i++;
						if(i == right)
						{
							break;
						}
					}
					while(!(values[j] < pivotValue))
					{
						j--;
						if(j == left)
						{
							break;
						}
					}
					if(i < j)
					{
						swap(i, j);
					}

				}
				pivot = i;
				swap(i, right);
			}
			return pivot;
		}

		/*
		 * Gets the array of values and puts them into a string. For example: if my array 			 * looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0" 			 * with no trailing comma.
		 *
		 * Does nothing and returns an empty string, if the array is null or empty.
		 *
		 * @return
		 *		the string representation of the current array
		 */
		string getArray()
		{	
			string output = "";
			if(this->size != 0 && length != 0)
			{
				for(int i = 0; i < length - 1; i++)			//add all but last number to a string with commas between
				{
					stringstream ss;
					ss << values[i];
					output += ss.str() + ",";
				}
				stringstream final;
				final << values[length - 1];
				output += final.str();
			}
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
			return this->size;
		}

		/*
		 * Adds the given value to the array.
		 */
		void addToArray(int value)
		{
			if(this->size == 0)
			{
				return;
			}
			values[position] = value;
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
			if(size > 0)
			{
				if(values != NULL)
				{
					clear();
				}
				values = new int[size];
				this->size = size;
				position = 0;
				length = 0;
				return true;
			}
			return false;
		}

		/*
		 * Clears the array.
		 */
		void clear()
		{
			this->size = 0;
			delete[] values;
			values = NULL;
		}
};
