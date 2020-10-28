#include "list.h"
#include <stdlib.h>
#include <string.h>

//insert into back of the list (the only type of insertion we need for this program)
void insert_back(linked_list* list, void* item, size_t datasize)
{
	//if the list is zero we need to create the head
	if (get_length(*list) == 0)
	{
		//allocate a node and its data
		ll_node* additem = (ll_node*)malloc(sizeof(ll_node));
		additem->data = malloc(datasize);

		//memcpy the data and set next to NULL
		additem->next = NULL;
		memcpy(additem->data, item, datasize);

		//insert the node
		list->first = additem;
	}
	//otherwise we traverse to the end of the list and insert there
	else
	{
		//traverse to the end of the list and get the pointer to the final node
		ll_node* trackingitem = list->first;
		for (unsigned int i = 0; i < get_length(*list) - 1; i++)
			trackingitem = trackingitem->next;

		//same thing as earlier, allocate the node, its data, copy the data and set next to NULL
		ll_node* additem = (ll_node*)malloc(sizeof(ll_node));
		additem->data = malloc(datasize);
		additem->next = NULL;
		memcpy(additem->data, item, datasize);

		//append the node
		trackingitem->next = additem;
	}
}

//i dont think i'm actually using this function anywhere but here it is
ll_node get_item(linked_list list, unsigned int index)
{
	return *get_item_ptr(list, index);
}

//gets a pointer to a specified node
ll_node* get_item_ptr(linked_list list, unsigned int index)
{
	//if the index is greater than the length of the list, return NULL
	if (index >= get_length(list))
		return NULL;

	//traverse to the specified node
	ll_node* trackingitem = list.first;
	while (index > 0)
	{
		trackingitem = trackingitem->next;
		index--;
	}

	//return the pointer
	return trackingitem;
}

//gets the length of the list (why aren't i memoizing this?)
unsigned int get_length(linked_list list)
{
	//get the head of the list and set the length to 0
	unsigned int length = 0;
	ll_node* trackingitem = list.first;

	//if the head is NULL, return 0
	if (trackingitem == NULL)
		return 0;

	//traverse the entire list until we hit NULL
	while (trackingitem->next != NULL)
	{
		trackingitem = trackingitem->next;
		length++;
	}

	//return the number of traversals + 1
	return length + 1;
}

//the worst free_list function you've ever seen
//i wrote this at like midnight last night and to my knowledge it works so i don't wanna change it at this point
void free_list(linked_list* list)
{
	//this is very inefficient, please don't judge my polynomial time algorithm to free a linked list when I could've easily made it linear time
	//yes, i'm freeing it back to front instead of front to back without memoizing any lookups
	//yes, i'm a better software developer than this
	//no, Ms. Allen (the one who taught my 221) would not be proud of me
	unsigned int length;
	//while the length is >1
	while ((length = get_length(*list)) > 1)
	{
		//get the last two items
		ll_node* free_item = get_item_ptr(*list, length - 1);
		ll_node* prior_item = get_item_ptr(*list, length - 2);
		//free the last node and its data
		free(free_item->data);
		free(free_item);
		//set the next to last node's next to NULL
		prior_item->next = NULL;
	}
	//if the length is 1
	if (get_length(*list) == 1)
	{
		//free the head and its data
		free(list->first->data);
		free(list->first);
		//set the head to NULL
		list->first = NULL;
	}
}

//initialize a linked list
void init_list(linked_list* list)
{
	//just set the head to NULL
	list->first = NULL;
}
