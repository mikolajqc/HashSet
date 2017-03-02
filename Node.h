#ifndef NODE_H
#define NODE_H

#include <iterator>
#include "List.h"

template <class T>
class Node
{
	template <class F> friend class List;
	
public:
	Node();
	Node(T initValue);
	
	T getValue();
	bool setValue(T value);

private:
	T value;
	Node* previousNode;
	Node* nextNode;
	bool isEnd;
};

#include "Node.hpp"

#endif /* NODE_H */ 
