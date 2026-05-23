#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
static List *copy = NULL;
static List *result = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
	list = List_create();
	mu_assert(list != NULL, "Failed to create list.");

	return NULL;
}

char *test_destroy()
{
	List_clear_destroy(list);
	List_clear_destroy(copy);
	List_clear_destroy(result);

	return NULL;
}

char *test_push_pop()
{
	List_push(list, test1);
	mu_assert(List_last(list) == test1, "Wrong last value.");
       	
	List_push(list, test2);
	mu_assert(List_last(list) == test2, "Wrong last value.");

	List_push(list, test3);
	mu_assert(List_last(list) == test3, "Wrong last Value.");
	mu_assert(List_count(list) == 3, "Wrong count on push.");

	char *val = List_pop(list);
	mu_assert(val == test3, "Wrong value on pop.");

	val = List_pop(list);
	mu_assert(val == test2, "Wrong value on pop.");
	
	val = List_pop(list);
	mu_assert(val == test1, "Wrong value on pop.");
	mu_assert(List_count(list) == 0, "Wrong count after pop.");

	return NULL;
}

char *test_unshift()
{
	List_unshift(list, test1);
	mu_assert(List_first(list) == test1, "Wrong first value.");

	List_unshift(list, test2);
	mu_assert(List_first(list) == test2, "Wrong first value.");
	
	List_unshift(list, test3);
	mu_assert(List_first(list) == test3, "Wrong first value.");
	mu_assert(List_count(list) == 3, "Wrong count on unshift.");

	return NULL;
}

char *test_remove()
{
	char *val = List_remove(list, list->first->next);
	mu_assert(val == test2, "Wrong remove element.");
	mu_assert(List_count(list) == 2, "Wrong count after remove.");
	mu_assert(List_first(list) == test3, "Wrong first after remove.");
	mu_assert(List_last(list) == test1, "Wrong last after remove.");

	return NULL;
}

char *test_shift()
{
	mu_assert(List_count(list) != 0, "Wrong count before shift.");
	char *val = List_shift(list);
	mu_assert(val == test3, "Wrong value on shift.");

	val = List_shift(list);
	mu_assert(val == test1, "Wrong value on shift.");
	mu_assert(List_count(list) == 0, "Wrong count after shift.");

	return NULL;
}

char *test_copy()
{
	List_push(list, test1);
     	List_push(list, test2);
	List_push(list, test3);
	
	copy = List_copy(list);
	mu_assert(copy != NULL, "Failed to copy list.");
	mu_assert(List_count(copy) == 3, "Wrong copy count.");
	mu_assert(List_first(copy) == test1, "Wrong copy first.");
	mu_assert(List_last(copy) == test3, "Wrong copy last.");

}

char *test_concat()
{
	result = List_concat(list, copy);
	mu_assert(result != NULL, "Failed to concatenate.");
	mu_assert(List_count(result) == 6, "Wrong result count.");
	mu_assert(List_first(result) == test1, "Wrong result first.");
	mu_assert(List_last(result) == test3, "Wrong result last.");
}
 
char *test_split()
{
	List *right = List_create();
	right = List_split(list, list->first->next);

	mu_assert(List_count(list) == 1, "Wrong left count after split.");
	mu_assert(List_count(right) == 5, "Wrong right count after split.");
	mu_assert(List_first(list) == test1, "Wrong left first.");
	mu_assert(List_first(right) == test2, "Wrong right first.");
	mu_assert(List_last(list) == test1, "Wrong left last.");
	mu_assert(List_last(right) == test3, "Wrong right last.");
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_remove);
	mu_run_test(test_shift);
	mu_run_test(test_copy);
	mu_run_test(test_concat);
	mu_run_test(test_split);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TEST(all_tests);

