#include "list.h"
#include <stdlib.h>
#include <string.h>

//insert into back of the list (the only type of insertion we need for this program)
void insert_back(list* list, void* item, size_t datasize)
{
	//copy the data over
	void* data = malloc(datasize);
	memcpy(data, item, datasize);

	//if we're at capacity
	if (list->length == list->allocated_length)
	{
		//reallocate
		list->data = realloc(list->data, sizeof(void*) * list->allocated_length * 2);
		list->allocated_length *= 2;
	}

	//insert the item
	list->data[list->length] = data;
	list->length++;
}

//frees the list and returns it to its initial state
void free_list(list* list)
{
	//free all the data in the array
	for (unsigned int i = 0; i < list->length; i++)
		free(list->data[i]);
	//free the array
	free(list->data);
	//initialize the list
	init_list(list);
}

//initializes the list
void init_list(list* list)
{
	//allocate 8 elements to start with
	list->data = malloc(sizeof(void**) * 8);
	//set the metadata
	list->length = 0;
	list->allocated_length = 8;
}
