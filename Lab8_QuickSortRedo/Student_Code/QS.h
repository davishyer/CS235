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
		void swap(int index1, int index2){
			int temp = values[index1];
			values[index1] = values[index2];
			values[index2] = temp;
		}
		void recursion(int left, int right){
			if(left >= right || left < 0 || right < 0)
				return;
			if(right - left == 1){
				if(values[left] > values[right])
					swap(left, right);
				return;
			}
			int pivot = partition(left, right, medianOfThree(left, right));
			recursion(left, (pivot - 1));
			recursion((pivot + 1), right);
		}
	public:
		QS(){
			this->size = 0;
			position = 0;
			values = NULL;
			length = 0;
		}
		~QS(){
			clear();
		}
		void sortAll(){
			recursion(0, this->size - 1);
		}
		int medianOfThree(int left, int right){
			int pivot = -1;
			if(values != NULL && left >= 0 && right >= 0 && left < length && right < length && left < right){
				pivot = (right + left) / 2;
				if(values[left] > values[pivot])
					swap(left, pivot);
				if(values[pivot] > values[right])
					swap(pivot, right);
				if(values[left] > values[pivot])
					swap(left, pivot);
			}
			return pivot;
		}
		int partition(int left, int right, int pivotIndex){
			int pivot = -1;
			if(values != NULL && left >= 0 && right >= 0 && left < length && right < length && left < right){
				if(left >= pivotIndex || right <= pivotIndex)
					return pivot;
				int pivotValue = values[pivotIndex];
				swap(pivotIndex, right);
				int i = left;
				int j = right - 1;
				while(i < j){
					while(!(values[i] > pivotValue)){
						i++;
						if(i == right)
							break;
					}
					while(!(values[j] < pivotValue)){
						j--;
						if(j == left)
							break;
					}
					if(i < j)
						swap(i, j);
				}
				pivot = i;
				swap(i, right);
			}
			return pivot;
		}
		string getArray(){	
			string output = "";
			if(this->size != 0 && length != 0){
				for(int i = 0; i < length - 1; i++){
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
		int getSize(){
			return this->size;
		}
		void addToArray(int value){
			if(this->size == 0)
				return;
			values[position] = value;
			position++;
			length++;
		}
		bool createArray(int size){
			if(size > 0){
				if(values != NULL)
					clear();
				values = new int[size];
				this->size = size;
				position = 0;
				length = 0;
				return true;
			}
			return false;
		}
		void clear(){
			this->size = 0;
			delete[] values;
			values = NULL;
		}
};
