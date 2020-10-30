#pragma once
#include <stddef.h>

//this is the one I decided to move to for no reason other than i hated using a linked list

typedef struct
{
	unsigned int length;
	unsigned int allocated_length;
	void** data;
} list;

void insert_back(list* list, void* item, size_t datasize);
void free_list(list* list);
void init_list(list* list);