#include <CUnit/Basic.h>

/* test files */
#include "stack_tests.h"
#include "array_list_tests.h"
#include "hashmap_tests.h"
#include "tree_tests.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

int main(void)
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* add a suite to the registry */
    pSuite = CU_add_suite("LibCollect Test Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if (!CU_add_test(pSuite, "push_pop_equality", test_push_pop_equality) ||
        !CU_add_test(pSuite, "free_empty_stack", test_free_empty_stack) ||
        !CU_add_test(pSuite, "pop_from_empty_stack", test_pop_from_empty_stack) ||
        !CU_add_test(pSuite, "array_list_in_out", test_array_list_in_out) ||
        !CU_add_test(pSuite, "array_list_iterator_test", test_array_list_iterator_test) ||
        !CU_add_test(pSuite, "put_get_equality", test_put_get_equality) ||
        !CU_add_test(pSuite, "put_reassign", test_put_reassign) ||
        !CU_add_test(pSuite, "tree_iteration", test_tree_iteration) ||
        !CU_add_test(pSuite, "tree_create", test_tree_create))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
