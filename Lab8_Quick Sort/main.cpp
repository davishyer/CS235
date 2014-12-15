#include "QS.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	int start = clock();
	for(int i = 0; i < 100000; i++)
	{
		QS quick;
		int size = rand() % 20;
		if(size < 3)
		{
			size = 3;
		}
		quick.createArray(size);
		
		for(int j = 0; j < quick.getSize(); j++)
		{
			quick.addToArray(rand() % 100);
		}
		
		quick.sortAll();
		cout << quick.getArray() << endl;
	}
	cout << "\nTime taken to run in seconds: " << ((clock() - start) / 1000000) << endl;
}
