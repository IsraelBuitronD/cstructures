#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdlib.h>

/* Singly linked list element */
typedef struct _singly_list_element {
  void *data;
  struct _singly_list_element *next;
} singly_list_element;

/* Singly linked list structure */
typedef struct _singly_list {
  int size;

  void (*destroy)(void *data);
  int  (*match)(const void *key1, const void *key2);

  singly_list_element *head;
  singly_list_element *tail;
} singly_list;

void slist_initialize(singly_list *list, void (*destroy)(void *data));
void slist_destroy(singly_list *list);
int  slist_insert_next(singly_list *list, singly_list_element *element, const void *data);
int  slist_remove_next(singly_list *list, singly_list_element *element, void **data);

#define slist_size(list) ((list)->size)
#define slist_head(list) ((list)->head)
#define slist_tail(list) ((list)->tail)
#define slist_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define slist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define slist_data(element) ((element)->data)
#define slist_next(element) ((element)->next)

#endif
