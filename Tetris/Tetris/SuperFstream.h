#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>

class SuperFstream
{
public:
	SuperFstream(const std::string& path, const std::string& mode);
	~SuperFstream();

	bool is_open();
	void close();
	SuperFstream& operator>>(int& int_var);
	SuperFstream& operator>>(char& char_var);

	void read(int& int_var1, int& int_var2);
	void read(char& char_var1, int& int_var1, int& int_var2);

	template<int n>
	void readN(char* char_var1, int* int_var1, int* int_var2)
	{
		for (int i = 0; i < n; i++)
		{
			read(char_var1[i], int_var1[i], int_var2[i]);
		}
	}

private:
	bool is_blank(const char& c);

private:
	FILE* file = NULL;
	char* begin = nullptr;
	char* current = nullptr;

};

