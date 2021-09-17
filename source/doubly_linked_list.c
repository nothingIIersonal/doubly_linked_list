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

void clear_doubly_linked_list(doubly_linked_list * p_list)
{
	node * p_temp = p_list->p_head;
	node * p_next =	NULL;

	while (p_temp)
	{
		p_next = p_temp->p_next;

		p_temp->p_next = NULL;
		p_temp->p_previous = NULL;
		
		free(p_temp);
		p_temp = p_next;

		(p_list->size)--;
	}

	p_list->p_tail = NULL;
	p_list->p_head = NULL;
}

void delete_doubly_linked_list(doubly_linked_list * p_list)
{
	clear_doubly_linked_list(p_list);

	free(p_list);
	p_list = NULL;
}

node * create_node(node * p_next, node * p_previous, void * p_data, u8 * type)
{
	node * p_node = (node *)calloc(1, sizeof( node ));

	if (p_node == NULL)
	{
		printf("Unable not allocate memory\n");		
		exit(1);
	}

	p_node->p_data = p_data;
	p_node->_type = type;

	p_node->p_next = p_next;
	p_node->p_previous = p_previous;

	return p_node;
}

node * find_node_by_id(doubly_linked_list * p_list, size_t id)
{
	if (id >= p_list->size)
	{
		printf("Index out of list size\n");
		return NULL;
	}

	node * p_search;
	
	if (id > (p_list->size / 2))
	{
		p_search = p_list->p_tail;
		
		while (p_search && ((id++) < (p_list->size - 1)))
		{
			p_search = p_search->p_previous;
		}		
	}
	else
	{
		p_search = p_list->p_head;

		while (p_search && id--)
		{
			p_search = p_search->p_next;
		}
	}

	return p_search;
}

node * find_node_by_ptr(doubly_linked_list * p_list, node * p_node)
{
	node * p_search_node = p_list->p_head;
	for (size_t i = 0; i < p_list->size; i++)
	{
		if ( p_node == p_search_node )
			break;
		p_search_node = p_search_node->p_next;
	}

	if ( p_node != p_search_node )
	{
		printf("Unable find node %p\n", p_node);
		return NULL;
	}	
}

node * push_head(doubly_linked_list * p_list, void * p_data, u8 * type)
{
	if ( !_item_type_is_correct(type) )
	{
		printf("\nUnable to identify data type \"%s\"", type);
		return NULL;
	}

	node * p_temp = create_node(p_list->p_head, NULL, p_data, type);

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

	return p_temp;
}

node * push_tail(doubly_linked_list * p_list, void * p_data, u8 * type)
{
	if ( !_item_type_is_correct(type) )
	{
		printf("\nUnable to identify data type \"%s\"", type);
		return NULL;
	}

	node * p_temp = create_node(NULL, p_list->p_tail, p_data, type);

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

	return p_temp;
}

node * insert_after(doubly_linked_list * p_list, node * p_node, void * p_data, u8 * type)
{
	if ( p_node == p_list->p_tail )
	{
		node * p_temp = push_tail(p_list, p_data, type);
		return p_temp;
	}

	node * p_search_node = find_node_by_ptr(p_list, p_node);

	if (p_search_node == NULL) { return NULL; }

	node * p_temp = create_node(p_search_node->p_next, p_search_node, p_data, type);

	p_search_node->p_next->p_previous = p_temp;
	p_search_node->p_next = p_temp;

	(p_list->size)++;

	return p_temp;
}

node * insert_before(doubly_linked_list * p_list, node * p_node, void * p_data, u8 * type)
{
	if ( p_node == p_list->p_head )
	{
		node * p_temp = push_head(p_list, p_data, type);
		return p_temp;
	}

	node * p_search_node = find_node_by_ptr(p_list, p_node);

	if (p_search_node == NULL) { return NULL; }

	node * p_temp = create_node(p_search_node, p_search_node->p_previous, p_data, type);

	p_search_node->p_previous->p_next = p_temp;
	p_search_node->p_previous = p_temp;

	(p_list->size)++;

	return p_temp;
}

node * insert_by_id_right_shift(doubly_linked_list * p_list, size_t id, void * p_data, u8 * type)
{
	if (id == 0) { return push_head(p_list, p_data, type); }
	if (id == p_list->size - 1) { return insert_before(p_list, p_list->p_tail, p_data, type); }

	node * p_temp = find_node_by_id(p_list, id);

	if (p_temp == NULL) { return NULL; }

	node * p_node = create_node(p_temp, p_temp->p_previous, p_data, type);

	p_temp->p_previous->p_next = p_node;
	p_temp->p_previous = p_node;

	(p_list->size)++;

	return p_node;
}

node * insert_by_id_left_shift(doubly_linked_list * p_list, size_t id, void * p_data, u8 * type)
{
	if (id == 0) { return insert_after(p_list, p_list->p_head, p_data, type); }
	if (id == p_list->size - 1) { return push_tail(p_list, p_data, type); }

	node * p_temp = find_node_by_id(p_list, id);

	if (p_temp == NULL) { return NULL; }

	node * p_node = create_node(p_temp->p_next, p_temp, p_data, type);

	p_temp->p_next->p_previous = p_node;
	p_temp->p_next = p_node;

	(p_list->size)++;

	return p_node;
}

node * replace_by_id(doubly_linked_list * p_list, size_t id, void * p_data, u8 * type)
{
	node * p_temp = find_node_by_id(p_list, id);

	if (p_temp == NULL) { return NULL; }

	p_temp->p_data = p_data;
	p_temp->_type = type;

	return p_temp;
}

void * pop_head_data(doubly_linked_list * p_list)
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

void * pop_tail_data(doubly_linked_list * p_list)
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

void * pop_data_by_id(doubly_linked_list * p_list, size_t id)
{
	if (id >= p_list->size)
	{
		printf("Index out of list size\n");
		return NULL;
	}

	if (id == 0) { return pop_head_data(p_list); }
	if (id == p_list->size - 1) { return pop_tail_data(p_list); }

	node * p_temp = find_node_by_id(p_list, id);

	if (p_temp == NULL) { return NULL; }

	void * p_data = p_temp->p_data;

	p_temp->p_next->p_previous = p_temp->p_previous;
	p_temp->p_previous->p_next = p_temp->p_next;

	free(p_temp);

	(p_list->size)--;

	return p_data;
}

void * get_head_data(doubly_linked_list * p_list)
{
	if ( !(p_list->size) )
	{
		printf("Unable to get head item - list is empty\n");		
		exit(3);
	}

	return p_list->p_head->p_data;
}

void * get_tail_data(doubly_linked_list * p_list)
{
	if ( !(p_list->size) )
	{
		printf("Unable to get head item - list is empty\n");		
		exit(3);
	}

	return p_list->p_tail->p_data;
}

void * get_data_by_id(doubly_linked_list * p_list, size_t id)
{
	node * p_temp = find_node_by_id(p_list, id);

	if (p_temp == NULL) { return NULL; }

	return p_temp->p_data;
}

void _swap_elements(doubly_linked_list * p_list, node * first_node, node * second_node)
{
	void * p_data_1 = first_node->p_data;
	void * p_data_2 = second_node->p_data;

	u8 * type_1 = first_node->_type;
	u8 * type_2 = second_node->_type;

	first_node->p_data = p_data_2;
	first_node->_type = type_2;

	second_node->p_data = p_data_1;
	second_node->_type = type_1;
}

void swap_elements(doubly_linked_list * p_list, node * first_node, node * second_node)
{
	if ( !first_node || !second_node ) { return; }

	_swap_elements(p_list, first_node, second_node);	
}

void swap_elements_by_ptr(doubly_linked_list * p_list, node * first_node, node * second_node)
{
	swap_elements(p_list, first_node, second_node);
}

void swap_elements_by_id(doubly_linked_list * p_list, size_t first_id, size_t second_id)
{
	swap_elements(p_list, find_node_by_id(p_list, first_id), find_node_by_id(p_list, second_id));
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
