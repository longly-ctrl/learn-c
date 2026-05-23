#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

/*
 * A node in a doubly linked list.
 */
typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
}ListNode;

/*
 * A doubly linked list that tracks its first node, last node, and count.
 */
typedef struct List {
	int count;
	ListNode *first;
	ListNode *last;
} List;

/*
 * Check that the list's internal structure is valid.
 *
 * This verifies the basic invariants that every list operation must perserve:
 * the list pointer is not NULL, count is never negative, an empty list has no
 * first or last node, and a non-empty list has valid first and last nodes.
 */
static void List_Check_invariant(List *list);
/*
 * Create a new empty list.
 */
List *List_create();
/*
 * Destroy the list and add its nodes.
 *
 * This does not free the values sotored in the nodes.
 * 
 * You should use clear first.
 */
void List_destroy(List *list);

/*
 * Free every value stored in the list.
 */
void List_clear(List *list);
/*
 * Free every value, every node, and the list itself.
 */
void List_clear_destroy(List *list);

/*
 * Return the number of nodes in the list.
 */
#define List_count(A) ((A)->count)
/*
 * Return the value stored in the first node, or NULL if the list is empty.
 */
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
/*
 * Return the value stored in the last node, or NULL if the list is empty.
 */
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

/*
 * Add a value to the end of the list.
 */
void List_push(List *list, void *value);
/*
 * Remove the last node and return its value.
 */
void *List_pop(List *list);

/*
 *Add a value to the beginning of the list.
 */ 
void List_unshift(List *list, void *value);
/*
 * Remove the first node and return its value
 */
void *List_shift(List *list);

/*
 * Remove a specific node and return its value.
 */
void *List_remove(List *list, ListNode *node);

/*
 * Create a shallow copy of the list.
 *
 * Copies the list nodes, but stores the same value pointer as the original
 * list. The values themselves are not duplicated.
 */
List *List_copy(List *list);

/*
 * Concatenate two lists into a new list.
 *
 * The returned list contains the values from left followed by the values from right.
 * The original list are not be destroyed.
 */
List *List_concat(List *left, List *right);

/*
 *Split a list at the given node.
 *Returns a new list starting at node. The original list keeps the nodes before
 *node. The node must belong the list.
 */
List *List_split(List *list, ListNode *value);

/*
 * Iterate through the list.
 *
 * Example:
 * LIST_FOREACH(list, first, next, cur) walks forword.
 * LIST_FORRACH(list, last, prev, cur) walks backward.
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
						ListNode *V = NULL;\
						for(V = _node = L->S; _node != NULL; V = _node =_node->M)

#endif
						

		
