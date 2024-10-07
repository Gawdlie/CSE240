#ifndef slist_h
#define slist_h

#include <stdio.h>

struct node {
  char* data;
  struct node* next;
};

typedef struct singlylinkedlist {
  struct node* head;
  struct node* tail;
} SList;

void insertHead(SList* list, char* data);
char* removeHead(SList* list);
void insertTail(SList* List, char* data);
char* removeTail(SList* list);

#endif
