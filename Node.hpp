//#include "Node.h"
template <class T> 
Node<T>::Node()
{
	isEnd = true;
	previousNode = nullptr;
	nextNode = nullptr;
}

template <class T>
Node<T>::Node(T value)
{
	this->value = value;
	isEnd = false;
}

template <class T>
T Node<T>::getValue()
{
	std::cout << "getvalue" << std::endl;
	if(isEnd)
	{
		printf("Attempt to get value from end node!\n");
		T errorValue;
		return errorValue;
	}
	
	return value;
}

template <class T>
bool Node<T>::setValue(T value)
{
	if(isEnd)
	{
		printf("Attempt to set value in end node!\n");
		return false;
	}
	
	this->value = value;
	
	return true;
}