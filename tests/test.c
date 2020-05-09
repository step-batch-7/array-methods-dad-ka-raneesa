#include <stdio.h>
#include <stdlib.h>
#include "../array.h"
#include "test.h"

Bool assert(int num1, int num2){
  if(num1 == num2){
    return True;
  }
  return False;
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
  expected->array[0] = 2;
  expected->array[1] = 4;
  display_assertion(assert_array(actual,expected),"should get evens in a given array\n");
}

void test_reduce(Array *src, Array *empty_array){
  PRINT_STRING("Reduce:\n");
  int actual = reduce(src, 0, &add_two_numbers);
  int expected = 15;
  display_assertion(assert(actual,expected),"should get sum of all numbers in array");

  actual = reduce(src, 10, &add_two_numbers);
  expected = 25;
  display_assertion(assert(actual,expected),"should get sum of all numbers in array and initial value");

  actual = reduce(empty_array, 10, &add_two_numbers);
  expected = 10;
  display_assertion(assert(actual,expected),"should get initial value when array has no elements");
}

int main(void){
  Array *numbers = create_array(5);
  numbers->array[0] = 1;
  numbers->array[1] = 2;
  numbers->array[2] = 3;
  numbers->array[3] = 4;
  numbers->array[4] = 5;

  Array *empty_array = create_array(0);
  test_map(numbers, empty_array);
  test_filter(numbers, empty_array);
  test_reduce(numbers, empty_array);

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);
  return 0;
}