#include <stdio.h>
#include <stdlib.h>
#include "array_void.h"

ArrayVoid_ptr create_void_array(int length){
  ArrayVoid_ptr new_void_array = malloc(sizeof(ArrayVoid));
  new_void_array->length = length;
  new_void_array->array = malloc(sizeof(Object) * length);
  return new_void_array;
}

ArrayVoid_ptr map_void(ArrayVoid_ptr src, MapperVoid mapper){
  ArrayVoid_ptr mapped_array = create_void_array(src->length);
  FOR_EACH(0, src->length)
  {
    mapped_array->array[i] = mapper(src->array[i]);
  }
  return mapped_array; 
}

ArrayVoid_ptr create_copy_of_void_array(ArrayVoid_ptr src){
  ArrayVoid_ptr copy = create_void_array(src->length);
  FOR_EACH(0, src->length)
  {
    copy->array[i] = src->array[i];
  }
  return copy;
}

ArrayVoid_ptr filter_void(ArrayVoid_ptr src, PredicateVoid predicate){
  if(src->length == 0){
    return create_void_array(0);
  }
  ArrayVoid_ptr new_array = create_void_array(src->length);
  new_array->length = 0;
  FOR_EACH(0, src->length)
  {
    if(predicate(src->array[i])){
      new_array->array[new_array->length] = src->array[i];
      new_array->length++;
    }
  }
  return create_copy_of_void_array(new_array);
}