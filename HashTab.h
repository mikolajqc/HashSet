#ifndef HASHTAB_H
#define HASHTAB_H

#include "List.h"
#include <vector>

template <class T>
class HashTab
{
	
public:
	HashTab(size_t K); // K - max number of ceils in vector
	~HashTab();
	
	bool init(size_t sizeToReserve); //czy init wogle jest konieczny? czy reserve tego nie
									 //zalatwia czy nie mozna tworzyc listy tylko gdy zajety?
	
	bool insert(T value, bool withResize = true);
	bool erase(T value);
	bool clean();
	bool empty();
	//dopisz find();
	
	size_t getSize(); //number of elements

	typename List<T>::Iterator operator[] (int index);
	
	//iterator w ogole w tym wypadku jest konieczny?
	class Iterator: public std::iterator<std::forward_iterator_tag, T>
	{
		friend class HashTab;
	public:
		Iterator();
		
		T operator*();
		
		Iterator& operator++();
		
		Iterator operator++(int);
		
		Iterator& operator--();
		
		Iterator operator--(int);
		
		bool operator==(const Iterator& a) const;
		
		bool operator!=(const Iterator& a) const;
	
	private:
		Node<T>* node;
		HashTab* hashTab;
	};
	
	Iterator begin();
	
	Iterator end();

	bool erase(Iterator i);

	bool find(T value, std::vector<Iterator>& iterators);
	
private:
	std::vector<List<T>* >* hashTable;
	size_t MAXNUMBEROFCEILS; // max number of ceils in vector
	//unsigned int numberOfCeils; // it is a size of vector so it isnt necessary
	unsigned int hashFunction(T value); // FNV-1a
	size_t size;
	
	size_t findNextPrime(size_t number);
	bool isPrime (size_t number);
	size_t findPreviousPrime(size_t number);
	
	bool resize(); // resizing when load factor is > 0.8 or if the load factor < 0.6
	float calculateLoadFactor();
};

#include "HashTab.hpp"

#endif /* HASHTAB_H */