#include "MyFstream.h"
#include <iostream>

MyFstream::MyFstream(const std::string& path, const std::string& mode)
{
	//std::cout << "MyFstream::MyFstream" << std::endl;
	file = fopen(path.c_str(), mode.c_str());
}

MyFstream::~MyFstream()
{
	//std::cout << "MyFstream::~MyFstream" << std::endl;
	if (file != NULL)
	{
		close();
	}
}

bool MyFstream::is_open()
{
	return file != NULL;
}

void MyFstream::close()
{
	if (file != NULL)
	{
		fclose(file);
		file = NULL;
	}
}

MyFstream& MyFstream::operator>>(int& int_var)
{
	fscanf(file, "%d\n", &int_var);
	return *this;
}

MyFstream& MyFstream::operator>>(char& char_var)
{
	fscanf(file, "%c\n", &char_var);
	return *this;
}

void MyFstream::read(int& int_var1, int& int_var2)
{
	fscanf(file, "%d\n%d\n", &int_var1, &int_var2);
}

void MyFstream::read(char& char_var1, int& int_var1, int& int_var2)
{
	fscanf(file, "%c\n%d\n%d\n", &char_var1, &int_var1, &int_var2);
}
