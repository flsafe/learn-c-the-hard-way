#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
	list = List_create();
	mu_assert(list != NULL, "Failed to create the list");

	return NULL;
}

char *test_destroy()
{
	List_clear_destroy(list);

	return NULL;
}

char *test_push_pop()
{
	List_push(list, test1);
	mu_assert(List_last(list) == test1, "Wrong last value");

	List_push(list, test2);
	mu_assert(List_last(list) == test2, "Wrong last value");

	List_push(list, test3);
	mu_assert(List_last(list) == test3, "Wrong last value");
	mu_assert(List_count(list) == 3, "Wrong count");

	char *val = List_pop(list);
	mu_assert(val == test3, "Wrong popped value");

	val = List_pop(list);
	mu_assert(val == test2, "Wrong popped value");

	val = List_pop(list);
	mu_assert(val == test1, "Wrong popped value");
	mu_assert(List_count(list) == 0, "Wrong count");

	return NULL;
}

char *test_shift()
{
	List_shift(list, test1);
	mu_assert(List_first(list) == test1, "Wrong first value");

	List_shift(list, test2);
	mu_assert(List_first(list) == test2, "Wrong first value");

	List_shift(list, test3);
	mu_assert(List_first(list) == test3, "Wrong last value");
	mu_assert(List_count(list) == 3, "Wrong count");

	return NULL;
}

char *test_remove()
{
	// We only need to test the middle remove case since push/shift
	// already tests the other cases
	char *val = List_remove(list, list->first->next);
	mu_assert(val == test2, "Wrong removed element");
	mu_assert(List_count(list) == 2, "Wrong count after remove");
	mu_assert(List_first(list) ==  test3, "Wrong first after remove");
	mu_assert(List_last(list) == test1, "Wrong last after remove");

	return NULL;
}

char *test_unshift()
{
	char *val = List_unshift(list);
	mu_assert(val == test3, "Wrong value on unshfit");

	val = List_unshift(list);
	mu_assert(val == test1, "Wrong value on unshift");
	mu_assert(List_count(list) == 0, "Wrong count");

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_shift);
	mu_run_test(test_remove);
	mu_run_test(test_unshift);
	mu_run_test(test_destroy);
	
	return NULL;
}

RUN_TESTS(all_tests);
