#undef NDEGUG
#include <assert.h>
#include <lcthw/list.h>
#include <lcthw/dbg.h>

static void List_Check_invariant(List *list)
{
	assert(list != NULL);
	assert(list->count >= 0);

	if(list->count == 0) {
		assert(list->first == NULL);
		assert(list->last == NULL);
	}else {
		assert(list->first != NULL);
		assert(list->last != NULL);
		assert(list->first->prev == NULL);
		assert(list->last->next == NULL);

	}
}

List *List_create()
{
	return calloc(1, sizeof(List));
}
void List_destroy(List *list)
{
	assert(list != NULL);
	LIST_FOREACH(list, first, next, cur) {
		if(cur->prev) {
			free(cur->prev);
		}
	}

	free(list->last);
	free(list);

}

void List_clear(List *list) 
{
	assert(list != NULL);
	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
	}
}

void List_clear_destroy(List *list)
{
	assert(list != NULL);
	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
		if(cur->prev) {
			free(cur->prev);
		}
	}
	free(list->last);
	free(list);


}

void List_push(List *list, void *value)
{
	assert(list != NULL);
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if(list->last == NULL) {
		list->first = node;
		list->last = node;
	}else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}

	list->count++;
	List_Check_invariant(list);

error:
	return;
}

void *List_pop(List *list) 
{
	assert(list != NULL);
	ListNode *node = list->last;
	return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
	assert(list != NULL);
	assert(value != NULL);
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if(list->first == NULL) {
		list->first = node;
		list->last = node;
	}else {
		list->first->prev = node;
		node->next = list->first;
		list->first = node;
	}
	list->count++;
	List_Check_invariant(list);

error:
	return;
}

void *List_shift(List *list)
{
	assert(list != NULL);

	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
	assert(list != NULL);
	assert(node != NULL);
	void *result = NULL;

	check(list->first && list->last, "List is empty.");
	check(node, "node can't be NULL");

	if(node == list->first && node == list->last) {
		list->first = NULL;
		list->last = NULL;
	}else if(node == list->first) {
		list->first = node->next;
		check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
		list->first->prev = NULL;
	}else if(node == list->last) {
		list->last = node->prev;
		check(list->last != NULL, "Invalid list, somehow got a last that is NULL.");
		list->last->next = NULL;
	}else {
		ListNode *after = node->next;
		ListNode *before = node->prev;
		after->prev = before;
		before->next = after;
	}
	list->count--;
	List_Check_invariant(list);
	result = node->value;
	free(node);

error:
	return result;
}

List *List_copy(List *list)
{
	List *copy = NULL;
	check(list != NULL, "list can't be NULL");

	copy = List_create();
	check_mem(copy);

	LIST_FOREACH(list, first, next, cur) {
		int before = copy->count;
		List_push(copy, cur->value);
		check(copy->count == before + 1, "Failed to copy list node.");
	}
	return copy;

error:
	if(copy) List_clear_destroy(copy);
	return NULL;
}

List *List_concat(List *left, List *right) 
{
	List *result = NULL;
	check(left != NULL, "left can't be NULL.");
	check(right != NULL, "right can't be NULL");

	result = List_copy(left);
	check(result != NULL, "Failed to copy left list.");

	LIST_FOREACH(right, first, next, cur) {
		int before = result->count;
		List_push(result, cur->value);
		check(result->count == before + 1, "Failed to append right node.");
	}
	return result;

error:
	if(result) List_clear_destroy(result);
	return NULL;

}

List *List_split(List *list, ListNode *node) 
{
	List *right = NULL;
	int right_count = 0;
	check(list != NULL, "list can't be NULL.");
	check(node != NULL, "value can't be NULL.");

	right = List_create();
	check_mem(right);

	right->first = node;
	right->last = list->last;

	if(node->prev) {
		list->last = node->prev;
		list->last->next = NULL;
		node->prev = NULL;
	}else {
		list->first = NULL;
		list->last = NULL;
	}

	LIST_FOREACH(right, first, next, cur) {
		right_count++;
	}

	right->count = right_count;
	list->count -= right_count;
	List_Check_invariant(list);

	check(list->count >= 0, "Invalid split count.");

	return right;
error:
	if(right) List_clear_destroy(right);
	return NULL;
}

