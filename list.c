#include "list.h"
#include <stdlib.h>
#include <string.h>

void insert_back(list* list, void* item, size_t datasize)
{
	void* data = malloc(datasize);
	memcpy(data, item, datasize);

	if (list->length == list->allocated_length)
	{
		list->data = realloc(list->data, sizeof(void*) * list->allocated_length * 2);
		list->allocated_length *= 2;
	}

	list->data[list->length] = data;
	list->length++;
}

void free_list(list* list)
{
	for (unsigned int i = 0; i < list->length; i++)
		free(list->data[i]);
	free(list->data);
	init_list(list);
}

void init_list(list* list)
{
	list->data = malloc(sizeof(void**) * 8);
	list->length = 0;
	list->allocated_length = 8;
}
