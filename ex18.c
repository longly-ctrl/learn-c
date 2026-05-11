#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
	if(errno){
		perror(message);
	}else{
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

typedef int (*compare_cb)(int a, int b);
typedef int* (*sort_func)(int *numbers, int count, compare_cb cmp);



int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if(!target) die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	for(i = 0; i< count; i++){
		for(j = 0; j < count - 1; j++){
			if(cmp(target[j], target[j+1]) > 0){
					temp = target[j+1];
					target[j+1] = target[j];
					target[j] = temp;
			}
		}
	}

	return target;
}

int *insertion_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int key = 0;
	int *target = malloc(sizeof(int) * count);

	if(!target) die("Memory error.");
	memcpy(target, numbers, count * sizeof(int));

	for(i = 0; i < count; i++){
		key = target[i];
		j = i - 1;
	

		while(j >= 0 && cmp(target[j], key) > 0 ){
			target[j + 1] = target[j];
			j = j - 1;
		}
		target[j + 1] = key;
	}
	return target;
}

int *selection_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int min_idx = 0;
	int temp = 0;
	int *target = malloc(count * sizeof(int));
	if(!target) die("Memory error.");
	memcpy(target, numbers, count * sizeof(int));

	for(i = 0; i < count - 1; i++){
		min_idx = i;
		for(j = i + 1; j < count; j++){
			if(cmp(target[j], target[min_idx]) < 0){
				min_idx = j;
			}
		}
		if(min_idx != i){
			temp = target[i];
			target[i] = target[min_idx];
			target[min_idx] = temp;
		}
	}
	return target;
}


int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if(a == 0 || b ==0){
		return 0;
	}else{
		return a % b;
	}

}
int wrong_signature(int a, int b, int c)
{
	return a - b;
}

char* wrong_return_type(int a, int b)
{
	return "wrong";
}

void test_sorting_with_algorithm(int *numbers, int count,
					compare_cb cmp, sort_func sorter,
					const char *algorithm_name)
{
	int i = 0;
	printf("\n%s with ", algorithm_name);

	if(cmp == sorted_order) printf("sortr_order: ");
	else if(cmp == reverse_order) printf("reverse_order: ");
	else printf("strange_order: ");

	int *sorted = sorter(numbers, count, cmp);
	if(!sorted) die("Failed to sort as requested.");

	for(i = 0; i < count; i++){
		printf("%d ", sorted[i]);
	}
	printf("\n");
	free(sorted);
}



int main(int argc, char *argv[])
{
	if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs =  argv + 1;
	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error.");

	for(i = 0; i < count; i++){
		numbers[i] = atoi(inputs[i]);
	}

	printf("Original array: ");
	for(i = 0; i < count; i++){
		printf("%d ", numbers[i]);
	}
	printf("\n");

	printf("/n=== Testing Bubble Sort ===/n");
	test_sorting_with_algorithm(numbers, count, sorted_order, bubble_sort, "Bubble Sort");
	test_sorting_with_algorithm(numbers, count, reverse_order, bubble_sort, "Bubble Sort");
	test_sorting_with_algorithm(numbers, count, strange_order, bubble_sort, "Bubble Sort");

	printf("/n=== Testing Insertion Sort ===/n");
	test_sorting_with_algorithm(numbers, count, sorted_order, insertion_sort, "Insertion Sort");
	test_sorting_with_algorithm(numbers, count, reverse_order, insertion_sort, "Insertion Sort");
	test_sorting_with_algorithm(numbers, count, strange_order, insertion_sort, "Insertion Sort");

	printf("/n=== Testing Selection Sort ===/n");
	test_sorting_with_algorithm(numbers, count, sorted_order, selection_sort, "Selection Sort");
	test_sorting_with_algorithm(numbers, count, reverse_order, selection_sort, "Selection Sort");
	test_sorting_with_algorithm(numbers, count, strange_order, selection_sort, "Selection Sort");

	free(numbers);
	return 0;
}


