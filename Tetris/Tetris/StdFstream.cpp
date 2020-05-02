#include "StdFstream.h"

StdFstream::StdFstream(const std::string& path, std::fstream::openmode mode)
	: file(path, mode)
{

}

StdFstream::~StdFstream()
{
	close();
}

bool StdFstream::is_open()
{
	return file.is_open();
}

void StdFstream::close()
{
	if (file.is_open())
	{
		file.close();
	}
}

StdFstream& StdFstream::operator>>(int& int_var)
{
	file >> int_var;
	return *this;
}

StdFstream& StdFstream::operator>>(char& char_var)
{
	file >> char_var;
	return *this;
}

void StdFstream::read(int& int_var1, int& int_var2)
{
	file >> int_var1 >> int_var2;
}

void StdFstream::read(char& char_var1, int& int_var1, int& int_var2)
{
	file >> char_var1 >> int_var1 >> int_var2;
}
