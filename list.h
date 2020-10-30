#pragma once
#include <stddef.h>

//this is the one I decided to move to for no reason other than i hated using a linked list
//and also I suppose it's significantly cleaner and a lot faster
//now that I think about it this implementation is just overall better in every way

typedef struct
{
	unsigned int length;
	unsigned int allocated_length;
	void** data;
} list;

void insert_back(list* list, void* item, size_t datasize);
void free_list(list* list);
void init_list(list* list);