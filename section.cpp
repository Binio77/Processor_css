#include "section.h"

section::section() : attributes(), selectors() {};

section::~section()
{
	selectors.Clear();
	attributes.Clear();
}

bool section::operator!=(section& right)
{
	if (attributes != right.attributes)
		return true;
	if (selectors != right.selectors)
		return true;

	return false;
}

bool section::operator==(section& right)
{
	if (attributes != right.attributes)
		return false;
	if (selectors != right.selectors)
		return false;

	return true;

}

int section::FindAttribute(attribute* search)
{
	for (int i = 0; i < attributes.Size(); i++)
	{
		if (attributes[i].SameAttribute(search))
			return i;
	}
	return -1;
}

attribute section::FindAttribute(mstring search)
{
	for (int i = 0; i < attributes.Size(); i++)
	{
		if (attributes[i].Name() == search)
			return attributes[i];
	}
	attribute empty_attribute;
	return empty_attribute;
}

int section::FindIndex(mstring search)
{
	for (int i = 0; i < attributes.Size(); i++)
	{
		if (attributes[i].Name() == search)
			return i;
	}
	return -1;
}

bool section::FindSelector(mstring search)
{
	for (int i = selectors.Size() - 1; i >= 0; i--)
	{
		if (selectors[i] == search)
			return true;
	}
	return false;
}

mstring section::FindSelector(int index)
{
	if (index < selectors.Size())
		return selectors[index];
	else
		return "";
}

bool section::Empty()
{
	if (attributes.Size() <= 0 && selectors.Size() <= 0)
		return true;
	else
		return false;
}


section& section::operator=(const section& right)
{
	attributes = right.attributes;
	selectors = right.selectors;
	return *this;
}




