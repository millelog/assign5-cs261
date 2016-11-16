#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"

struct dynarray {
  void** data;
  int size;
  int capacity;
};

struct dynarray* dynarray_create(int capacity) {

  assert(capacity > 0);
  struct dynarray* da = malloc(sizeof(struct dynarray));
  assert(da);

  da->data = malloc(capacity * sizeof(void*));
  assert(da->data);
  da->size = 0;
  da->capacity = capacity;

  return da;

}

void dynarray_free(struct dynarray* da) {

  assert(da);
  free(da->data);
  free(da);

}

int dynarray_size(struct dynarray* da) {

  assert(da);
  return da->size;

}

void* dynarray_get(struct dynarray* da, int idx) {

  assert(da);
  assert((idx < da->size && idx >= 0) || idx == -1);

  // Let users specify idx = -1 to indicate the end of the array.
  if (idx == -1) {
    idx = da->size - 1;
  }

  return da->data[idx];

}

void dynarray_set(struct dynarray* da, int idx, void* val) {

  assert(da);
  assert((idx < da->size && idx >= 0) || idx == -1);

  // Let users specify idx = -1 to indicate the end of the array.
  if (idx == -1) {
    idx = da->size - 1;
  }

  da->data[idx] = val;

}

void _dynarray_resize(struct dynarray* da, int new_capacity) {

  assert(new_capacity > da->size);
  void** new_data = malloc(new_capacity * sizeof(void*));
  assert(new_data);

  // Copy the old data to the new array.
  for (int i = 0; i < da->size; i++) {
    new_data[i] = da->data[i];
  }

  // Free the old data and update da with the new data.
  free(da->data);
  da->data = new_data;
  da->capacity = new_capacity;

}

void dynarray_insert(struct dynarray* da, int idx, void* val) {

  assert(da);
  assert((idx <= da->size && idx >= 0) || idx == -1);

  // Let users specify idx = -1 to indicate adding to the end of the array.
  if (idx == -1) {
    idx = da->size;
  }

  // Resize if needed.
  if (da->size == da->capacity) {
    _dynarray_resize(da, 2 * da->capacity);
  }

  /*
   * Make space for the new value at idx by moving all the subsequent elements
   * back one spot in the array.
   */
  for (int i = da->size; i > idx; i--) {
    da->data[i] = da->data[i-1];
  }

  da->data[idx] = val;
  da->size++;

}

void dynarray_remove(struct dynarray* da, int idx) {

  assert(da);
  assert((idx < da->size && idx >= 0) || idx == -1);

  // Let users specify idx = -1 to indicate the end of the array.
  if (idx == -1) {
    idx = da->size - 1;
  }

  // Move each subsequent array element after idx into the space before it.
  for (int i = idx; i < da->size - 1; i++) {
    da->data[i] = da->data[i+1];
  }

  da->size--;

}
