#include "doubly_linked_list.h"

const size_t _item_type_is_correct(const u8 * type)
{
	if ( !strcmp(type, U8) || !strcmp(type, U8STR) || !strcmp(type, FLT) ||
		!strcmp(type, PTR) || !strcmp(type, U64) || !strcmp(type, SSZT) )
	{
		return 1;
	}

	return 0;
}

doubly_linked_list * create_doubly_linked_list()
{
	doubly_linked_list * p_temp = (doubly_linked_list *)calloc(1, sizeof( doubly_linked_list ));

	p_temp->size = 0;
	p_temp->p_head = p_temp->p_tail = NULL;
	 
	return p_temp;
}

void delete_doubly_linked_list(doubly_linked_list * p_list)
{
	node * p_temp = p_list->p_head;
	node * p_next =	NULL;

	while (p_temp)
	{
		p_next = p_temp->p_next;
		free(p_temp);
		p_temp = p_next;
	}

	free(p_list);
	p_list = NULL;
}

const void push_head(doubly_linked_list * p_list, void * p_data, u8 * type)
{
	if ( !_item_type_is_correct(type) )
	{
		printf("\nUnable to identify data type \"%s\"", type);
		return;
	}

	node * p_temp = (node *)calloc(1, sizeof( node ));

	if (p_temp == NULL)
	{
		printf("Unable not allocate memory\n");		
		exit(1);
	}

	p_temp->p_data = p_data;
	p_temp->p_next = p_list->p_head;
	p_temp->p_previous = NULL;

	p_temp->_type = type;

	if (p_list->p_head)
	{
		p_list->p_head->p_previous = p_temp;
	}
	p_list->p_head = p_temp;

	if (p_list->p_tail == NULL)
	{
		p_list->p_tail = p_temp;
	}

	(p_list->size)++;
}

const void push_tail(doubly_linked_list * p_list, void * p_data, u8 * type)
{
	if ( !_item_type_is_correct(type) )
	{
		printf("\nUnable to identify data type \"%s\"", type);
		return;
	}

	node * p_temp = (node *)calloc(1, sizeof(node));

	if (p_temp == NULL)
	{
		printf("Can not allocate memory\n");		
		exit(2);
	}

	p_temp->p_data = p_data;
	p_temp->p_previous = p_list->p_tail;
	p_temp->p_next = NULL;

	p_temp->_type = type;

	if (p_list->p_tail)
	{
		p_list->p_tail->p_next = p_temp;
	}
	p_list->p_tail = p_temp;

	if (p_list->p_head == NULL)
	{
		p_list->p_head = p_temp;
	}

	(p_list->size)++;
}

void * pop_head(doubly_linked_list * p_list)
{
	if ( !(p_list->size) )
	{
		printf("Unable to get head item - list is empty\n");		
		exit(3);
	}

	node * p_previous = p_list->p_head;
	void * p_data = p_list->p_head->p_data;

	p_list->p_head = p_list->p_head->p_next;

	if (p_list->p_head)
	{
		p_list->p_head->p_previous = NULL;
	}

	if ( p_list->size == 1 )
	{	
		p_list->p_tail = NULL;
	}

	free(p_previous);

	(p_list->size)--;

	return p_data;
}

void * pop_tail(doubly_linked_list * p_list)
{
	if ( !(p_list->size) )
	{
		printf("Unable to get tail item - list is empty\n");		
		exit(4);
	}

	node * p_next = p_list->p_tail;
	void * p_data = p_list->p_tail->p_data;

	p_list->p_tail = p_list->p_tail->p_previous;

	if (p_list->p_tail)
	{
		p_list->p_tail->p_next = NULL;
	}

	if ( p_list->size == 1 )
	{
		p_list->p_head = NULL;
	}

	free(p_next);

	(p_list->size)--;

	return p_data;
}

const void print_doubly_linked_list(const doubly_linked_list * p_list) 
{
    node * p_temp = p_list->p_head;
    
    while (p_temp) 
    {
    	if ( !strcmp(p_temp->_type, U8) )
			printf("\n"U8" ", *( (u8 *)(p_temp->p_data) ) );

		else if ( !strcmp(p_temp->_type, U8STR) )
			printf("\n"U8STR" ", (u8 *)(p_temp->p_data) );
    	
    	else if ( !strcmp(p_temp->_type, FLT) )
			printf("\n"FLT" ", *( (float *)(p_temp->p_data) ) );
		
		else if ( !strcmp(p_temp->_type, PTR) )
			printf("\n"PTR" ", (p_temp->p_data) );
    	
    	else if ( !strcmp(p_temp->_type, U64) )
			printf("\n"U64" ", *( (u64 *)(p_temp->p_data) ) );
    	
    	else if ( !strcmp(p_temp->_type, SSZT) )
			printf("\n"SSZT" ", *( (ssize_t *)(p_temp->p_data) ) );

        p_temp = p_temp->p_next;
    }
    printf("\n");
}
