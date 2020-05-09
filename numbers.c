#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "array_void.h"

#define NEW_LINE printf("\n");

Object increment_by_one(Object data);
Object convert_to_lowercase(Object data);
Object add_numbers(Object num1, Object num2);
int square_of_num(int value);
Bool is_even(int number);
Bool is_vowel(Object data);
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

Bool is_vowel(Object data){
  char c = *(char *)data;
  int lowercase, uppercase;
  lowercase = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
  uppercase = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
  return (lowercase || uppercase);
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

int add_two_numbers(int num1, int num2){
  return num1 + num2;
}

Object add_numbers(Object data1, Object data2){
  int *num1 = (int *)data1;
  int *num2 = (int *)data2;
  *num2 = *num1 + *num2;
  return (Object)num2;
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
  printf("Map void:\n");
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
  NEW_LINE;

  printf("Filter void:\n");
  new_void_array = filter_void(void_array, &check_even);
  printf("Increment numbers by one : ");
  FOR_EACH(0,new_void_array->length){
    display_number(new_void_array->array[i]);
  }
  NEW_LINE;

  new_void_array = filter_void(void_array, &is_vowel);
  printf("Vowels : ");
  FOR_EACH(0,new_void_array->length){
    display_char(new_void_array->array[i]);
  }
  NEW_LINE;
  NEW_LINE;

  int *init = malloc(sizeof(int));
  *init = 0;
  Object result = (Object)init;
  printf("Reduce void:\n");
  result = reduce_void(void_array, init, &add_numbers);
  printf("Sum of all numbers in array : ");
  display_number(result);
  NEW_LINE;

  *init = 100;
  result = reduce_void(void_array, init, &add_numbers);
  printf("Sum of all numbers in array and initial value : ");
  display_number(result);
  NEW_LINE;

  *init = 100;
  ArrayVoid_ptr empty_void_array = create_void_array(0);
  result = reduce_void(empty_void_array, init, &add_numbers);
  printf("Sum When empty array is given: ");
  display_number(result);
  NEW_LINE;

  free(init);
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