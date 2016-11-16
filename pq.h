/*
 * This file contains the declarations of the structure and functions for a
 * priority queue.
 */

#ifndef __PQ_H
#define __PQ_H

/*
 * Structure used to represent a priority queue.
 */
struct pq;

/*
 * Creates a new priority queue.
 */
struct pq* pq_create();

/*
 * Frees the memory associated with a priority queue.
 */
void pq_free(struct pq* pq);

/*
 * Returns 1 if the given priority queue is empty or 0 otherwise.
 */
int pq_isempty(struct pq* pq);

/*
 * Inserts an item with a specified priority into a priority queue.
 *
 * @param item This is a generic pointer to any kind of item to be inserted
 *   into the priority queue.  It can point to an int (i.e. an int*), string
 *   (a char*), or any other type of data, even a struct of some sort (e.g.
 *   a struct foo*).
 *
 * @param priority This is the priority value to associate with the item
 *   being inserted into the priority queue.  Lower values here correspond
 *   to higher priorities.  For example an item with priority value 0 will
 *   be returned from the priority queue before an item with priority 5.
 */
void pq_insert(struct pq* pq, void* item, int priority);

/*
 * Returns the first (i.e. highest-priority) item in a priority queue without
 * removing it from the queue.
 */
void* pq_first(struct pq* pq);

/*
 * Removes the first (i.e. highest-priority) item in a priority queue and
 * returns it.
 */
void* pq_remove_first(struct pq* pq);


#endif
