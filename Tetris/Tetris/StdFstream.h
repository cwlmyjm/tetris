#pragma once
#include <fstream>
#include <string>

class StdFstream
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

private:
	std::fstream file;
};

