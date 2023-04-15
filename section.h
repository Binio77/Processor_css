#pragma once
#include"attribute.h"
class section
{
public:
	list<attribute>attributes;
	list<mstring>selectors;
	section();
	~section();
	section& operator=(const section& right);
	int FindAttribute(attribute* search);
	attribute FindAttribute(mstring search);
	int  FindIndex(mstring search);
	bool FindSelector(mstring search);
	mstring FindSelector(int index);
	bool Empty();
	bool operator==(section& right);
	bool operator!=(section& right);


};

