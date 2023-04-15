#pragma once
#include "list.h"
class attribute
{
private:

	friend std::ostream& operator<<(std::ostream& output, const attribute& _attribute);

public:
	mstring name;
	mstring value;
	attribute();
	~attribute() {};
	mstring Name();
	mstring Value();
	void SetName(mstring* _name);
	void SetValue(mstring* _value);
	attribute& operator=(const attribute& right);
	bool SameAttribute(attribute* source);
	bool operator==(attribute& right);
	bool operator!=(attribute& right);
	bool operator==(mstring& right);
	bool Empty();
	void Clear();
};

