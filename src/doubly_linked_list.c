#include <stdlib.h>
#include <string.h>

#include "doubly_linked_list.h"

void dlist_initialize(doubly_list *list, void (*destroy)(void *data)) {
  list -> size = 0;
  list -> destroy = destroy;
  list -> head = NULL;
  list -> tail = NULL;

  return;
}

void dlist_destroy(doubly_list *list) {
  void *data;

  /* Remove elements */
  while(dlist_size(list) > 0) {
    if(dlist_remove(list, dlist_tail(list), (void **)&data) == 0 &&
       list->destroy != NULL) {
      /* Call function for free allocated data */
      list->destroy(data);
    }
  }

  /* Clear structure */
  memset(list, 0, sizeof(doubly_list));

  return;
}

int  dlist_insert_prev(doubly_list *list, doubly_list_element *element, const void *data) {
  doubly_list_element *new_element;

  /* Allow NULL only when list is empty */
  if(element == NULL && dlist_size(list) != 0)
    return -1;

  /* Allocate memory for new element */
  if((new_element = (doubly_list_element *)malloc(sizeof(doubly_list_element))) == NULL)
    return -1;

  /* Insert element */
  new_element->data = (void *)data;

  if(dlist_size(list) == 0) {
    /* Insert when list is empty */
    list->head = new_element;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = new_element;
  } else {
    /* Insert when list is not empty */
    new_element->prev = element->prev;
    new_element->next = element;
    
    if(element->prev == NULL)
      list->head = new_element;
    else
      element->prev->next = new_element;

    element->prev = new_element;
  }

  /* Update list size */
  list->size++;

  return 0;
}

int  dlist_insert_next(doubly_list *list, doubly_list_element *element, const void *data) {
  doubly_list_element *new_element;

  /* Allow NULL only when list is empty */
  if(element == NULL && dlist_size(list) != 0)
    return -1;

  /* Allocate memory for new element */
  if((new_element = (doubly_list_element *)malloc(sizeof(doubly_list_element))) == NULL)
    return -1;

  /* Insert element */
  new_element->data = (void *)data;

  if(dlist_size(list) == 0) {
    /* Insert when list is empty */
    list->head = new_element;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = new_element;
  } else {
    /* Insert when list is not empty */
    new_element->prev = element;
    new_element->next = element->next;
    
    if(element->next == NULL)
      list->tail = new_element;
    else
      element->next->prev = new_element;

    element->next = new_element;
  }

  /* Update list size */
  list->size++;

  return 0;
}

int  dlist_remove(doubly_list *list, doubly_list_element *element, void **data) {
  /* Avoid NULL element and removal from empty list */
  if(element == NULL && dlist_size(list) != 0)
    return -1;
  
  /* Remove element */
  *data = element->data;

  if(element == list->head) {
    /* Remove from head */
    list->head = element->next;

    if(list->head == NULL)
      list->tail = NULL;
    else
      element->next->prev = NULL;
  } else {
    /* Remove not from head */
    element->prev->next = element->next;
    if(element->next == NULL)
      list->tail = element->prev;
    else
      element->next->prev = element->prev;
  }
  
  /* Free old element storage */
  free(element);

  /* Update list size */
  list->size--;

  return 0;
}
