#pragma once
#include <fstream>
#include <string>

class StdFstream
	: public std::fstream
{
public:
	StdFstream(const std::string& path, std::fstream::openmode mode);
	~StdFstream();

	bool is_open();
	void close();
	StdFstream& operator>>(int& int_var);
	StdFstream& operator>>(char& char_var);

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

	StdFstream& operator<<(std::ostream& (__cdecl* fun)(std::ostream&));

	template<typename T>
	StdFstream& operator<<(T& var)
	{
		file << var;
		return *this;
	};

private:
	std::fstream file;
};

