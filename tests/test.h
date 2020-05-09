#ifndef __TEST_ARRAY_
#define __TEST_ARRAY_

#define PRINT_STRING(string) printf("%s\n", string)

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define PASS GREEN "\u2714 " RESET
#define FAIL RED "\u2718 " RESET

int PASSING_TESTS = 0;
int FAILING_TESTS = 0;

int square_of_num(int value);
Bool is_even(int number);
int add_two_numbers(int num1, int num2);
Bool assert(int num1, int num2);
Bool assert_array(Array *array_1, Array *array_2);
void display_assertion(Bool assertion_status, char *message);
void test_map(Array *src, Array *empty_array);
#endif