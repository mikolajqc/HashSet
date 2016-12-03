//#include "Node.h"
template <class T> 
Node<T>::Node()
{
	isEnd = true;
	previousNode = nullptr;
	nextNode = nullptr;
}

template <class T>
Node<T>::Node(T value, Node* previousNode, Node* nextNode)
{
	this->value = value;
	this->previousNode = previousNode;
	this->nextNode = nextNode;
	isEnd = false;
}

template <class T>
T Node<T>getValue()
{
	return value;
}
//bool setValue(T value);