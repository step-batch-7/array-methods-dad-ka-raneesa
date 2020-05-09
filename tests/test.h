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
int add_two_numbers(int num1, int num2);
Bool is_even(int number);
Bool check_even(Object data);
Bool is_vowel(Object data);
Object increment_by_one(Object data);
Object convert_to_lowercase(Object data);

Bool assert(int num1, int num2);
Bool void_assert(Object actual, Object expected);
Bool assert_array(Array *array_1, Array *array_2);
Bool assert_void_array(ArrayVoid_ptr array_1, ArrayVoid_ptr array_2);

void display_assertion(Bool assertion_status, char *message);

void test_map(Array *src, Array *empty_array);
void test_filter(Array *src, Array *empty_array);
void test_reduce(Array *src, Array *empty_array);

Array *create_test_array(void);

void test_map_void();
void test_filter_void();
#endif