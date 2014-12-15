#pragma once
#include <iostream>
#include <string>
using namespace std;

/*
 * WARNING: It is expressly forbidden to modify any part of this document, including its name
 */

class QSInterface
{
	public:
		QSInterface(){}
		virtual ~QSInterface(){}

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
		virtual void sortAll(int data[], int size) = 0;

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
		virtual void sort(int data[], int size, int left, int right) = 0;

		/*
		 *
		 */
};
