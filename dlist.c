//Doubly linked list code

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dlist.h"
#include "utils.c"

//dnode
typedef struct dnode dnode;
struct dnode {
  int data;
  dnode* next;
  dnode* prev;
};

dnode* dnode_create(int data, dnode* next, dnode* prev) {
  dnode* p = (dnode*)malloc(sizeof(dnode));
  p->data = data;
  p->next = next;
  p->prev = prev;

  return p;
}

//LINKED LIST
typedef struct dlist dlist;
struct dlist {
  dnode* head;
  dnode* tail;
  size_t size;
};

dlist* dlist_create() {
  dlist* p = (dlist*)malloc(sizeof(dlist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;

  return p;
}

int dlist_front(dlist* list){
  if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  return list->head->data;
}

int dlist_back(dlist* list){
  if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  return list->tail->data;
}

void dlist_popfront(dlist* list) {
  if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  dnode* p = list->head;
  list->head = list->head->next;
  if(list->size != 1) { list->head->prev = NULL; }
  free(p);
  --list->size; //IS THIS RIGHT?
}

void dlist_popback(dlist* list){
  if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  if (list->size == 1) { dlist_popfront(list); return; }

  //dnode* prev = list->tail->prev;
  // prev->next = NULL;
  // free(list->tail);
  // list ->tail = prev;

  dnode* p = list->tail;
  list->tail = p->prev;
  free(p);
  list->tail->next = NULL;
  --list->size;
}

void dlist_pushfront(dlist* list, int num) {
  dnode* p = dnode_create(num, list->head, NULL); //(dnode*)malloc(sizeof(dnode));
  if(list->size != 0) { list->head->prev = p; }
  list->head = p;
  if (list->size == 0) {
    list-> tail = p;
    list->tail->prev = NULL;
  }
  ++list->size;
}

void dlist_pushback(dlist* list, int num){
  if (list->size == 0) { dlist_pushfront(list, num); return; }//if(list->head == NULL) { dlist_pushfront(list, num); return; }
  dnode* p = dnode_create(num, NULL, list->tail);//(dnode*)malloc(sizeof(dnode));
  list->tail->next = p;
  list->tail = p;
  ++list->size;
}

bool dlist_empty(dlist* list) { return list->size == 0; }

void dlist_clear(dlist* list) {
  while(!dlist_empty(list)) {
    dlist_popfront(list);
  }
}

size_t dlist_size(dlist* list) { return list->size; }

void dlist_print(dlist* list, const char* msg) {
  printf("%s\n", msg);
  if (dlist_empty(list)) { printf("List is empty\n"); return; }

  dnode* p = list->head;
  while (p != NULL) {
    printf("%p <-- %d (%p) --> %p\n", p->prev, p->data, p, p->next);
    p = p->next;
  }
}

// static const char* yesno(bool condition) {
//   return condition ? "YES" : "NO";
// }

// static void checknull(dlist* list) {    //Make sure the passed pointer is not NULL
//   if (list == NULL) { fprintf(stderr, "NULL pointer\n"); exit(1); }
// }


//TEST
// void dlist_frontback(dlist* list, int front, int back) {
//   printf("assert front of list is: %d\n", front);
//   assert(dlist_front(list) == front);
//   printf("assert back of list is: %d\n", back);
//   assert(dlist_front(list) == back);
// }
//
// void dlist_test_once(dlist* list, int start, int end, int step, void (*fp)(dlist*, int)){
//   for(int i = start; i < end; i += step) { fp(list, i); }
//   dlist_print(list, "list is created and is...\n");
//   printf("list size is: %zu\n", dlist_size(list));
//   printf("list is empty? %s\n", yesorno(dlist_empty(list)));
//
//   int firstadded = start;
//   int lastadded = start;
//   while(lastadded + step < end) { lastadded += step; }
//
//   //if (fp == dlist_pushback) { dlist_frontback(list, firstadded, lastadded); }
//   //if (fp == dlist_pushback) { dlist_frontback(list, lastadded, firstadded); }
//   if (fp == dlist_pushback) {
//     printf("assert front of list is: %d\n", firstadded);
//     assert(dlist_front(list) == firstadded);
//     printf("assert back of list is: %d\n", lastadded);
//     assert(dlist_back(list) == lastadded);
//   }
//   if (fp == dlist_pushfront) {
//     printf("assert front of list is: %d\n", lastadded);
//     assers(dlist_front(list) == lastadded);
//     printf("assert back of list is: %d\n", firstadded);
//     assert(dlist_back(list) == firstadded);
//   }
// }
//
// void dlist_test() {
//   dlist* list = dlist_create();
//   // for (int i = 10; i < 50; i += 10) {
//   //   dlist_pushfront(list, i);
//   // }
//   dlist_test_once(list, 10, 50, 10, dlist_pushfront);
//   dlist_test_once(list, 20, 100, 40, dlist_pushback);
//
//   dlist_print(list, "list is created and is...");
//   printf("list size is: %zu\n", dlist_size(list));
//   printf("list is empty? %d\n", dlist_empty(list));
//
//   free(list);
// }


// int dlist_front(dlist* list){
//   if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
//   return list->head->data;
// }
//
// int dlist_back(dlist* list){
//   if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
//   return list->tail->data;
// }
//
// void dlist_popfront(dlist* list) {
//   if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
//   dnode* p = list->head;
//   list->head = list->head->next;
//   head->prev = NULL;
//   free(p);
//   --list->size; //IS THIS RIGHT?
// }
//
// void dlist_popback(dlist* list){
//   if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
//   if (list->size == 1) { dlist_popfront(list); return; }
//
//   dnode* p = list->head;
//   while(p->next != list->tail) { p = p->next; }
//   p->next = NULL;
//   free(list->tail);
//   list->tail = p;
//   list->tail->next = NULL;
//   --list->size;
// }
//
// void dlist_pushfront(dlist* list, int num) {
//   dnode* p = dnode_create(num, list->head, NULL); //(dnode*)malloc(sizeof(dnode));
//   list->head = p;
//   if (list->size == 0) { list-> tail = p; } //if(list->tail == NULL) { list->tail = p; }
//   ++list->size;
// }
//
// void dlist_pushback(dlist* list, int num) {
//   if (list->size == 0) { dlist_pushfront(list, num); return; }//if(list->head == NULL) { dlist_pushfront(list, num); return; }
//   dnode* p = dnode_create(num, NULL, list->tail);//(dnode*)malloc(sizeof(dnode));
//   list->tail->next = p;
//   list->tail = p;
//   ++list->size;
// }
//
// void dlist_insert(dlist* list, int num, int pos) {
//   if (list->head == NULL) { fprintf(stderr, "List is empty, cannot insert\n"); }
//   if (list->size > pos) { fprintf(stderr, "Position does not exist in list\n"); }
//
//   int count = 1;
//   dnode* p = list->head;
//
//   while(count++ != pos) { p = p->next; }  //Gets us to the position before
//   dnode_create(num, p->next, p);
// }
//
// bool dlist_empty(dlist* list) { return list->size == 0; }
//
// void dlist_clear(dlist* list) {
//   while(!dlist_empty(list)) {
//     dlist_popfront(list);
//   }
// }
//
//
// size_t dlist_size(dlist* list) { return list->size; }
//
// void dlist_print(dlist* list, const char* msg) {
//   printf("%s\n", msg);
//   if (dlist_empty(list)) { printf("List is empty\n"); return; }
//
//   dnode* p = list->head;
//   while (p != NULL) {
//     printf("%d --> %p\n", p->data, p->next);
//     p = p->next;
//   }
// }
//
// //TEST
// void dlist_test() {
//   dlist* list = dlist_create();
//   for (int i = 10; i < 50; i += 10) {
//     dlist_pushfront(list, i);
//   }
//   dlist_print(list, "list is created and is...");
//   printf("list size is: %zu\n", dlist_size(list));
//   printf("list is empty? %d\n", dlist_empty(list));
//
//   free(list);
// }
//
// //MAIN
// int main(int argc, const char* argv[]) {
//   dlist_test();
//   return 0;
// }
