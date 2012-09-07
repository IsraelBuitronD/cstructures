#include <stdlib.h>
#include <string.h>

#include "singly_linked_list.h"

void slist_initialize(singly_list *list, void (*destroy)(void *data)) {
  list -> size = 0;
  list -> destroy = destroy;
  list -> head = NULL;
  list -> tail = NULL;

  return;
}

void slist_destroy(singly_list *list) {
  void *data;

  /* Remove elements */
  while(slist_size(list) > 0) {
    if(slist_remove_next(list, NULL, (void **)&data) == 0 &&
       list->destroy != NULL) {
      /* Call function for free allocated data */
      list->destroy(data);
    }
  }

  /* Clear structure */
  memset(list, 0, sizeof(list));

  return;
}

int slist_insert_next(singly_list *list, singly_list_element *element, const void *data) {
  singly_list_element *new_element;
  
  /* Allocate memory for new element */
  if((new_element = (singly_list_element *)malloc(sizeof(singly_list_element))) == NULL)
    return -1;

  /* Insert element */
  new_element->data = (void *)data;
  if(element == NULL) {
    /* Insert at head */
    if(slist_size(list) == 0)
      list->tail = new_element;

    new_element->next = list->head;
    list->head = new_element;
  } else {
    /* Insert not at head */
    if(element->next == NULL)
      list->tail = new_element;

    new_element->next = element->next;
    element->next = new_element;
  }

  /* Update list size */
  list->size++;

  return 0;
}

int slist_remove_next(singly_list *list, singly_list_element *element, void **data) {
  singly_list_element *old_element;

  /* Avoid remove from empty list */
  if(slist_size(list) == 0)
    return -1;

  /* Remove element */
  if(element == NULL) {
    /* Remove from head */
    *data = list->head->data;
    old_element = list->head;
    list->head = list->head->next;

    if(slist_size(list) == 1)
      list->tail = NULL;
  } else {
    /* Remove not from head */
    if(element->next == NULL)
      return -1;
    
    *data = element->next->data;
    old_element = element->next;
    element->next = element->next->next;

    if(element->next == NULL)
      list->tail = element;
  }
  
  /* Free old element storage */
  free(old_element);

  /* Update list size */
  list->size--;

  return 0;
}
