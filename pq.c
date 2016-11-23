/*
 * This file contains the implementation of a priority queue.
 *
 * You must complete the implementations of these functions:
 *   pq_insert()
 *   pq_first()
 *   pq_remove_first()
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "dynarray.h"
#include "pq.h"

// This is the initial capacity that will be allocated for the heap.
#define INITIAL_HEAP_CAPACITY 16

/*
 * This is the definition of the structure we will use to represent the
 * priority queue.  It contains only a dynamic array, which will be used to
 * store the heap underlying the priority queue.
 */
struct pq {
  struct dynarray* heap;
};


/*
 * This is an auxiliary structure that we'll use to represent a single element
 * in the priority queue.  It contains two fields:
 *
 *   priority - the priority value assigned to the item
 *   item - the pointer to the data item represented by this element
 *
 * Both of these will come directly from the corresponding values passed to
 * pq_insert().
 */
struct pq_elem {
  int priority;
  void* item;
};


/*
 * This function allocates and initializes a new priority queue.
 *
 * You should not modify this function.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq->heap = dynarray_create(INITIAL_HEAP_CAPACITY);
  return pq;
}


/*
 * This function frees the memory associated with a priority queue.
 *
 * You should not modify this function.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  dynarray_free(pq->heap);
  free(pq);
}

/*
 * This function returns 1 if the given priority queue is empty or 0
 * otherwise.
 *
 * You should not mofidy this function.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return dynarray_size(pq->heap) > 0;
}


/*
 * This function inserts a new item with a specified priority into a priority
 * queue.
 *
 * You should complete the implementation of this function.  The first part
 * is done for, where a new element is created to be placed into the dynamic
 * array underlying the priority queue.
 */
void pq_insert(struct pq* pq, void* item, int priority) {
  assert(pq);

  /*
   * Allocate space for the new element to be placed into the priority queue
   * and initialize it with the provided values.
   */
  struct pq_elem* new_elem = malloc(sizeof(struct pq_elem));
  new_elem->item = item;
  new_elem->priority = priority;


   int insertion_index=dynarray_size(pq->heap);
   dynarray_insert(pq->heap, -1, new_elem);

  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the newly added element up in the heap array.  To
   * perform the percolation, you will have to compare the priority values of
   * the struct pq_elems in the heap array (i.e. by comparing the
   * elem->priority values).
   */

    perc_up(pq, insertion_index);

}

void perc_up(struct pq* pq, int index){
  if(dynarray_size(pq->heap)==1){
    return;
  }

  struct pq_elem* current = dynarray_get(pq->heap, index);
  if(dynarray_get(pq->heap, index/2) != NULL && index!=0){

    struct pq_elem* parent = dynarray_get(pq->heap, index/2);

    if(current->priority<parent->priority){
      dynarray_set(pq->heap, index, parent);
      dynarray_set(pq->heap, index/2, current);
      perc_up(pq, index/2);
    }
  }
  return;
}

void print_heap(struct pq* pq){
  for(int i=0; i<dynarray_size(pq->heap); i++){
    struct pq_elem *current = dynarray_get(pq->heap, i);
    printf("Index: %d priority: %d\n", i, current->priority);
  }
}
/*
 * This function returns the first (highest-priority) item from a priority
 * queue without removing it.
 *
 * You should complete the implementation of this function.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);

  struct pq_elem* first_elem = NULL;

  /*
   * Determine what index in the heap array corresponds to the highest-priority
   * element (i.e. the one with the lowest priority value), and store the
   * value there in first_elem.
   */
   first_elem = dynarray_get(pq->heap, 0);

  /*
   * Return the extracted item, if the element taken out of the priority
   * queue is not NULL.
   */
  if (first_elem != NULL) {
    return first_elem->item;
  } else {
    return NULL;
  }
}


/*
 * This function removes the first (highest-priority) element from a priority
 * queue and returns its value.
 *
 * You should complete this function.
 */
void* pq_remove_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);


  struct pq_elem* first_elem = NULL;

  /*
   * Determine what index in the heap array corresponds to the highest-priority
   * element (i.e. the one with the lowest priority value), and store the
   * value there in first_elem.
   */
  first_elem = dynarray_get(pq->heap, 0);
  if(dynarray_size(pq->heap)==1){
    dynarray_remove(pq->heap, 0);
    if (first_elem != NULL) {
      return first_elem->item;
    } else {
      return NULL;
    }
  }
  /*
   * Replace the hdfighest-priority element with the appropriate one from within
   * the heap array.  Remove that replacement element from the array after
   * copying its value to the location of the old highest-priority element..
   */
  dynarray_set(pq->heap, 0, dynarray_get(pq->heap, 1));
  dynarray_remove(pq->heap, 1);
  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the element that replaced the highest-priority
   * element down in the heap array.  To perform the percolation, you will
   * have to compare the priority values of the struct pq_elems in the heap
   * array (i.e. by comparing the elem->priority values).  It may be helpful
   * to write a helper function to accomplish this percolation down.
   */
  perc_down(pq, 0);

  /*
   * Return the extracted item, if the element taken out of the priority
   * queue is not NULL.
   */
  if (first_elem != NULL) {
    return first_elem->item;
  } else {
    return NULL;
  }
}

void perc_down(struct pq* pq, int index){
  struct pq_elem* current = dynarray_get(pq->heap, index);
  int left_index, right_index;
  if(index == 0){
    left_index = 1;
    right_index = 2;
  }
  else{
    left_index = index*2;
    right_index = index*2+1;
  }
  if(left_index < dynarray_size(pq->heap) && dynarray_get(pq->heap, left_index) != NULL){
    struct pq_elem* left = NULL;


    left = dynarray_get(pq->heap, left_index);

    if(current->priority>left->priority){
      dynarray_set(pq->heap, index, left);
      dynarray_set(pq->heap, left_index, current);
    }
    perc_down(pq, left_index);
  }

  else if(right_index < dynarray_size(pq->heap) && dynarray_get(pq->heap, right_index) != NULL){
    struct pq_elem* right = NULL;

    right = dynarray_get(pq->heap, right_index);


    if(current->priority>right->priority){
      dynarray_set(pq->heap, index, right);
      dynarray_set(pq->heap, right_index, current);
    }
    perc_down(pq, right_index);
  }
  return;
}
