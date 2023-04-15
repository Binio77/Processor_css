#include "css.h"

css::css() : sections(), inside_section(false), command_section(false) {};

void css::Input()
{
    char input_char = 0;
    bool selector_part = true;
    bool edited_attribute = false;
    mstring str, first, third;
    int count = 0;
    char second;
    section* new_section = new section();
    attribute* new_attribute = new attribute();
    do
    {
        input_char = getchar();

        if (!command_section)
        {
            if (input_char == ',' && selector_part)
            {
                while (str[str.Size() - 1] <= ' ')
                    str.PopBack();

                new_section->selectors.AddBack(&str);

                str.Clear();
            }
            else if (input_char == '{' && str.Size() > 0 && selector_part)
            {
                while (str[str.Size() - 1] <= ' ')
                    str.PopBack();

                new_section->selectors.AddBack(&str);
                selector_part = false;
                str.Clear();
            }
            else if (input_char == ':' && !selector_part)
            {
                    
                new_attribute->SetName(&str);
                str.Clear();
            }
            else if (input_char == ';' && !selector_part)
            {
                while (str[str.Size() - 1] <= ' ')
                    str.PopBack();
                new_attribute->SetValue(&str);

                for (int i = 0; i < new_section->attributes.Size(); i++)
                {
                    if (new_section->attributes[i].name == new_attribute->name)
                    {
                        new_section->attributes[i] = *new_attribute;
                        edited_attribute = true;
                    }
                }

                if (!edited_attribute)
                {
                    new_section->attributes.AddBack(new_attribute);
                }

                edited_attribute = false;

                str.Clear();
            }
            else if (input_char == '}' && !selector_part)
            {
                if (str.Size() > 0)
                {
                    while (str[str.Size() - 1] <= ' ')
                        str.PopBack();

                    new_attribute->SetValue(&str);
                    for (int i = 0; i < new_section->attributes.Size(); i++)
                    {
                        if (new_section->attributes[i].SameAttribute(new_attribute))
                        {
                            new_section->attributes[i] = *new_attribute;
                            edited_attribute = true;
                        }
                    }
                    if (!edited_attribute)
                        new_section->attributes.AddBack(new_attribute);

                    str.Clear();
                }

                selector_part = true;
                edited_attribute = false;

                if (new_section->attributes.Size() != 0)
                    sections.AddBack(new_section);
                
                new_section->selectors.Clear();
                new_section->attributes.Clear();
                delete new_section;
                new_section = nullptr;

                new_section = new section();

            }
            else
            {
                if (input_char != '\n' && input_char != '\t' && input_char != '{' && input_char != '}')
                    str.PushBack(input_char);

                if (input_char == '{')
                    selector_part = false;

                if (str[0] <= ' ')
                    str.Clear();

                if (str == "????")
                {
                    command_section = true;
                    str.Clear();
                }
            }
        }
        else
        {
            if (str == "****")
            {
                str.Clear();
                command_section = false;
            }
            else if (input_char == ',')
            {
                if (count == 0)
                {
                    first = str;
                    count++;
                    str.Clear();
                }
                else if (count == 1)
                {
                    second = str[0];
                    str.Clear();
                    count++;
                }
            }
            else if (input_char == '\n' && str.Size() > 0 || input_char == EOF && str.Size() > 0)
            {
                if (count == 0 && str[0] == '?')
                {
                    std::cout << "? == " << sections.Size() << std::endl;
                }
                else if(!first.Empty())
                {
                    third = str;
                    CommandInterpreter(first, second, third);
                    first.Clear();
                }
                str.Clear();
                count = 0;
            }
            else
            {
                if (input_char != '\n' && input_char != ',')
                    str.PushBack(input_char);
            }
        }


    } while (input_char != EOF);
    

}


void css::CommandInterpreter(mstring first, char second, mstring third)
{
    int count = 0;

    switch (second)
    {
    case 'S':
    {
        if (first[0] >= '1' && first[0] <= '9' && third[0] == '?')
        {
            int section_index = first.s_to_int() - 1;
            if (section_index < sections.Size())
                std::cout << first << ',' << second << ',' << third << " == " << sections[section_index].selectors.Size() << std::endl;

        }
        else if (first[0] >= '1' && first[0] <= '9')
        {
            int section_index = first.s_to_int() - 1;
            if (section_index < sections.Size())
            {
                int selector_index = third.s_to_int() - 1;
                if (sections[section_index].selectors.Size() > selector_index)
                    std::cout << first << ',' << second << ',' << third << " == " << sections[section_index].selectors[selector_index] << std::endl;
            }
        }
        else
        {
            sections.CounterHead();
            while (sections.counter != nullptr)
            {
                for (int i = 0; i < sections.counter->actual_size; i++)
                {
                    if (sections.counter->index_array[i] != EMPTY_SPACE)
                    {
                        for (int j = 0; j < sections.counter->data[i].selectors.Size(); j++)
                        {
                            if (sections.counter->data[i].selectors[j] == first)
                            {
                                count++;
                                break;
                            }
                        }
                    }
                }
                
                sections.counter = sections.counter->next;
            }

            std::cout << first << ',' << second << ',' << third << " == " << count << std::endl;
            count = 0;
        }
        break;
    }
    case 'A':
    {

        if (first[0] >= '1' && first[0] <= '9' && third[0] == '?')
        {
            int section_index = first.s_to_int() - 1;
            if (section_index < sections.Size())
                std::cout << first << ',' << second << ',' << third << " == " << sections[section_index].attributes.Size() << std::endl;

        }
        else if (first[0] >= '1' && first[0] <= '9')
        {
            int section_index = first.s_to_int() - 1;
            if (section_index < sections.Size())
            {
                attribute* attr = new attribute();
                *attr = sections[section_index].FindAttribute(third);

                if (!attr->Empty())
                    std::cout << first << ',' << second << ',' << third << " == " << attr->Value() << std::endl;

                count = 0;
            }
        }
        else
        {
            sections.CounterHead();
            while (sections.counter != nullptr)
            {
                for (int i = 0; i < sections.counter->actual_size; i++)
                {
                    if (sections.counter->index_array[i] != EMPTY_SPACE)
                    {
                        for (int j = 0; j < sections.counter->data[i].attributes.Size(); j++)
                        {
                            if (sections.counter->data[i].attributes[j].name == first)
                            {
                                count++;
                                break;
                            }
                        }
                    }
                }

                sections.counter = sections.counter->next;
            }

            std::cout << first << ',' << second << ',' << third << " == " << count << std::endl;
            count = 0;
        }
        break;
    }
    case 'D':
    {
        if (third[0] == '*')
        {
            int section_index = first.s_to_int() - 1;

            if (section_index < sections.Size())
            {
                sections.DeleteI(section_index);
                std::cout << first << ',' << second << ',' << third << " == deleted" << std::endl;
            }
        }
        else
        {
            int section_index = first.s_to_int() - 1;
            if (section_index < sections.Size())
            {
                count = sections[section_index].FindIndex(third);

                if (count >= 0)
                {
                    sections[section_index].attributes.DeleteI(count);
                    std::cout << first << ',' << second << ',' << third << " == deleted" << std::endl;

                    if (sections[section_index].attributes.Size() == 0)
                    {
                        sections.DeleteI(section_index);
                    }
                }
            }


        }
        break;
    }
    case 'E':
    {
        count = -1;
        for (int i = sections.Size() - 1; i >= 0; i--)
        {
            if (sections[i].FindSelector(first))
            {
                count = i;
                break;
            }
        }

        if (count != -1)
        {
            attribute* attr = new attribute();
            *attr = sections[count].FindAttribute(third);

            if (!attr->Empty())
                std::cout << first << ',' << second << ',' << third << " == " << attr->Value() << std::endl;
        }

        break;
    }
    }
}
