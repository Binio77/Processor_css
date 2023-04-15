#include "mstring.h"
#include<string.h>
#define ADDINGSIZE 10
mstring::mstring() : str(nullptr)
{
    length = ADDINGSIZE;
    str = new char[length];
    str[0] = '\0';

};

mstring::mstring(size_t size) : str{ new char[size + ADDINGSIZE] } {};

mstring::mstring(const mstring& orig)
{
    length = orig.length;
    str = new char[length];
    strcpy_s(str, strlen(orig.str) + 1, orig.str);
    str[strlen(orig.str)] = '\0';
}

mstring::mstring(const char* s)
{
    if (s == nullptr)
    {
        str = new char[ADDINGSIZE];
        str[0] = '\0';

    }
    else
    {
        length = strlen(s) + ADDINGSIZE;
        str = new char[length];
        strcpy_s(str, strlen(s) + 1, s);
        str[strlen(s)] = '\0';

    }

}

std::ostream& operator<<(std::ostream& os, const mstring& str)
{
    for (int i = 0; i < strlen(str.str); i++)
        std::cout << str.str[i];
    return os;
}

std::istream& operator>>(std::istream& input, mstring& str)
{
    char* buffer = new char[1000000];
    memset(&buffer[0], 0, sizeof(buffer));
    input >> buffer;
    str = mstring{ buffer
    };
    delete[] buffer;
    return input;
}

mstring& mstring::operator=(const mstring& right)
{
    if (this == &right)
        return *this;

    if (str != nullptr)
        delete[] str;

    length = right.length;
    str = new char[length];
    strcpy_s(str, strlen(right.str) + 1, right.str);
    return *this;
}

char& mstring::operator[](int i)
{
    if (i <= strlen(str) - 1)
    {
        return str[i];

    }
    else
        return str[0];
}

int mstring::Size()
{
    return strlen(str);
}

bool mstring::operator==(mstring& right)
{
    if (Size() != right.Size())
        return false;
    else
    {
        for (size_t i = 0; i < Size(); i++)
        {
            if (str[i] != right.str[i])
                return false;

        }
        return true;

    }
}

bool mstring::operator==(const char* source)
{
    if (strlen(str) != strlen(source))
        return false;
    for (int i = 0; i < Size(); i++)
    {
        if (str[i] != source[i])
            return false;

    }
    return true;
}

bool mstring::operator!=(mstring& right)
{
    if (Size() != right.Size())
        return true;
    else
    {
        for (size_t i = 0; i < Size(); i++)
        {
            if (str[i] != right.str[i])
                return true;

        }
        return false;

    }
}

bool mstring::Empty()
{
    if (Size() <= 0)
        return true;
    else
        return false;
}

void mstring::Clear()
{
    delete[] str;
    length = ADDINGSIZE;
    str = new char[length];
    str[0] = '\0';
}

void mstring::PushBack(char c)
{
    if (str != nullptr)
    {
        if (length > Size() + 1)
        {
            int temp_size = Size();
            str[temp_size] = c;
            str[temp_size + 1] = '\0';

        }
        else
        {
            length += Size();
            char* buffer = new char[length];
            for (int i = 0; i < Size(); i++)
                buffer[i] = str[i];

            int temp_size = Size();
            buffer[temp_size] = c;
            buffer[temp_size + 1] = '\0';
            *this = mstring(buffer);
            delete[] buffer;

        }

    }
    else
    {
        length = ADDINGSIZE;
        str = new char[length];

        str[0] = c;
        str[1] = '\0';

    }
}

void mstring::PopBack()
{
    char* buffer = new char[length];

    for (int i = 0; i < Size() - 1; i++)
    {
        buffer[i] = str[i];
    }

    buffer[Size() - 1] = '\0';
    *this = mstring(buffer);
    delete[] buffer;
}

int mstring::s_to_int()
{
    return atoi(str);
}

mstring::~mstring()
{
    if (str != nullptr)
        delete[] str;

    str = nullptr;
}