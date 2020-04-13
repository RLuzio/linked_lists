//Singly linked list code

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "slist.h"
#include "utils.c"

//snode
typedef struct snode snode;
struct snode {
  int data;
  snode* next;
};

snode* snode_create(int data, snode* next) {
  snode* p = (snode*)malloc(sizeof(snode));
  p->data = data;
  p->next = next;

  return p;
}

//LINKED LIST
typedef struct slist slist;
struct slist {
  snode* head;
  snode* tail;
  size_t size;
};

slist* slist_create() {
  slist* p = (slist*)malloc(sizeof(slist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;

  return p;
}

int slist_front(slist* list){
  if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  return list->head->data;
}

int slist_back(slist* list){
  if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  return list->tail->data;
}

void slist_popfront(slist* list) {
  if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  snode* p = list->head;
  list->head = list->head->next;
  free(p);
  --list->size; //IS THIS RIGHT?
}

void slist_popback(slist* list){
  if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  if (list->size == 1) { slist_popfront(list); return; }

  snode* p = list->head;
  snode* prev;
  while(p->next != NULL) { prev = p; p = p->next; }
  prev->next = NULL;
  free(p);
  list->tail = prev;
  --list->size;
}

void slist_pushfront(slist* list, int num) {
  snode* p = snode_create(num, list->head); //(snode*)malloc(sizeof(snode));
  list->head = p;
  if (list->size == 0) { list-> tail = p; } //if(list->tail == NULL) { list->tail = p; }
  ++list->size;
}

void slist_pushback(slist* list, int num){
  if (list->size == 0) { slist_pushfront(list, num); return; }//if(list->head == NULL) { slist_pushfront(list, num); return; }
  snode* p = snode_create(num, NULL);//(snode*)malloc(sizeof(snode));
  list->tail->next = p;
  list->tail = p;
  ++list->size;
}

bool slist_empty(slist* list) { return list->size == 0; }

void slist_clear(slist* list) {
  while(!slist_empty(list)) {
    slist_popfront(list);
  }
}

size_t slist_size(slist* list) { return list->size; }

void slist_print(slist* list, const char* msg) {
  printf("%s\n", msg);
  if (slist_empty(list)) { printf("List is empty\n"); return; }

  snode* p = list->head;
  while (p != NULL) {
    printf("%d --> %p\n", p->data, p->next);
    p = p->next;
  }
}

// static const char* yesno(bool condition) {
//   return condition ? "YES" : "NO";
// }

static void checknull(slist* list) {    //Make sure the passed pointer is not NULL
  if (list == NULL) { fprintf(stderr, "NULL pointer\n"); exit(1); }
}

//TEST
void slist_frontback(slist* list, int front, int back) {
  printf("assert front of list is: %d\n", front);
  assert(slist_front(list) == front);
  printf("assert back of list is: %d\n", back);
  assert(slist_front(list) == back);
}

// void slist_test_once(slist* list, int start, int end, int step, void (*fp)(slist*, int)){
//   for(int i = start; i < end; i += step) { fp(list, i); }
//   slist_print(list, "list is created and is...\n");
//   printf("list size is: %zu\n", slist_size(list));
//   printf("list is empty? %s\n", tesorno(slist_empty(list)));
//
//   int firstadded = start;
//   int lastadded = start;
//   while(lastadded + step < end) { lastadded += step; }
//
//   //if (fp == slist_pushback) { slist_frontback(list, firstadded, lastadded); }
//   //if (fp == slist_pushback) { slist_frontback(list, lastadded, firstadded); }
//   if (fp == slist_pushback) {
//     printf("assert front of list is: %d\n", firstadded);
//     assert(slist_front(list) == firstadded);
//     printf("assert back of list is: %d\n", lastadded);
//     assert(slist_back(list) == lastadded);
//   }
//   if (fp == slist_pushfront) {
//     printf("assert front of list is: %d\n", lastadded);
//     assers(slist_front(list) == lastadded);
//     printf("assert back of list is: %d\n", firstadded);
//     assert(slist_back(list) == firstadded);
//   }
// }
//
// void slist_test() {
//   slist* list = slist_create();
//   // for (int i = 10; i < 50; i += 10) {
//   //   slist_pushfront(list, i);
//   // }
//   slist_test_once(list, 10, 50, 10, slist_pushfront);
//   slist_test_once(list, 20, 100, 40, slist_pushback);
//
//   slist_print(list, "list is created and is...");
//   printf("list size is: %zu\n", slist_size(list));
//   printf("list is empty? %d\n", slist_empty(list));
//
//   free(list);
// }

//MAIN
// int main(int argc, const char* argv[]) {
//   slist_test();
//   return 0;
// }
