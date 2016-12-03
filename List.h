#include "Node.h"

template <class T>
class List
{

public:
	List();
	~List();

	bool insert(T value);
	bool erase(T value);

private:
	Node<T>* headNode; //pointers are equal if the list is empty
	Node<T>* endNode; // necessary?
	size_t size;
	
};