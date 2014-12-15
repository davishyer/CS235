#pragma once
#include <iostream>
#include <string>
#include "QSInterface.h"
using namespace std;

/*
 * WARNING: It is expressly forbidden to modify any part of this document, including its name
 */

class QSTestInterface
{
	public:
		QSTestInterface(){}
		virtual ~QSTestInterface(){}

		/*
		 * For all methods below, the correctness of an operation is defined in QSInterface.h.
		 */

		/*
		 * testSortAll
		 *
		 * Returns true if the given QSInterface object correctly sorts given arrays.
		 *
		 * @param test
		 * 		an implementation of the QSInterface class
		 * @return
		 * 		true if [test] correctly sorts; false otherwise
		 */
		virtual bool testSortAll(QSInterface* test) = 0;

		/*
		 * testSort
		 *
		 * Returns true if the given QSInterface object correctly sorts given subarrays.
		 *
		 * @param test
		 * 		an implementation of the QSInterface class
		 * @return
		 * 		true if [test] correctly sorts; false otherwise
		 */
		virtual bool testSort(QSInterface* test) = 0;
};
