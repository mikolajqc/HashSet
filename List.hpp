template <class T>
List<T>::List()
{
	headNode = new Node<T>;
	endNode = headNode;
	size = 0;
}

template <class T>
List<T>::~List()
{
	//erasing
	//delete headNode; //temporary !!!!
}

template <class T>
bool List<T>::empty()
{
	if(size == 0) return true;
	return false;
}

template <class T>
size_t List<T>::getSize()
{
	return size;
}

template <class T>
bool List<T>::insert(T value)
{
	Node<T>* newNode = new Node<T>();
	
	if(empty())
	{
		headNode = newNode;
		endNode->previousNode = newNode;
		newNode->nextNode = endNode;
	}
	else
	{
		endNode->previousNode->nextNode = newNode;
		newNode->previousNode = endNode->previousNode;
		endNode->previousNode = newNode;
	}
	return true;
}
//	bool erase(T value);