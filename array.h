#ifndef __ARRAY_H
#define __ARRAY_H

#define FOR_EACH(startAt, endAt) for (int i = startAt; i < endAt; i++)

typedef enum
{
  False,
  True
} Bool;

typedef int (*Mapper)(int);
typedef Bool (*Predicate)(int);
typedef int (*Reducer)(int, int);

typedef struct
{
  int *array;
  int length;
} Array;

Array *create_array(int length);
Array *map(Array *src, Mapper mapper);
Array *filter(Array *src, Predicate predicate);
int reduce(Array *src, int init, Reducer reducer);

#endif
