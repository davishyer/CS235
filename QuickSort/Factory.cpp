#include "Factory.h"
#include "QSTestInterface.h"

using namespace std;

/*
 * Unlike all other documents provided, you may modify this document slightly (but do not change its name)
 */
//=======================================================================================
/*
	createQSTest()

	Creates and returns an object whose class extends QSTestInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "QSTest", you might say, "return new QSTest();".
*/
QSTestInterface* Factory::createQSTest()
{
	return new QS();//Modify this line
}
//=======================================================================================
