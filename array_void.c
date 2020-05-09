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