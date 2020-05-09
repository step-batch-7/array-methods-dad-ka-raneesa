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
  printf("%s\n", message);
}

int square_of_num(int value)
{
  return value * value;
}

void test_map(Array *src, Array *empty_array){
  Array *actual = map(empty_array, &square_of_num);
  Array *expected = create_array(0);
  display_assertion(assert_array(actual,expected),"should get empty array for empty array given");

  actual = map(src, &square_of_num);
  expected = create_array(5);
  FOR_EACH(0,5){
    expected->array[i] = square_of_num(src->array[i]);
  }
  display_assertion(assert_array(actual,expected),"should get squares of a given array");
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

  printf(GREEN "\n%d passing" RESET, PASSING_TESTS);
  printf(RED "\n%d failing\n" RESET, FAILING_TESTS);
  return 0;
}