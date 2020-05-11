#include <stdio.h>
#include <stdlib.h>
#include "../array_void.h"
#include "test.h"

Bool assert(int actual, int expected){
  return actual == expected;
}

Bool assert_void(Object actual, Object expected){
  int *num1 = (int *)actual;
  int *num2 = (int *)expected;
  return *num1 == *num2;
}

Bool assert_array(Array *array_1, Array *array_2)
{
  if (array_1->length != array_2->length)
  {
    return False;
  }
  Bool assertion_status = True;
  for (int i = 0; i < array_1->length; i++)
  {
    assertion_status &= assert(array_1->array[i], array_2->array[i]);
  }
  return assertion_status;
}

Bool assert_void_array(ArrayVoid_ptr array_1, ArrayVoid_ptr array_2)
{
  if (array_1->length != array_2->length)
  {
    return False;
  }
  Bool assertion_status = True;
  for (int i = 0; i < array_1->length; i++)
  {
    assertion_status &= assert_void(array_1->array[i], array_2->array[i]);
  }
  return assertion_status;
}

void display_assertion(Bool assertion_status, char *message)
{
  if (assertion_status)
  {
    printf(PASS);
    PASSING_TESTS++;
  }
  else
  {
    printf(FAIL);
    FAILING_TESTS++;
  }
  PRINT_STRING(message);
}

Object increment_by_one(Object data){
  int *number = (int *)data;
  *number = *number + 1;
  return (Object)number;
}

Object convert_to_lowercase(Object data){
  int *number = (int *)data;
  if(*number>=65 && *number<=90){
    *number = *number + 32;
   }
  return (Object)number;
}

int square_of_num(int value)
{
  return value * value;
}

Bool is_even(int number){
  if(number % 2 == 0){
    return True;
  }
  return False;
}

Bool check_even(Object data){
  int *number = (int *)data;
  return is_even(*number);
}

Bool is_vowel(Object data){
  char c = *(char *)data;
  int lowercase, uppercase;
  lowercase = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
  uppercase = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
  return (lowercase || uppercase);
}

int add_two_numbers(int num1, int num2){
  return num1 + num2;
}

Object add_numbers(Object data1, Object data2){
  int *num1 = (int *)data1;
  int *num2 = (int *)data2;
  *num2 = *num1 + *num2;
  return (Object)num2;
}


void test_map(Array *src, Array *empty_array){
  PRINT_STRING("Map:\n");
  Array *actual = map(empty_array, &square_of_num);
  Array *expected = create_array(0);
  display_assertion(assert_array(actual,expected),"should get empty array for empty array given");

  actual = map(src, &square_of_num);
  expected = create_array(5);
  FOR_EACH(0,5){
    expected->array[i] = src->array[i] * src->array[i];
  }
  display_assertion(assert_array(actual,expected),"should get squares of a given array\n");
}

void test_filter(Array *src, Array *empty_array){
  PRINT_STRING("Filter:\n");
  Array *actual = filter(empty_array, &is_even);
  Array *expected = create_array(0);
  display_assertion(assert_array(actual,expected),"should get empty array for empty array given");

  actual = filter(src, &is_even);
  expected = create_array(2);
  expected->array[0] = 66;
  expected->array[1] = 68;
  display_assertion(assert_array(actual,expected),"should get evens in a given array\n");
}

void test_reduce(Array *src, Array *empty_array){
  PRINT_STRING("Reduce:\n");
  int actual = reduce(src, 0, &add_two_numbers);
  int expected = 335;
  display_assertion(assert(actual,expected),"should get sum of all numbers in array");

  actual = reduce(src, 10, &add_two_numbers);
  expected = 345;
  display_assertion(assert(actual,expected),"should get sum of all numbers in array and initial value");

  actual = reduce(empty_array, 10, &add_two_numbers);
  expected = 10;
  display_assertion(assert(actual,expected),"should get initial value when array has no elements\n");
}

Array *create_test_array(void){
  Array *numbers = create_array(5);
  numbers->array[0] = 65;
  numbers->array[1] = 66;
  numbers->array[2] = 67;
  numbers->array[3] = 68;
  numbers->array[4] = 69;
  return numbers;
}

ArrayVoid_ptr initialization_of_void_array(void){
  Array *numbers = create_test_array();
  ArrayVoid_ptr void_array = create_void_array(5);
  FOR_EACH(0,5){
    void_array->array[i] = &numbers->array[i];
  }
  return void_array;
}


void test_map_void(){
  PRINT_STRING("Map void:\n");
  ArrayVoid_ptr void_array = initialization_of_void_array();

  ArrayVoid_ptr actual = map_void(void_array, &increment_by_one);
  ArrayVoid_ptr expected = create_void_array(5);
  int initial_value = 66;
  int *num = malloc(sizeof(int) * 5);
  FOR_EACH(0,5){
    num[i] = initial_value + i;
    expected->array[i] = &num[i];
  }
  display_assertion(assert_void_array(actual,expected),"should increment numbers by 1");

  actual = map_void(void_array, &convert_to_lowercase);
  FOR_EACH(0,5){
    num[i] = num[i] + 32;
  }
  display_assertion(assert_void_array(actual,expected),"should convert all to lowercase\n");
}

void test_filter_void(){
  PRINT_STRING("Filter void:\n");
  ArrayVoid_ptr void_array = initialization_of_void_array();

  ArrayVoid_ptr actual = filter_void(void_array, &check_even);
  ArrayVoid_ptr expected = create_void_array(2);
  int *num = malloc(sizeof(int) * 2);
  num[0] = 66;
  num[1] = 68;
  int *numbers_array[2] = {&num[0], &num[1]};
  expected->array = (Object *)numbers_array;
  display_assertion(assert_void_array(actual,expected),"should filter all even numbers");

  actual = filter_void(void_array, &is_vowel);
  int *result = (Object)actual->array[0];
  num[0] = 65;
  num[1] = 69;
  display_assertion(assert_void_array(actual,expected),"should filter all vowels\n");
}

void test_reduce_void(){
  ArrayVoid_ptr void_array = initialization_of_void_array();
  ArrayVoid_ptr empty_array = create_void_array(0);
  PRINT_STRING("Reduce void:\n");
  int *init = malloc(sizeof(int));
  *init = 0;
  Object actual = (Object)init;
  actual = reduce_void(void_array, init, &add_numbers);
  int *result = malloc(sizeof(int));
  *result = 335;
  Object expected = (Object)result;
  display_assertion(assert_void(actual,expected),"should get sum of all numbers in array");

  *init = 10;
  actual = reduce_void(void_array, init, &add_numbers);
  *result = 345;
  display_assertion(assert_void(actual,expected),"should get sum of all numbers in array and initial value");

  *init = 10;
  actual = reduce_void(empty_array, init, &add_numbers);
  *result = 10;
  display_assertion(assert_void(actual,expected),"should get initial value when array has no elements\n");
}

int main(void){
  Array *numbers = create_test_array();

  Array *empty_array = create_array(0);
  test_map(numbers, empty_array);
  test_filter(numbers, empty_array);
  test_reduce(numbers, empty_array);

  test_map_void();
  test_filter_void();
  test_reduce_void();

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);
  return 0;
}