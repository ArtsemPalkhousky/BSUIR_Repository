#include "StringObject.h"

String::String()
{
	length = 0;
	str = NULL;
}


String::String(int len) 
{
	length = len;
	str = new char[length + 1];
}

String::String(const char* source)
{
	length = strlen(source);
	str = new char[length + 1];
	strcpy_s(str, length + 1, source);
}


String::String(const String& source)
{
	length = source.length;
	str = new char[length + 1];
	strcpy_s(str, source.length + 1, source.str);
}

String::~String()
{
	delete[] str;
}

String& String::operator=(const String& secondString)
{
	if (str != 0)
		delete[] str;
	str = new char[secondString.length + 1];
	strcpy_s(str, secondString.length + 1, secondString.str);
	length = secondString.length;
	return *this;
}

String& String::operator=(const char* secondString)
{
	if (str != 0)
		delete[] str;
	str = new char[strlen(secondString) + 1];
	strcpy_s(str, strlen(secondString) + 1, secondString);
	length = strlen(secondString);
	return *this;
}

String String::operator+(const String& str2)
{
	String NewString;
	NewString.length = length + str2.length;
	NewString.str = new char[NewString.length + 1];
	int i = 0;
	for (; i < length; i++)
		NewString.str[i] = str[i];
	for (int j = 0; i < NewString.length; i++, j++)
		NewString.str[i] = str2.str[j];
	NewString.str[NewString.length] = '\0';
	return NewString;
}

String String::operator+(const char* str2)
{
	String NewString(length + strlen(str2));
	int i = 0;
	for (; i < length; i++)
		NewString.str[i] = str[i];
	for (int j = 0; i < NewString.length; i++, j++)
		NewString.str[i] = str2[j];
	NewString.str[NewString.length] = '\0';
	return NewString;
}

String String::operator+(const char str2)
{
	String NewString(length + 1);
	int i = 0;
	for (; i < length; i++)
		NewString.str[i] = str[i];
	NewString.str[i] = str2;
	i++;
	NewString.str[i] = '\0';
	return NewString;
}

String operator+(const char* str1, const String& str2)
{
	String NewString (strlen(str1) + str2.length);
	int i = 0;
	for (; i < strlen(str1); i++)
		NewString.str[i] = str1[i];
	for (int j = 0; i < NewString.length; i++, j++)
		NewString.str[i] = str2.str[j];
	NewString.str[NewString.length] = '\0';
	return NewString;
}


String& String::operator+=(const String& str)
{
	return *this = *this + str;;
}

String& String::operator+=(const char* str)
{
	return *this = *this + str;
}

String& String::operator+=(const char str)
{
	return *this = *this + str;
}

ostream& operator<<(ostream& out, const String& string)
{
	return out << string.str;
}

istream& operator>>(istream& is, String& string)
{
	char buffer[80];
	is.getline(buffer, sizeof buffer);
	string = buffer;
	string.length = strlen(buffer);
	return is;
}

char& String::operator[](int index)
{
	if (index < 0 || index >= (int)length)
		exit(EXIT_FAILURE);
	else
		return str[index];
}

String String::operator()(int position1, int position2)
{
	String subString(position2 - position1 + 2);
	int i = position1, j = 0;
	while (i <= position2) {
		subString.str[j] = str[i];
		i++;
		j++;
	}
	subString[j] = '\0';
	subString.length = strlen(subString.str);
	return subString;
}



bool String::operator==(const String& secondString)
{
	return strcmp(str, secondString.str) == 0;
}

bool String::operator==(const char* secondString)
{
	return strcmp(str, secondString) == 0;
}




bool String::operator!=(const String& secondString)
{
	return strcmp(str, secondString.str) != 0;
}

bool String::operator!=(const char* secondString)
{
	return strcmp(str, secondString) != 0;
}




bool String::operator<(const String& secondString)
{
	return length < secondString.length;
}

bool String::operator<(const char* secondString)
{
	return length < strlen(secondString);
}



bool String::operator>(const String& secondString)
{
	return length > secondString.length;
}

bool String::operator>(const char* secondString)
{
	return length > strlen(secondString);
}



bool operator==(const char* firstString, String& secondString)
{
	return strcmp(firstString, secondString.str) == 0;
}

bool operator!=(const char* firstString, String& secondString)
{
	return !(firstString == secondString);
}




bool operator<(const char* firstString, String& secondString)
{
	return strlen(firstString) < secondString.length;
}

bool operator>(const char* firstString, String& secondString)
{
	return !(firstString < secondString);
}
