/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
212  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q;
    if ((q = malloc(sizeof(queue_t))) == NULL)
        return NULL;
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    /* How about freeing the list elements and the strings? */
    list_ele_t *cur = q->head;
    list_ele_t *tmp;
    while (cur) {
        tmp = cur;
        cur = cur->next;
        free(tmp->value);
        free(tmp);
    }

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if ((newh = malloc(sizeof(list_ele_t))) == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    char *str;

    int len = strlen(s);
    if ((str = malloc(len + 1)) == NULL) {
        free(newh);
        return false;
    }
    str[len] = '\0';
    strcpy(str, s);
    newh->value = str;

    if (!q->head) {
        newh->next = NULL;
        q->tail = newh;
        q->head = newh;
        q->size += 1;
        return true;
    }

    newh->next = q->head;
    q->head = newh;
    q->size += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if (!q)
        return false;
    list_ele_t *newh;
    if ((newh = malloc(sizeof(list_ele_t))) == NULL)
        return false;

    char *str;

    int len = strlen(s);
    if ((str = malloc(len + 1)) == NULL) {
        free(newh);
        return false;
    }
    str[len] = '\0';
    strcpy(str, s);
    newh->value = str;

    if (!q->head) {
        newh->next = NULL;
        q->tail = newh;
        q->head = newh;
        q->size += 1;
        return true;
    }
    newh->next = NULL;
    q->tail->next = newh;
    q->tail = newh;
    q->size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */

    if (!q || !q->head)
        return false;

    list_ele_t *tmp;
    tmp = q->head;
    q->head = q->head->next;

    if (sp) {
        strncpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    free(tmp->value);
    free(tmp);

    q->size -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */

    if (!q)
        return 0;

    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */

    if (!q)
        return;
    if ((!q->head) || (!q->head->next))
        return;

    list_ele_t *next;
    list_ele_t *prev = q->head;
    list_ele_t *cur = q->head->next;


    prev->next = NULL;
    q->tail = prev;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    q->head = prev;

    return;
}
