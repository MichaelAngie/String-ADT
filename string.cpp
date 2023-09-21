#include "string.h"
#include <iostream>  
#include <vector>                   

//rules of usage
//construction of strings must be done via the operations
//can not acces past the null terminator str[0,1,2,...,length()-1]
//0 <= length() <= capacity()


//default constructor
String::String()
{
    stringSize = 1;
    str = new char[1];
    str[0] = 0;
}


//char constructor
String::String(char ch)
{
    if (ch == 0)
    {
        stringSize = 1;
        str = new char[stringSize];
        str[0] = ch;
    }
    else
    {
        stringSize = 2;
        str = new char[stringSize];
        str[0] = ch;
        str[1] = 0;
    }

}

//char array constructor
String::String(const char toString[])
{
    int size = 0;
    while (toString[size] != 0)
    {
        size++;
    }

    stringSize = size + 1;
    str = new char[stringSize];

    for (int i = 0; i < size; ++i)
    {
        str[i] = toString[i];
    }

    str[size] = 0;

}

//copy constructor
String::String(const String& actual)
{
    stringSize = actual.stringSize;
    str = new char[stringSize];
    for (int i = 0; i < stringSize; ++i)
    {
        str[i] = actual.str[i];
    }
}

//destructor
String::~String()
{
    delete[] str;
}

//Constant time swap
void String::swap(String& rhs)
{
    int tempSize = rhs.stringSize;
    rhs.stringSize = stringSize;
    stringSize = tempSize;

    char* temp = rhs.str;
    rhs.str = str;
    str = temp;
    //do i delete the temp poiinter?

}

//assignment operator
String& String::operator=(String rhs)
{
    if (str == rhs.str) return *this;
    delete[] str;

    stringSize = rhs.stringSize;
    str = new char[stringSize];
    for (int i = 0; i < stringSize; ++i)
    {
        str[i] = rhs.str[i];
    }

    return *this;
}


int String::capacity() const
{
    return stringSize - 1;
}


int String::length() const
{
    int size = 0;
    while (str[size] != 0)
    {
        size++;
    }
    return size;
}

char& String::operator[](int i)
{
    if (i >= 0 && i < length())
    {
        return str[i];
    }
    return str[length()];                   //can i use assert in this assignment?
    std::cerr << "Out of bounds error.\n";
}

char String::operator[](int i) const
{
    if (i >= 0 && i < length())
    {
        return str[i];
    }
    return 0;                               //can i use assert in this assignment?
    std::cerr << "Out of bounds error.\n";
}

String& String::operator+=(const String& rhs)
{
    int lhsLength = length();
    int rhsLength = rhs.length();
    int newLength = lhsLength + rhsLength;
    stringSize = newLength + 1;

    char* temp = new char[stringSize];

    int j = 0;
    for (int i = 0; i < lhsLength; ++i)
    {
        temp[j] = str[j];
        ++j;
    }
    for (int i = 0; i < rhsLength; ++i)
    {
        temp[j] = rhs.str[i];
        ++j;
    }

    temp[stringSize - 1] = 0;
    delete[] str;
    str = temp;

    return *this;
}

bool String::operator==(const String& rhs) const
{
    int i = 0;
    while ((str[i] != 0) && (str[i] == rhs.str[i])) ++i;
    return str[i] == rhs.str[i];
}

bool String::operator<(const String& rhs) const
{
    int i = 0;
    while ((str[i] != 0) && (str[i] == rhs.str[i])) ++i;
    return str[i] < rhs.str[i];
}

String String::substr(int start, int end) const
{
    if (start < 0) start = 0;
    if (start >= length()) return String();
    if (end < start) return String();

    //std::cout << "In substr() the argument are: \nStart: " << start << "\nEnd: " << end << std::endl;
    //std::cout << "In substr() the result pointer points to a new array of size [" << (end - start) << "] + 2" << std::endl;
    String result;
    delete[] result.str;
    result.str = new char[end - start + 2];

    for (int i = start; i <= end; ++i)
    {
        result.str[i - start] = str[i];
    }
    //std::cout << "In substr() the temp char array computed to: " << temp << "\nIt will now be sent to String constructor." << std::endl;
    result.str[end - start + 1] = 0;
    //std::cout << "In substr() the result is: " << result << std::endl;
    return result;
}

int String::findch(int start, char findMe) const
{
    int i = start;
    if ((start < 0) || (start >= length())) return -1;

    while (str[i] != 0)
    {
        if (str[i] == findMe) return i;
        ++i;
    }
    return -1;
}

int String::findstr(int start, const String& findMe) const
{
    int i = start;
    if ((start < 0) || (start >= length())) return -1;

    while (str[i] != 0)
    {
        //std::cout << "In findstr(): " << substr(i, i + findMe.length() - 1) << std::endl;
        if (substr(i, i + findMe.length() - 1) == findMe) return i;
        //std::cout <<  "It does not equal " << findMe << std::endl;
        ++i;
    }
    //std::cout << "findstr() reached null array element and ended, returning -1" << std::endl;
    return -1;
}

std::vector<String> String::split(char ch) const
{
    std::vector<String> result;
    int thisLength = length();
    int foundChar;
    int spot = 0;

    while (findch(spot, ch) != -1)
    {
        foundChar = findch(spot, ch);
        result.push_back(substr(spot, foundChar));
        spot = foundChar;
    }
    return result;

}



//Friends

std::istream& operator>>(std::istream& input, String& rhs)
{
    char temp[1024];
    input >> temp;
    rhs = String(temp);
    return input;
}

std::ostream& operator<<(std::ostream& output, const String& rhs)
{
    output << rhs.str;
    return output;
}


//Free Functions

String operator+(String lhs, const String& rhs)
{
    return lhs += rhs;
    /*
    String result(lhs);
    int offset = result.length();
    int i = 0;
    while (rhs[i] != 0)
    {
        if (offset + i >= result.capacity()) break;
        result[offset + i] = rhs[i];
        ++i;
    }
    result[offset + i] = 0;
    return result;
    */
}

bool operator==(const char lhs[], const String& rhs)
{
    return String(lhs) == rhs;
}

bool operator==(char lhs, const String& rhs)
{
    return String(lhs) == rhs;
}

bool operator<(const char lhs[], const String& rhs)
{
    return String(lhs) < rhs;
}

bool operator<(char lhs, const String& rhs)
{
    return String(lhs) < rhs;
}

bool operator<=(const String& lhs, const String& rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs);
}

bool operator>=(const String& lhs, const String& rhs)
{
    return !(lhs < rhs);
}

bool operator>(const String& lhs, const String& rhs)
{
    return rhs < lhs;
}
