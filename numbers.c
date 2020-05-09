#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "array_void.h"

#define NEW_LINE printf("\n");

Object increment_by_one(Object data);
int square_of_num(int value);
Bool is_even(int number);
int add_two_numbers(int num1, int num2);
void display_array(Array *array);
void do_array_operations(Array *numbers, Array *empty_array);
void do_void_array_operations(ArrayVoid_ptr void_array);

Object increment_by_one(Object data){
  int *number = (int *)data;
  *number = *number + 1;
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

void display_array(Array *array)
{
  FOR_EACH(0, array->length)
  {
    printf("%d ", array->array[i]);
  }
  printf("\n");
}

void do_array_operations(Array *numbers, Array *empty_array){
  int result;
  printf("Original array: ");
  display_array(numbers);
  NEW_LINE;

  printf("Map Operation:\n");
  Array *new_array = map(empty_array, &square_of_num);
  printf("Map an empty list: ");
  display_array(new_array);

  new_array = map(numbers, &square_of_num);
  printf("Map list with numbers(Squares): ");
  display_array(new_array);
  NEW_LINE;

  printf("Filter Operation:\n");
  new_array = filter(empty_array, &is_even);
  printf("Filter an empty list: ");
  display_array(new_array);

  new_array = filter(numbers, &is_even);
  printf("Filter even numbers: ");
  display_array(new_array);
  NEW_LINE;

  printf("Reduce Operation:\n");
  result = reduce(numbers, 0, &add_two_numbers);
  printf("Add all numbers : %d", result);
  NEW_LINE;
  
  result = reduce(numbers, 10, &add_two_numbers);
  printf("Add all numbers with initial value : %d", result);
  NEW_LINE;
}

void display_number(void *data)
{
  int *number = (int *)data;
  printf("number: %d\n", *number);
}

void do_void_array_operations(ArrayVoid_ptr void_array){
  printf("Void map:\n");
  ArrayVoid_ptr new_void_array = map_void(void_array, &increment_by_one);
  FOR_EACH(0,new_void_array->length){
    display_number(new_void_array->array[i]);
  }
}

int main(void){
  Array *empty_array = create_array(0);
  Array *numbers = create_array(5);
  numbers->array[0] = 1;
  numbers->array[1] = 2;
  numbers->array[2] = 3;
  numbers->array[3] = 4;
  numbers->array[4] = 5;

  do_array_operations(numbers, empty_array);
  
  ArrayVoid_ptr void_array = create_void_array(numbers->length);

  FOR_EACH(0,5){
    void_array->array[i] = &numbers->array[i];
  }

  do_void_array_operations(void_array);

  free(numbers);
  free(empty_array);
  return 0;
}