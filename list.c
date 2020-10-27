#include "list.h"
#include <stdlib.h>
#include <string.h>

void insert_back(linked_list* list, void* item, size_t datasize)
{
	if (get_length(*list) == 0)
	{
		ll_node* additem = (ll_node*)malloc(sizeof(ll_node));
		additem->data = malloc(datasize);
		additem->next = NULL;
		memcpy(additem->data, item, datasize);

		list->first = additem;
	}
	else
	{
		ll_node* trackingitem = list->first;
		for (unsigned int i = 0; i < get_length(*list) - 1; i++)
		{
			trackingitem = trackingitem->next;
		}

		ll_node* additem = (ll_node*)malloc(sizeof(ll_node));
		additem->data = malloc(datasize);
		additem->next = NULL;
		memcpy(additem->data, item, datasize);

		trackingitem->next = additem;
	}
}

ll_node get_item(linked_list list, unsigned int index)
{
	return *get_item_ptr(list, index);
}

ll_node* get_item_ptr(linked_list list, unsigned int index)
{
	if (index >= get_length(list))
		return NULL;

	ll_node* trackingitem = list.first;
	while (index > 0)
	{
		trackingitem = trackingitem->next;
		index--;
	}

	return trackingitem;
}

unsigned int get_length(linked_list list)
{
	unsigned int length = 0;
	ll_node* trackingitem = list.first;
	
	if (trackingitem == NULL)
		return 0;
	
	while (trackingitem->next != NULL)
	{
		trackingitem = trackingitem->next;
		length++;
	}
	return length + 1;
}

void free_list(linked_list* list)
{
	//this is very inefficient, please don't judge my polynomial time algorithm to free a linked list when I could've easily made it linear time
	unsigned int length;
	while ((length = get_length(*list)) > 1)
	{
		ll_node* free_item = get_item_ptr(*list, length - 1);
		ll_node* prior_item = get_item_ptr(*list, length - 2);
		free(free_item->data);
		free(free_item);
		prior_item->next = NULL;
	}
	if (get_length(*list) == 1)
	{
		free(list->first->data);
		free(list->first);
		list->first = NULL;
	}
}

void init_list(linked_list* list)
{
	list->first = NULL;
}
