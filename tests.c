
#include <CUnit/CUnit.h>
#include <stdio.h>
#include "model.h"


int spinup_persistence(void) {
	printf("Spinning up persistence tests\n\n");
	// TODO: there should be a flush persistence here, really
	return 0;
}

int teardown_persistence(void) {
	printf("Tearing down persistence tests\n\n");
	return 0;
}

void test_empty_list(void) {
	printf("Testing for empty list\n");
	CU_ASSERT_PTR_NULL(persistence_get_head_terminal())
}

Card_Type_T c_types[1] = {Visa};
Transaction_Type_T t_types[2] = {Cheque, EFTPOS};

void test_mem_create_terminal(void) {
	Terminal_T* term;

	term = mem_create_terminal(1, c_types, 2, t_types);
	persistence_add_terminal(term);
	printf("Terminal ID: %d\n", term->id);
	CU_ASSERT_EQUAL(term->id, 1);

	term = mem_create_terminal(1, c_types, 2, t_types);
	persistence_add_terminal(term);
	printf("Terminal ID: %d\n", term->id);
	CU_ASSERT_EQUAL(term->id, 2);

	term = mem_create_terminal(1, c_types, 2, t_types);
	persistence_add_terminal(term);
	printf("Terminal ID: %d\n", term->id);
	CU_ASSERT_EQUAL(term->id, 3);
}

void test_not_empty_list(void) {
	printf("testing for non-empty list\n");
	CU_ASSERT_PTR_NOT_NULL(persistence_get_head_terminal());
}

void test_find_terminal_pos(void) {
	printf("testing for existing terminal in list");
	CU_ASSERT_PTR_NOT_NULL(persistence_find_terminal(1));
	CU_ASSERT_PTR_NOT_NULL(persistence_find_terminal(2));
}

void test_find_terminal_neg(void) {
	printf("testing for not existing terminal in list");
	CU_ASSERT_PTR_NULL(persistence_find_terminal(200));
}

int spinup_parsing(void) {
	printf("Spinning up parsing tests\n\n");
	return 0;
}

int teardown_parsing(void) {
	printf("Tearing down parsing tests\n\n");
	return 0;
}

void test_parsing() {
	const char* json_in = "{\"cardType\": [\"Visa\",\"MasterCard\",\"EFTPOS\"],\"transactionType\": [\"Cheque\",\"Savings\",\"Credit\"]}";
	Terminal_T* term = parse_terminal(json_in);
	printf("Parsed json: got id %d\n", term->id);
	CU_ASSERT_PTR_NOT_NULL(term);
}

void test_printing() {
	Terminal_T* term = mem_create_terminal(1, c_types, 2, t_types);\
	const char* termS = print_terminal(term);
	printf("%s\n", termS);
}

int spinup_rest(void) {
	printf("Spinning up restful api tests\n\n");
	return 0;
}

int teardown_rest(void) {
	printf("Tearing down restful api tests\n\n");
	return 0;
}

void test_create_rest() {
	const char* json_in = "{\"cardType\": [\"Visa\",\"MasterCard\",\"EFTPOS\"],\"transactionType\": [\"Cheque\",\"Savings\",\"Credit\"]}";
	const char* ret = rest_handle_create("/", json_in);
	printf("%s", ret);
}

void test_get_rest_all() {
	const char* term = print_terminal(persistence_find_terminal(4));
	CU_ASSERT_TRUE(strlen(term) >= 10);
}



void define_persistence_tests(void){
	CU_pSuite persistence_tests = CU_add_suite("persistence_tests", spinup_persistence, teardown_persistence);
	CU_add_test(persistence_tests, "test empty list", test_empty_list);
	CU_add_test(persistence_tests, "test create terminal", test_mem_create_terminal);
	CU_add_test(persistence_tests, "test non-empty-list", test_not_empty_list);
	CU_add_test(persistence_tests, "test find existing terminal", test_find_terminal_pos);
	CU_add_test(persistence_tests, "test find non-existant terminal", test_find_terminal_neg);
}

void define_parsing_tests(void) {
	CU_pSuite parsing_tests = CU_add_suite("parsing_tests", spinup_parsing, teardown_parsing);
	CU_add_test(parsing_tests, "test parsing", test_parsing);
	CU_add_test(parsing_tests, "test printing", test_printing);
}
void define_rest_tests(void) {
	CU_pSuite rest_tests = CU_add_suite("rest_tests", spinup_rest, teardown_rest);
	CU_add_test(rest_tests, "test add", test_create_rest);
//	CU_add_test(rest_tests, "test get all", test_get_rest_all);
}

int main(int argc, char **argv) {
	CU_initialize_registry();

	define_persistence_tests();
	define_parsing_tests();
//	define_rest_tests();



	CU_run_all_tests();

	printf("\nTests run: %d\n", CU_get_number_of_tests_run());
	printf("\nTests failed: %d\n", CU_get_number_of_tests_failed());

	CU_cleanup_registry();
	return CU_get_error();
}

