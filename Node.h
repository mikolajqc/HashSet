

template <class T>
class Node
{

public:
	Node();
	Node(T initValue);
	Node(T initValue, Node* previousNode, Node* nextNode);
	~Node();

	T getValue();
	bool setValue(T value);

private:
	T value;
	Node* previousNode;
	Node* nextNode;
	bool isEnd; // is necessery?
};