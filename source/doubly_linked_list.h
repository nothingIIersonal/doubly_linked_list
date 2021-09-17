#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

// some types of node datas

#define U8 "%c"
#define U8STR "%s"
#define FLT "%f"
#define PTR "%p"
#define U64 "%ld"
#define SSZT "%zu"

// ...

typedef uint8_t u8;
typedef uint64_t u64;

typedef struct _node
{
	void * p_data;

	struct _node * p_previous;
	struct _node * p_next;

	u8 * _type;

} node;

typedef struct _doubly_linked_list
{
    ssize_t size;

    node * p_head;
    node * p_tail;
    
} doubly_linked_list;

const size_t _item_type_is_correct(const u8 *); 

doubly_linked_list * create_doubly_linked_list();

const void clear_doubly_linked_list(doubly_linked_list *);

const void delete_doubly_linked_list(doubly_linked_list *);

node * create_node(node *, node *, void *, u8 *);

node * find_node_by_id(doubly_linked_list *, size_t);

node * find_node_by_ptr(doubly_linked_list *, node *);

node * push_head(doubly_linked_list *, void *, u8 *);

node * push_tail(doubly_linked_list *, void *, u8 *);

node * insert_after(doubly_linked_list *, node *, void *, u8 *);

node * insert_before(doubly_linked_list *, node *, void *, u8 *);

node * insert_by_id_right_shift(doubly_linked_list *, size_t, void *, u8 *);

node * insert_by_id_left_shift(doubly_linked_list *, size_t, void *, u8 *);

node * replace_by_id(doubly_linked_list *, size_t, void *, u8 *);

void * pop_head_data(doubly_linked_list *);

void * pop_tail_data(doubly_linked_list *);

void * pop_data_by_id(doubly_linked_list *, size_t);

void * get_head_data(doubly_linked_list *);

void * get_tail_data(doubly_linked_list *);

void * get_data_by_id(doubly_linked_list *, size_t);

const void _swap_elements(doubly_linked_list *, node *, node *);

const void swap_elements(doubly_linked_list *, node *, node *);

const void swap_elements_by_ptr(doubly_linked_list *, node *, node *);

const void swap_elements_by_id(doubly_linked_list *, size_t, size_t);

const void print_doubly_linked_list(const doubly_linked_list *);

#endif