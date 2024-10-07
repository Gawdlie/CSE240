#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"


void insertHead(SList* list, char* data) {
  struct node* newHead = malloc(sizeof(struct node));

  newHead->data = strdup(data);
  newHead->next = list->head;
  list->head = newHead;

  if(list->tail == NULL) {
    list->tail = newHead;
    list->tail->next = NULL;
  }
}

char* removeHead(SList* list) {
  char* tempData = list->head->data;

  if(list->head == NULL) {
    return NULL;
  }

  if(list->head->next == NULL) {
    free(list->head);
    return tempData;
  }

  list->head = list->head->next;

  return tempData;
}

void insertTail(SList* list, char* data) {
  struct node* newTail = malloc(sizeof(struct node));

  if(list->head == NULL) {
    list->head = newTail;
    list->tail = newTail;
  }

  newTail->data = strdup(data);
  newTail->next = NULL;
  list->tail->next = newTail;
  list->tail = newTail;
}

char* removeTail(SList* list) {
  struct node* current = list->head;
  char* tailData = list->tail->data;

  if(list->head == NULL) {
    return NULL;
  }

  if(list->head == list->tail) {
    free(list->tail);
    return tailData;
  }


  while(current->next->next != NULL) {
    current = current->next;
  }

  current->next = NULL;
  list->tail = current;

 return tailData;
}

