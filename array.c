#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *create_array(int length){
  Array *new_array = malloc(sizeof(Array));
  new_array->length = length;
  new_array->array = malloc(sizeof(int) * length);
  return new_array;
}

Array *map(Array *src, Mapper mapper){
  Array *new_array = create_array(src->length);
  FOR_EACH(0, src->length)
  {
    new_array->array[i] = mapper(src->array[i]);
  }
  return new_array;
}

Array *create_copy_of_array(Array *src){
  Array *copy = create_array(src->length);
  FOR_EACH(0, src->length)
  {
    copy->array[i] = src->array[i];
  }
  return copy;
}


Array *filter(Array *src, Predicate predicate){
  Array *new_array = create_array(0);
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