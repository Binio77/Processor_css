#include "attribute.h"

attribute::attribute() : name(), value() {};

std::ostream& operator<<(std::ostream& output, const attribute& _attribute)
{
	output << _attribute.name << ' ' << _attribute.value;
	return output;
}

bool attribute::operator==(attribute& right)
{
	if (name == right.name && value == right.value)
		return true;
	else
		return false;
}

bool attribute::operator!=(attribute& right)
{
	if (name != right.name || value != right.value)
		return true;
	else
		return false;
}

mstring attribute::Name()
{
	return name;
}

mstring attribute::Value()
{
	return value;
}

void attribute::SetName(mstring* _name)
{
	name = *_name;
}

void attribute::SetValue(mstring* _value)
{
	value = *_value;
}

attribute& attribute::operator=(const attribute& right)
{
	name = right.name;
	value = right.value;
	return *this;
}

bool attribute::SameAttribute(attribute* source)
{
	if (name == source->name)
		return true;
	else
		return false;
}

bool attribute::Empty()
{
	if (name.Empty())
		return true;
	else
		return false;
}

void attribute::Clear()
{

	name.Clear();
	value.Clear();

}

bool attribute::operator==(mstring& right)
{
	if (name == right)
		return true;
	else
		return false;
}