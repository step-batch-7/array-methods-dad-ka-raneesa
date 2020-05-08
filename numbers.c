#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define NEW_LINE printf("\n");

int square_of_num(int value);
Bool is_even(int number);
int add_two_numbers(int num1, int num2);
void display_array(Array *array);

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

int main(void){
  int result;
  Array *numbers = malloc(sizeof(Array));
  numbers->length = 5;
  numbers->array = malloc(sizeof(int) * numbers->length);
  numbers->array[0] = 1;
  numbers->array[1] = 2;
  numbers->array[2] = 3;
  numbers->array[3] = 4;
  numbers->array[4] = 5;

  Array *empty_array = malloc(sizeof(Array));
  empty_array->length = 0;
  empty_array->array = malloc(sizeof(int) * 0);

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

  return 0;
}