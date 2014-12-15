#include "QS.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	QS quick;
	quick.createArray(40);

	quick.addToArray(5);
	quick.addToArray(2);
	quick.addToArray(0);
	quick.addToArray(10);
	quick.addToArray(13);
	quick.addToArray(9);
	quick.addToArray(1);
	quick.addToArray(11);
	quick.addToArray(1);
	quick.addToArray(19);
	quick.addToArray(3);
	quick.addToArray(8);
	quick.addToArray(17);
	quick.addToArray(5);
	quick.addToArray(8);
	quick.addToArray(12);
	quick.addToArray(11);
	quick.addToArray(0);
	quick.addToArray(6);
	quick.addToArray(17);
	quick.addToArray(18);
	quick.addToArray(9);
	quick.addToArray(15);
	quick.addToArray(14);
	quick.addToArray(16);
	quick.addToArray(7);
	quick.addToArray(4);
	quick.addToArray(15);
	quick.addToArray(3);
	quick.addToArray(7);
	quick.addToArray(19);
	quick.addToArray(10);
	quick.addToArray(1);
	quick.addToArray(6);
	quick.addToArray(4);
	quick.addToArray(18);
	quick.addToArray(13);
	quick.addToArray(14);
	quick.addToArray(2);
	quick.addToArray(12);

	cout << quick.getArray() << endl;

	quick.sortAll();
}
