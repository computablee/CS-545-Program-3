#pragma once
#include <stddef.h>

//OBSELETE - NOT USED IN THE FINAL PROGRAM

//this is a header file, look in list.c for explanations for all the functions

//definition for a node, contains a void pointer to the data it contains and a pointer to the next node
//the void pointer is so that i had a reason to call this a "generic linked list library" that's not limited to
//storing brush data
typedef struct ll_node
{
	void* data;
	struct ll_node* next;
} ll_node;

//coulda also probably just done
//typedef ll_node* linked_list
typedef struct
{
	ll_node* first;
} linked_list;

void ll_insert_back(linked_list* list, void* item, size_t datasize);
ll_node ll_get_item(linked_list list, unsigned int index);
ll_node* ll_get_item_ptr(linked_list list, unsigned int index);
unsigned int ll_get_length(linked_list list);
void ll_free_list(linked_list* list);
void ll_init_list(linked_list* list);