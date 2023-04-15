#pragma once
#include "mstring.h"

// Max block size 65534 due to usage of unsigned short int in node
// Number 65535 reserved as an empty space indicator
#define EMPTY_SPACE 65535
#define BLOCK_SIZE 8

template<typename T>
struct node
{
	T* data;
	node* next;
	node* prev;
	int size, actual_size;
	unsigned short int index_array[BLOCK_SIZE];

	node() : next(nullptr), prev(nullptr), data(nullptr), size(0), actual_size(0) {};
	~node()
	{
	}
};

template<typename T>
class list
{
private:
	node<T>* head;
	node<T>* tail;
	int block_size, size, node_count;
	void DeleteNode(node<T>* _node);
	node<T>* FindIndex(int _index);
	node<T>* FindIndexToDelete(int _index);
public:
	node<T> *counter;
	list();
	~list();
	void CounterHead();
	void AddBack(T* value);
	void AddBackEmptyBlock();
	void DeleteI(int index);
	void EditI(int index, T* value);
	void SetSizeToZero();
	int Size();
	void Clear();

	T& operator[](int index);
	list& operator=(const list& right);
	bool operator!=(list& right);
	bool operator==(list& right);
	
};