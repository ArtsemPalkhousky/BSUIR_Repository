#pragma once
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

class String
{
	char* str;
	int length;

public:

	friend ostream& operator<<(ostream& out, const String& string);
	friend istream& operator>>(istream& in, String& string);

	String();
	String(int);
	String(const String& source);
	String(const char* source);
	~String();

	String& operator=(const String&);
	String& operator=(const char*);

	String operator+(const String&);
	String operator+(const char*);
	String operator+(const char);
	friend String operator+(const char*, const String&);

	friend String operator+(char _char, const String& str1)
	{
		String NewString(str1.length + 1);
		int i = 0;
		NewString.str[i] = _char;
		for (int j = 0, i = 1; i < NewString.length; i++, j++)
			NewString.str[i] = str1.str[j];
		NewString.str[NewString.length] = '\0';
		return NewString;
	}

	String& operator+=(const String&);
	String& operator+=(const char*);
	String& operator+=(const char);

	bool operator==(const String&);
	bool operator==(const char*);
	friend bool operator==(const char*, String&);

	bool operator!=(const String&);
	bool operator!=(const char*);
	friend bool operator!=(const char*, String&);

	bool operator<(const String&);
	bool operator<(const char*);
	friend bool operator<(const char*, String&);

	bool operator>(const String&);
	bool operator>(const char*);
	friend bool operator>(const char*, String&);

	char& operator[](int);
	String operator()(int, int);
};

