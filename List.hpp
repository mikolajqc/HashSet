//Mikolaj Ciesielski
//Plik z implementacja klasy List

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
	clean();
	delete headNode;
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
		newNode->nextNode = endNode;
	}
	++size;
	return true;
}

template <class T>
int List<T>::erase(T value)
{
	std::vector<List<T>::Iterator> iterators;
	int result = 0;
	
	if (!find(value, iterators)) return result;
	
	for(unsigned int i = 0; i < iterators.size(); ++i)
	{
		result += erase(iterators[i]);
	}
	return result;
}

template <class T>
bool List<T>::clean()
{
	if(empty()) return false;
	
	List<T>::Iterator i = begin();
	
	while(i!=end())
	{
		List<T>::Iterator temp = i++;
		erase(temp);
	}
	return true;
}