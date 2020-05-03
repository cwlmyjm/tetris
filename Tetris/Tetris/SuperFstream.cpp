#include "SuperFstream.h"

SuperFstream::SuperFstream(const std::string& path, const std::string& mode)
{
	file = fopen(path.c_str(), mode.c_str());
	if (file)
	{
		fseek(file, 0, SEEK_END);
		long lsize = ftell(file);
		rewind(file);
		begin = (char*)malloc(lsize * sizeof(char) + 1);
		memset(begin, 0, lsize * sizeof(char) + 1);
		fread(begin, 1, lsize, file);
		current = begin;
	}
}

SuperFstream::~SuperFstream()
{
	if (file != NULL)
	{
		close();
	}
	if (begin)
	{
		free(begin);
	}
}

bool SuperFstream::is_open()
{
	return file != NULL;
}

void SuperFstream::close()
{
	if (file != NULL)
	{
		fclose(file);
		file = NULL;
	}
}

SuperFstream& SuperFstream::operator>>(int& int_var)
{
	int_var = 0;
	while (is_blank(*current))
	{
		current++;
	}

	while (!is_blank(*current))
	{
		int_var = int_var * 10 + (*current - '0');
		current++;
	}

	return *this;
}

SuperFstream& SuperFstream::operator>>(char& char_var)
{
	while (is_blank(*current))
	{
		current++;
	}

	char_var = *current;
	current++;

	return *this;
}

void SuperFstream::read(int& int_var1, int& int_var2)
{
	*this >> int_var1 >> int_var2;
}

void SuperFstream::read(char& char_var1, int& int_var1, int& int_var2)
{
	*this >> char_var1 >> int_var1 >> int_var2;
}

bool SuperFstream::is_blank(const char& c)
{
	return c == ' ' || c == '\r' || c == '\n' || c == '\0';
}
