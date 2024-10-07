#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

#define MAX_NAME_LEN 20

typedef SList Deque;
typedef enum{F = 0, T = 1} Bool;

void pushBack(Deque* q, char* data) {
  insertTail(q, data);
}

void pushFront(Deque* q, char* data) {
  insertHead(q, data);
}

char* popBack(Deque* q) {
  char* poppedName;
  poppedName = removeTail(q);
  pushFront(q, poppedName);
  return poppedName;
}

char* popFront(Deque* q) {
  char* poppedName;
  poppedName = removeHead(q);
  pushBack(q, poppedName);
  return poppedName;
}


int main() {
  Deque q = {NULL, NULL};
  FILE* fp = fopen("deque.txt", "r");
  char input[MAX_NAME_LEN];
  Bool done = F;

    if(fp == NULL){
        fprintf(stderr, "Cannot open %s.\n", "deque.txt");
        exit(1);
    }

    //Source: CSE240F24_A6.pdf
    while(!done) {
        char* name = malloc(MAX_NAME_LEN);
        if(fscanf(fp, "%s", name) == 1) {
            pushBack(&q, name);
        }
        else {
            done = T;
        }
    }

    printf("To scroll through the names type\n");
    printf("f: forwards, b: backwards, q: quit\n");
    scanf("%s", input);

  while(strcmp(input, "q") != 0) {
    char* name;
    if(strcmp(input, "f") == 0) {
      name = popFront(&q);
      printf("%s\n", name);
    }

    if(strcmp(input, "b") == 0) {
      name = popBack(&q);
      printf("%s\n", name);
    }
    scanf("%s", input);
  }

  printf("Bye!\n");

  fclose(fp);

  return 0;
}
