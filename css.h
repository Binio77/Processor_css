#pragma once
#include"section.h"
class css
{
private:
	list<section>sections;
	bool inside_section;
	bool command_section;

public:
	css();
	void Input();
	void CommandInterpreter(mstring first, char second, mstring third);
};

