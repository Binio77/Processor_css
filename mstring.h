#pragma once
#include<iostream>
#pragma warning(disable : 4996)
class mstring
{
private:
	char* str;
	unsigned int length, size;
	friend std::ostream& operator<<(std::ostream& os, const mstring& str);
	friend std::istream& operator>>(std::istream& input, mstring& str);
public:
	mstring();
	mstring(size_t _size);
	mstring(const mstring& orig);
	mstring(const char* s);
	mstring& operator=(const mstring& right);
	int s_to_int();
	bool operator==(mstring& source);
	bool operator==(const char* source);
	bool operator!=(mstring& source);
	bool Empty();
	void Clear();
	void PushBack(char c);
	void PopBack();
	char& operator[](int i);
	int Size();
	~mstring();
};

