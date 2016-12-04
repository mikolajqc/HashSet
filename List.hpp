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
	Node<T>* newNode = new Node<T>(value);
	
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
	++size;
	return true;
}

template <class T>
bool List<T>::erase(T value)
{
	if(empty()) return false;
	
	
	for(List<T>::Iterator i = begin();i!=end(); ++i)
	{
		if(*i == value)
		{
			if(i == begin())
			{
				headNode = headNode->nextNode;
				headNode->previousNode = nullptr;
			}
			else
			{
				(&i)->previousNode->nextNode = (&i)->nextNode;
				(&i)->nextNode->previousNode = (&i)->previousNode;
			}
			delete(&i);
			--size;
			return true;
		}
	}
	
	return false;
}

template <class T>
bool List<T>::clean()
{
	if(empty()) return false;
	
	for(List<T>::Iterator i = begin();i!=--end();++i)
	{
		erase(*i); //do poprawki erase powinien przjmowac iterator
	}
	
	return true;
}