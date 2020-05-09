#include <stdio.h>
#include <stdlib.h>
#include "../array_void.h"
#include "test.h"

Bool assert(int actual, int expected){
  return actual == expected;
}

Bool void_assert(Object actual, Object expected){
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
    assertion_status &= void_assert(array_1->array[i], array_2->array[i]);
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

int add_two_numbers(int num1, int num2){
  return num1 + num2;
}

void test_map(Array *src, Array *empty_array){
  PRINT_STRING("Map:\n");
  Array *actual = map(empty_array, &square_of_num);
  Array *expected = create_array(0);
  display_assertion(assert_array(actual,expected),"should get empty array for empty array given");

  actual = map(src, &square_of_num);
  expected = create_array(5);
  FOR_EACH(0,5){
    expected->array[i] = square_of_num(src->array[i]);
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

void test_map_void(){
  PRINT_STRING("Map void:\n");
  Array *numbers = create_test_array();
  ArrayVoid_ptr void_array = create_void_array(5);
  FOR_EACH(0,5){
    void_array->array[i] = &numbers->array[i];
  }

  ArrayVoid_ptr actual = map_void(void_array, &increment_by_one);
  ArrayVoid_ptr expected = create_void_array(5);
  FOR_EACH(0,5){
    expected->array[i] = increment_by_one(void_array->array[i]);
  }
  display_assertion(assert_void_array(actual,expected),"should increment numbers by 1");

  actual = map_void(void_array, &convert_to_lowercase);
  expected = create_void_array(5);
  FOR_EACH(0,5){
    expected->array[i] = convert_to_lowercase(void_array->array[i]);
  }
  display_assertion(assert_void_array(actual,expected),"should convert to lowercase\n");
}

int main(void){
  Array *numbers = create_test_array();

  Array *empty_array = create_array(0);
  test_map(numbers, empty_array);
  test_filter(numbers, empty_array);
  test_reduce(numbers, empty_array);

  test_map_void();

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);
  return 0;
}