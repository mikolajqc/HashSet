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
		
		Node<T>* operator&()
		{
			return node;
		}
		
		Iterator& operator++()
		{
			node = node->nextNode;
			std::cout << "++" << std::endl; 
			return *this;
		}
		
		Iterator operator++(int)
		{
			Iterator temp = *this;
			this->node = this->node->nextNode;
			return temp;
		}
		
		Iterator& operator--()
		{
			node = node->previousNode;
			//std::cout << "--" << std::endl; 
			return *this;
		}
		
		Iterator operator--(int)
		{
			Iterator temp = *this;
			this->node = this->node->previousNode;
			return temp;
		}
		
		bool operator==(const Iterator& a) const
		{
			return list == a.list && node == a.node;
		}
		
		bool operator!=(const Iterator& a) const
		{
			return list != a.list || node != a.node;
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
	
	bool erase(Iterator i)
	{
		if(empty() || i == end())
		{
			std::cout << "List is empty or attempt to delete end node!" << std::endl;
			return false;
		}
		if(i ==begin())
		{
			headNode = headNode->nextNode;
			headNode->previousNode = nullptr;
		}
		else
		{
			(&i)->nextNode->previousNode = (&i)->previousNode;
			(&i)->previousNode->nextNode = (&i)->nextNode;
		}
		delete(&i);
		--size;
		return true;
	}

private:
	Node<T>* headNode; //pointers are equal if the list is empty
	Node<T>* endNode; // necessary?
	size_t size;
	
	
};

#include "List.hpp"

#endif /* LIST_H */