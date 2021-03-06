#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <vector>

template <class T>
class List
{
	
public:
	List();
	~List();

	bool insert(T value);
	int erase(T value); //return number of erased elements 
	
	bool clean();
	bool empty();
	size_t getSize();
	
	class Iterator: public std::iterator<std::forward_iterator_tag, T>
	{
		friend class List;
	public:
		Iterator(Node<T>* n, List* l)
		:node(n), list(l){}
		
		T operator*()
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

	bool find(T value, std::vector<Iterator>& iterators)
	{
		bool result = false;
		Iterator i = begin();
		while(i!=end())
		{
			Iterator temp = i++;
			if(*temp == value)
			{
				result = true;
				iterators.push_back(temp);
			}
		}
		return result;
	}
	
	

private:
	Node<T>* headNode;
	Node<T>* endNode;
	size_t size;

};

#include "List.hpp"

#endif /* LIST_H */
