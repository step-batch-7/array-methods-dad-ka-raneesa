#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *map(Array *src, Mapper mapper){
  Array *new_array = malloc(sizeof(Array));
  new_array->length = src->length;
  new_array->array = malloc(sizeof(int) * new_array->length);
  FOR_EACH(0, src->length)
  {
    new_array->array[i] = mapper(src->array[i]);
  }
  return new_array;
}

Array *create_copy_of_array(Array *new_array){
  Array *copy = malloc(sizeof(Array));
  copy->length = new_array->length;
  copy->array = malloc(sizeof(int) * new_array->length);
  FOR_EACH(0, new_array->length)
  {
    copy->array[i] = new_array->array[i];
  }
  return copy;
}


Array *filter(Array *src, Predicate predicate){
  Array *new_array = malloc(sizeof(Array));
  new_array->length = 0;
  new_array->array = malloc(sizeof(int) * src->length);
  FOR_EACH(0, src->length)
  {
    if(predicate(src->array[i])){
      new_array->array[new_array->length] = src->array[i];
      new_array->length++;
    }
  }
  return create_copy_of_array(new_array);
}

int reduce(Array *src, int init, Reducer reducer){
  int result = init;
  FOR_EACH(0, src->length){
    result = reducer(src->array[i], result);
  }
  return result;
}