using namespace std;

template<class T>
class Node
{
public:
	Node<T>* next;
	T data;
	Node(T value)
	{
		data = value;
		next = NULL;
	}
};
