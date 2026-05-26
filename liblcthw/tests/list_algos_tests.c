#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define BENCHMARK_SIZE 100
#define BENCHMARK_SECONDS 3.0

char *benchmark_values[] = {
	"zulu", "alpha", "echo", "bravo", "delta",
	"hotel", "charlie", "foxtrot", "india", "golf",
	"kilo", "juliet", "mike", "lima", "november",
	"oscar", "quebec", "papa", "romeo", "sierra",
	"tango", "victor", "uniform", "whiskey", "xray",
	"yankee"
};

#define BENCHMARK_VALUES_COUNT \
	(sizeof(benchmark_values) / sizeof(benchmark_values[0]))

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5

List *create_words()
{
	int i = 0;
	List *words = List_create();

	for(i = 0; i < NUM_VALUES; i++) {
		List_push(words, values[i]);
	}
	return words;
}

List *create_benchmark_words()
{
	int i = 0;
	List *words = List_create();
	check_mem(words);

	for(i = 0; i < BENCHMARK_SIZE; i++) {
		List_push(words, benchmark_values[i % BENCHMARK_VALUES_COUNT]);
	}

	return words;

error:
	return NULL;
}

int is_sorted(List *words)
{
	LIST_FOREACH(words, first, next, cur) {
		if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
			debug("%s, %s", (char *)cur->value, (char *)cur->next->value);
			return 0;
		}
	}

	return 1;
}


char *test_bubble_sort()
{
	List *words = create_words();

	int rc = List_bubble_sort(words, (List_compare)strcmp);
	mu_assert(rc == 0, "Bubble sort failed.");
	mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");


	rc = List_bubble_sort(words, (List_compare)strcmp);
	mu_assert(rc == 0, "Bubble sort failed.");
	mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

	List_destroy(words);

	words = List_create();
	rc = List_bubble_sort(words, (List_compare)strcmp);
	mu_assert(rc == 0, "Bubble sort failed on empty list.");
	mu_assert(is_sorted(words), "Words should be sorted if empty.");

	List_destroy(words);

	return NULL;
}

char *test_merge_sort()
{
	List *words = create_words();

	List *res = List_merge_sort(words, (List_compare)strcmp);
	mu_assert(is_sorted(res), "Words are not sorted after merge sort.");
	
	List *res2 = List_merge_sort(words, (List_compare)strcmp);
	mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");

	List_destroy(res2);
	List_destroy(res);

	List_destroy(words);

	return NULL;
}

char *test_sort_performance()
{
	int bubble_rounds = 0;
	int merge_rounds = 0;
	double bubble_seconds = 0.0;
	double merge_seconds = 0.0;

	clock_t start = clock();

	while(bubble_seconds < BENCHMARK_SECONDS) {
		List *words = create_benchmark_words();
		mu_assert(words != NULL, "Failed to create benchmark words.");

		int rc = List_bubble_sort(words, (List_compare)strcmp);
		mu_assert(rc == 0, "Bubble sort failed during benchmark words.");
		mu_assert(List_is_sorted(words, (List_compare)strcmp),
				"Bubble sort benchmark result was not sorted.");

		List_destroy(words);
		bubble_rounds++;
		bubble_seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
	}

	start = clock();

	while(merge_seconds < BENCHMARK_SECONDS) {
		List *words = create_benchmark_words();
		mu_assert(words != NULL, "Failed to create benchmark words.");

		List *sorted = List_merge_sort(words, (List_compare)strcmp);
		mu_assert(sorted != NULL, "Merge sort failed during benchmark.");
		mu_assert(List_is_sorted(sorted, (List_compare)strcmp),
				"Merge sort benchmark result was not sorted.");

		List_destroy(words);
		List_destroy(sorted);
		merge_rounds++;
		merge_seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
	}

	printf("\n---- SORT PERFORMANCE ----\n");
	printf("List size: %d\n", BENCHMARK_SIZE);
	printf("Bubble sort: %d rounds in %.2f seconds, %.8f sec/rounds\n",
			bubble_rounds,
			bubble_seconds,
			bubble_seconds / bubble_rounds);

	printf("Merge sort: %d rounds in %.2f seconds, %.8f sec/rounds\n",
			merge_rounds,
			merge_seconds,
			merge_seconds / merge_rounds);

	return NULL;
}




char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_bubble_sort);
	mu_run_test(test_merge_sort);
	mu_run_test(test_sort_performance);

	return NULL;

}

RUN_TEST(all_tests);
