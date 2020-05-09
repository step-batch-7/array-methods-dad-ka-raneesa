#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "array_void.h"

#define NEW_LINE printf("\n");

Object increment_by_one(Object data);
Object convert_to_lowercase(Object data);
int square_of_num(int value);
Bool is_even(int number);
int add_two_numbers(int num1, int num2);
void display_array(Array *array);
void display_number(void *data);
void display_char(void *data);
void do_array_operations(Array *numbers, Array *empty_array);
void do_void_array_operations(ArrayVoid_ptr void_array);

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
  printf("%d ", *number);
}

void display_char(void *data)
{
  char *letter = (char *)data;
  printf("%c ", *letter);
}

void do_void_array_operations(ArrayVoid_ptr void_array){
  printf("Void map:\n");
  ArrayVoid_ptr new_void_array = map_void(void_array, &increment_by_one);
  printf("Increment numbers by one : ");
  FOR_EACH(0,new_void_array->length){
    display_number(new_void_array->array[i]);
  }
  NEW_LINE;

  new_void_array = map_void(void_array, &convert_to_lowercase);
  printf("Convert to lower case : ");
  FOR_EACH(0,new_void_array->length){
    display_char(new_void_array->array[i]);
  }
  NEW_LINE;
}

int main(void){
  Array *empty_array = create_array(0);
  Array *numbers = create_array(5);
  numbers->array[0] = 65;
  numbers->array[1] = 66;
  numbers->array[2] = 67;
  numbers->array[3] = 68;
  numbers->array[4] = 69;
  do_array_operations(numbers, empty_array);
  NEW_LINE;

  ArrayVoid_ptr void_array = create_void_array(5);
  FOR_EACH(0,5){
    void_array->array[i] = &numbers->array[i];
  }

  do_void_array_operations(void_array);

  free(numbers);
  free(empty_array);
  return 0;
}