#include "list.h"
#include "attribute.h"
#include "section.h"

template<typename T>
list<T>::list() : head(nullptr), tail(nullptr), block_size(BLOCK_SIZE), size(0), node_count(0) {};


template<typename T>
list<T>::~list()
{
	this->Clear();
}

template<typename T>
void list<T>::Clear()
{
	if (head != nullptr)
	{
		node<T>* curr = this->head;
		while (curr != nullptr)
		{
			node<T>* temp = curr->next;
			delete[] curr->data;
			delete curr;
			curr = temp;
		}
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
}


template<typename T>
void list<T>::AddBack(T* value)
{
	// If there are no empty blocks, add new block
	if (node_count * block_size == this->size)
	{
		AddBackEmptyBlock();
	}

	node<T>* curr = tail;

	// Find the first empty index array cell
	while (curr->size == this->block_size && curr->prev != nullptr)
	{
		curr = curr->prev;
	}

	int curr_index = 0;

	// Find the first empty index array cell
	while (curr_index < block_size && curr->index_array[curr_index] != EMPTY_SPACE)
	{
		curr_index++;
	}

	// Set the value and the index table
	curr->data[curr_index] = *value;
	this->size++;
	if(curr->size == curr->actual_size)
		curr->actual_size++;
	curr->size++;
	
	curr->index_array[curr_index] = this->size - 1;

}

template<typename T>
void list<T>::AddBackEmptyBlock()
{
	if (head == nullptr)
	{
		head = new node<T>();
		head->data = new T[block_size];

		// Marking index array as empty space by setting value to 65535
		for (size_t i = 0; i < block_size; i++)
		{
			head->index_array[i] = EMPTY_SPACE;
		}

		head->size = 0;
		//head->index_array[0] = 0;
		this->size = 0;
		this->node_count = 1;
		tail = head;
	}
	else
	{
		node<T>* curr = tail;
		node<T>* new_block = new node<T>();

		// Marking index array as empty space by setting value to 65535
		for (size_t i = 0; i < block_size; i++)
			new_block->index_array[i] = EMPTY_SPACE;

		new_block->data = new T[block_size];
		new_block->size = 0;
		new_block->prev = curr;
		curr->next = new_block;
		this->node_count++;
		tail = curr->next;
	}
}

template<typename T>
void list<T>::DeleteNode(node<T>* curr)
{
	if (curr->prev != nullptr)
	{
		curr->prev->next = curr->next;
	}

	if (curr->next != nullptr)
	{
		curr->next->prev = curr->prev;
	}

	if (curr == head)
	{
		head = curr->next;
	}

	if (tail == curr)
	{
		tail = curr->prev;
	}

	delete[]curr->data;
	delete curr;
	
}

template<typename T>
node<T>* list<T>::FindIndex(int _index)
{
	// Safety check
	if (_index < 0 || _index >= size)
	{
		throw std::out_of_range("No index like this");
	}

	node<T>* curr;
	int curr_block_index = 0;

	if (_index < this->size / 2)
	{
		curr = head;

		// Searching for the index in the index array
		// 
		// Assuming index is exsisting due to the mechanics of this->size
		while (curr->index_array[curr_block_index] != _index)
		{
			curr_block_index++;

			// End of block
			if (curr_block_index >= block_size)
			{
				curr = curr->next;
				curr_block_index = 0;
			}
		}
	}
	else
	{
		curr = tail;
		// Searching for the index in the index array
		// 
		// Assuming index is exsisting due to the mechanics of this->size
		while (curr->index_array[curr_block_index] != _index)
		{
			curr_block_index++;

			// End of block
			if (curr_block_index >= block_size)
			{
				curr = curr->prev;
				curr_block_index = 0;
			}
		}
	}

	return curr;
}

template<typename T>
node<T>* list<T>::FindIndexToDelete(int _index)
{
	if (_index < 0 || _index >= size)
	{
		throw std::out_of_range("No index like this");
	}

	node<T>* curr;
	node<T>* result;
	int curr_block_index = 0;

	if (_index < this->size / 2)
	{
		curr = head;

		// Searching for the index in the index array
		// 
		// Assuming index is exsisting due to the mechanics of this->size
		while (curr->index_array[curr_block_index] != _index)
		{
			// Filling the missing space
			if (curr->index_array[curr_block_index] > _index && curr->index_array[curr_block_index] != EMPTY_SPACE)
			{
				curr->index_array[curr_block_index]--;
			}

			curr_block_index++;

			// End of block
			if (curr_block_index >= block_size)
			{
				curr = curr->next;
				curr_block_index = 0;
			}
		}

		result = curr;

		// Continuation of filling the missing space
		// Not doing a full sweep again, due to the time complexity improvement
		while (curr_block_index < block_size || curr->next != nullptr)
		{
			// Filling the missing space
			if (curr->index_array[curr_block_index] > _index && curr->index_array[curr_block_index] != EMPTY_SPACE)
			{
				curr->index_array[curr_block_index]--;
			}

			curr_block_index++;

			// End of block
			if (curr_block_index >= block_size && curr->next != nullptr)
			{
				curr = curr->next;
				curr_block_index = 0;
			}
		}
	}
	else
	{
		curr = tail;
		// Searching for the index in the index array
		// 
		// Assuming index is exsisting due to the mechanics of this->size
		while (curr->index_array[curr_block_index] != _index)
		{
			// Filling the missing space
			if (curr->index_array[curr_block_index] > _index && curr->index_array[curr_block_index] != EMPTY_SPACE)
			{
				curr->index_array[curr_block_index]--;
			}

			curr_block_index++;

			// End of block
			if (curr_block_index >= block_size)
			{
				curr = curr->prev;
				curr_block_index = 0;
			}
		}

		result = curr;

		// Continuation of filling the missing space
		// Not doing a full sweep again, due to the time complexity improvement
		while (curr_block_index < block_size || curr->prev != nullptr)
		{
			// Filling the missing space
			if (curr->index_array[curr_block_index] > _index && curr->index_array[curr_block_index] != EMPTY_SPACE)
			{
				curr->index_array[curr_block_index]--;
			}

			curr_block_index++;

			// End of block
			if (curr_block_index >= block_size && curr->prev != nullptr)
			{
				curr = curr->prev;
				curr_block_index = 0;
			}
		}
	}

	return result;
}

template<typename T>
void list<T>::DeleteI(int _index)
{
	if (_index < 0 || _index >= size)
	{
		throw std::out_of_range("No index like this");
	}

	node<T>* curr = FindIndexToDelete(_index);

	int curr_block_index = 0;
	while (curr->index_array[curr_block_index] != _index)
	{
		curr_block_index++;
	}

	curr->index_array[curr_block_index] = EMPTY_SPACE;
	//curr->data[curr_block_index] = nullptr;
	curr->size--;
	this->size--;

	// Deleting empty node
	if (curr->size == 0)
	{
		DeleteNode(curr);
		node_count--;
	}

}

template<typename T>
void list<T>::EditI(int _index, T* value)
{
	if (_index < 0 || _index >= size)
	{
		throw std::out_of_range("No index like this");
	}

	node<T>* curr = FindIndex(_index);
	int curr_block_index = 0;
	while (curr->index_array[curr_block_index] != _index)
	{
		curr_block_index++;
	}

	curr->data[curr_block_index] = *value;
}

template<typename T>
void list<T>::SetSizeToZero()
{
	size = 0;
};

template<typename T>
int list<T>::Size()
{
	return size;
}

// Operators

template<typename T>
list<T>& list<T>::operator=(const list<T>& right)
{
	if (this != &right)
	{
		// Clearing left list
		while (head != nullptr)
		{
			node<T>* temp = head;
			head = head->next;
			delete[] temp->data;
			delete temp;
		}

		node<T>* curr_right = right.head;

		if (curr_right != nullptr)
		{
			this->AddBackEmptyBlock();
			node<T>* curr_left = head;

			while (curr_right != nullptr)
			{
				for (size_t i = 0; i < block_size; i++)
				{
					curr_left->index_array[i] = curr_right->index_array[i];

					if (curr_right->index_array[i] != EMPTY_SPACE)
						curr_left->data[i] = curr_right->data[i];
				}

				curr_left->size = curr_right->size;
				curr_left->actual_size = curr_right->actual_size;

				curr_right = curr_right->next;

				if (curr_right != nullptr)
				{
					this->AddBackEmptyBlock();
					curr_left = curr_left->next;
				}
			}

			tail = curr_left;
			size = right.size;
			
		}
	}

	return *this;
}

template<typename T>
bool list<T>::operator!=(list<T>& right)
{
	if (this->size != right.size)
		return true;

	node<T>* left_curr = this->head;
	node<T>* right_curr = right.head;

	// Assuming left_curr and right_curr to be equal in size
	// based on the if statement above 
	while (left_curr != nullptr)
	{
		for (int i = 0; i < block_size; i++)
		{
			if (left_curr->index_array[i] != right_curr->index_array[i])
				return true;
			else
				if (left_curr->data[i] != right_curr->data[i])
					return true;
		}

		left_curr = left_curr->next;
		right_curr = right_curr->next;
	}

	return false;
}

template<typename T>
bool list<T>::operator==(list<T>& right)
{
	if (this->size != right.size)
		return false;

	node<T>* left_curr = this->head;
	node<T>* right_curr = right.head;

	// Assuming left_curr and right_curr to be equal in size
	// based on the if statement above
	while (left_curr != nullptr)
	{
		for (int i = 0; i < left_curr->size; i++)
		{
			if (left_curr->data[i] != right_curr->data[i])
				return false;
		}

		left_curr = left_curr->next;
		right_curr = right_curr->next;
	}

	return true;
}

template<typename T>
T& list<T>::operator[](int _index)
{
	if (_index < 0 || _index >= size)
	{
		throw std::out_of_range("No index like this");
	}

	node<T>* curr = FindIndex(_index);
	int curr_block_index = 0;

	while (curr->index_array[curr_block_index] != _index)
	{
		curr_block_index++;
	}


	return curr->data[curr_block_index];
}

template<typename T>
void list<T>::CounterHead()
{
	counter = head;
}

template class list<mstring>;
template class list<section>;
template class list<attribute>;