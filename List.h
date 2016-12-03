#ifndef LIST_H
#define LIST_H

#include "Node.h"

template <class T>
class List
{
	
public:
	List();
	~List();

	bool insert(T value);
	bool erase(T value);
	bool clean();//cleaning all list
	bool empty();
	size_t getSize();
	
	class Iterator: public std::iterator<std::forward_iterator_tag, T>
	{
		friend class List;
	public:
		Iterator(Node<T>* n, List* l)
		:node(n), list(l){}
		
		T operator*() //is it possible?
		{
			return node->getValue();
		}
		
		Iterator& operator++()
		{
			node = node->nextNode;
			return *this;
		}
		
		Iterator operator++(int)
		{
			Iterator temp = *this;
			this->node = this->node->next;
			return temp;
		}
	
	private:
		Node<T>* node;
		List* list;
	};
	
	Iterator begin()
	{
		return Iterator(this->headNode, this);
	}
	Iterator end()
	{
		return Iterator(this->endNode, this);
	}

private:
	Node<T>* headNode; //pointers are equal if the list is empty
	Node<T>* endNode; // necessary?
	size_t size;
	
	
	
	
};

#include "List.hpp"

#endif /* LIST_H */