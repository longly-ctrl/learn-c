#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

inline void ListNode_swap(ListNode *a, ListNode *b)
{
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
	int sorted = 1;
	check(list != NULL, "list can't be NULL.");
	check(cmp != NULL, "cmp can't be NULL.");

	if(List_count(list) <= 1) {
		return 0;
	}

	do {
		sorted = 1;
		LIST_FOREACH(list, first, next, cur) {
			if(cur->next) {
				if(cmp(cur->value, cur->next->value) > 0) {
					ListNode_swap(cur, cur->next);
					sorted = 0;
				}
			}
		}
	}while(!sorted);

	return 0;
error:
	return 1;
}

static List *List_merge(List *left, List *right, List_compare cmp)
{
	check(left != NULL, "left can't be NULL.");
	check(right != NULL, "right can't be NULL.");
	check(cmp != NULL, "cmp can't be NULL.");

	List *result = List_create();
	check_mem(result);

	void *val = NULL;

	while(List_count(left) > 0 || List_count(right) > 0) 
	{
		if(List_count(left) > 0 && List_count(right) > 0)
		{
			if(cmp(List_first(left), List_first(right)) <= 0) {
				val = List_shift(left);
			}else {
				val = List_shift(right);
			}
			List_push(result, val);
		}else if(List_count(left) > 0) {
			val = List_shift(left);
			List_push(result, val);
		}else if(List_count(right) > 0) {
			val = List_shift(right);
			List_push(result, val);
		}
	}
	return result;

error:
	return NULL;
}

List *List_merge_sort(List *list, List_compare cmp)
{
	check(list != NULL, "list can't be NULL.");
	check(cmp != NULL, "cmp can't be NULL.");

	if(List_count(list) <= 1) {
		return list;
	}

	List *left = List_create();
	List *right = List_create();
	check_mem(left);
	check_mem(right);

	int middle = List_count(list) / 2;

	LIST_FOREACH(list, first, next, cur) {
		if(middle > 0) {
			List_push(left, cur->value);
		}else {
			List_push(right, cur->value);
		}

		middle --;
	}

	List *sort_left = List_merge_sort(left, cmp);
	List *sort_right = List_merge_sort(right, cmp);

	if(sort_left != left) List_destroy(left);
	if(sort_right != right) List_destroy(right);

	return List_merge(sort_left, sort_right, cmp);

error:
	return NULL;
}

int List_is_sorted(List *list, List_compare cmp)
{
	check(list != NULL, "list can't be NULL.");
	check(cmp != NULL, "cmp can't be NULL.");

	if(List_count(list) <= 1) {
		return 1;
	}
	
	LIST_FOREACH(list, first, next, cur) {
		if(cur->next && cmp(cur->value, cur->next->value) > 0) {
			return 0;
		}

	}

	return 1;

error:
	return 0;
}

