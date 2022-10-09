/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

#define END_OF_FILE_CHAR '\0'
/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
    {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *ele = q->head;
    while (ele != NULL){
        list_ele_t *next = ele->next;
        free(ele->value); // Free the string
        free(ele);
        ele = next; // slide to the next element
    }
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    char *news;

    /* What should you do if the q is NULL? */
    if (q == NULL){
        return false;
    } 

    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    news = malloc(strlen(s) + 1); // +1 for "\0"

    /* What if either call to malloc returns NULL? */
    if (newh == NULL || news == NULL){
        return false;
    }

    newh->next = q->head;
    q->head = newh;
    q->size ++;

    strcpy(news, s);
    newh->value = news;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL){
        return false;
    }

    list_ele_t *newt;
    char *news;

    newt = malloc(sizeof(list_ele_t));
    news=malloc(strlen(s) + 1);

    if (newt == NULL || news == NULL){
        return false;
    }

    newt->next = q->tail->next; // Both should be NULL
    q->tail->next = newt; // Add new element to the tail
    q->tail = newt; // Update the tail to the new element
    q->size ++;

    strcpy(news, s);
    newt->value  = news;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (q==NULL){
        return false;
    }

    list_ele_t *oldh = q->head;
    q->head = q->head->next;

    if (buf != NULL){
        strncpy(buf, oldh->value, bufsize-1);
        buf[bufsize -1 ] = END_OF_FILE_CHAR;
    }

    free(oldh->value);
    free(oldh); // Clean all the char pointer and the old head
    q->size--;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL){
        return 0;
    } else {
        return q->size;
    }
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q  == NULL || q->head == NULL || q->head->next == NULL){
        return; // do nothing for null, empty and 1-element queue
    } 

    list_ele_t *prev = q->head;
    list_ele_t *cur = prev->next;
    prev->next = NULL; // The old head's next element when reversed should be NULL
    list_ele_t *next = cur;
    while (cur != NULL){
        next = cur->next;
        cur->next = prev; // reverse the next pointer
        prev = cur;
        cur = next;        
    }
    // Switch the head and tail pointer
    q->tail = q->head;
    q->head = prev; // at end of the while loop, prev is the last element that used to pointer 

}
