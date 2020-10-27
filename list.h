#pragma once
#include <ctype.h>

typedef struct ll_node
{
	void* data;
	struct ll_node* next;
} ll_node;

typedef struct
{
	ll_node* first;
} linked_list;

void insert_back(linked_list* list, void* item, size_t datasize);
ll_node get_item(linked_list list, unsigned int index);
ll_node* get_item_ptr(linked_list list, unsigned int index);
unsigned int get_length(linked_list list);
void free_list(linked_list* list);
void init_list(linked_list* list);