#include "MyMemory.h"
#include <stdio.h>
#include <stdlib.h>

void* operator new(size_t sz)
{
	void* ptr = malloc(sz);
	if (!ptr)
		return nullptr;
	return ptr;
}

void operator delete(void* ptr)
{
	free(ptr);
}
