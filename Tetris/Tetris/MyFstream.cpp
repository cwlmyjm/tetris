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

// MyFstream的readN需要特化实现，未实现的无法调用，会编译不通过的。

#define REPEAT2(str) str str
#define REPEAT4(str) REPEAT2(str) REPEAT2(str)
#define REPEAT8(str) REPEAT4(str) REPEAT4(str)

template<>
void MyFstream::readN<2>(char* char_var1, int* int_var1, int* int_var2)
{
	fscanf(file, REPEAT2("%c\n%d\n%d\n"),
		char_var1, int_var1, int_var2,
		char_var1 + 1, int_var1 + 1, int_var2 + 1);
}

template<>
void MyFstream::readN<4>(char* char_var1, int* int_var1, int* int_var2)
{
	fscanf(file, REPEAT4("%c\n%d\n%d\n"),
		char_var1, int_var1, int_var2,
		char_var1 + 1, int_var1 + 1, int_var2 + 1,
		char_var1 + 2, int_var1 + 2, int_var2 + 2,
		char_var1 + 3, int_var1 + 3, int_var2 + 3);
}

template<>
void MyFstream::readN<8>(char* char_var1, int* int_var1, int* int_var2)
{
	fscanf(file, REPEAT8("%c\n%d\n%d\n"),
		char_var1, int_var1, int_var2,
		char_var1 + 1, int_var1 + 1, int_var2 + 1,
		char_var1 + 2, int_var1 + 2, int_var2 + 2, 
		char_var1 + 3, int_var1 + 3, int_var2 + 3,
		char_var1 + 4, int_var1 + 4, int_var2 + 4,
		char_var1 + 5, int_var1 + 5, int_var2 + 5,
		char_var1 + 6, int_var1 + 6, int_var2 + 6,
		char_var1 + 7, int_var1 + 7, int_var2 + 7);
}
