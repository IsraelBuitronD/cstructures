#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdlib.h>

/* Doubly linked list element */
typedef struct _doubly_list_element {
  void *data;
  struct _doubly_list_element *prev;
  struct _doubly_list_element *next;
} doubly_list_element;

/* Doubly linked list structure */
typedef struct _doubly_list {
  int size;

  void (*destroy)(void *data);
  int  (*match)(const void *key1, const void *key2);

  doubly_list_element *head;
  doubly_list_element *tail;
} doubly_list;

void dlist_initialize(doubly_list *list, void (*destroy)(void *data));
void dlist_destroy(doubly_list *list);
int  dlist_insert_prev(doubly_list *list, doubly_list_element *element, const void *data);
int  dlist_insert_next(doubly_list *list, doubly_list_element *element, const void *data);
int  dlist_remove(doubly_list *list, doubly_list_element *element, void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_prev(element) ((element)->prev)
#define dlist_next(element) ((element)->next)

#endif
