#include "QSInterface.h"
#include <sstream>


class QS : public QSInterface
{
private:
	void switchIntegers(int &data[], int left, int right)						//switches integer values
	{
		int temp = data[left];
		data[left] = data[right];
		data[right] = temp;
	}

public:
	QSInterface(){}
	~QSInterface(){}

	/*
	 * For all methods below, it is assumed that the given array's size is correctly provided by the following parameter.
	 */

	/*
	 * sortAll()
	 *
	 * Sorts elements of the given array.  After this method is called, every
	 * element in the array is less than or equal to the following element.
	 *
	 * Does nothing if the given array is empty.
	 *
	 * @param data
	 * 		an array of integers
	 * @param size
	 * 		the correct size of the given array
	 */
	void sortAll(int data[], int size)
	{
		if(size > 1)			//valid size
		{
			sort(data[], size, 0, size - 1);
		}

	}

	/*
	 * sort()
	 *
	 * Sorts elements of the given array between the two given indices.  After
	 * this method is called, every element between the indices is less than or
	 * equal to the following element.
	 *
	 * Does nothing if the given array is empty, if either of the given integers
	 * is out of bounds, or if the first integer is not less than the second
	 * integer.
	 *
	 * @param data
	 * 		an array of integers
	 * @param size
	 * 		the correct size of the given array
	 * @param left
	 * 		the left boundary for the subarray to sort
	 * @param right
	 * 		the right boundary for the subarray to sort
	 */
	void sort(int data[], int size, int left, int right)
	{
		if(size != 0)						//valid size
		{
			if(left >= 0 && left <= size - 1)		//valid left index
			{
				if(right > left && right <= size - 1)	//valid right index
				{
					int pivot = right;
					for(int i = left; i < right; i++)
					{
						if(data[i] > data[pivot])
						{
							switchIntegers(data[], i, pivot);
						}
					}
					sort(data[], size - 1, left, right - 1);
				}
			}
		}
	}
};
