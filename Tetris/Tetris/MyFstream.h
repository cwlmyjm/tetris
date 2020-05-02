#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>

class MyFstream
{
public:
	MyFstream(const std::string& path, const std::string& mode);
	~MyFstream();

	bool is_open();
	void close();
	MyFstream& operator>>(int& int_var);
	MyFstream& operator>>(char& char_var);

	void read(int& int_var1, int& int_var2);
	void read(char& char_var1, int& int_var1, int& int_var2);

private:
	FILE* file = NULL;
};

