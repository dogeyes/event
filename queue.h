#ifndef _QUEUE
#define _QUEUE
#include <stdlib.h>
struct node {
  struct node* next;
  struct node* prev;
  NODE_VALUE_TYPE value;
};

struct queue {
  struct node* head;
  struct node* tail;
  int num;
};

queue* create_queue() {
  queue* q = (queue*)malloc(sizeof(queue));
  // head is a dummy node;
  node* head = (node*)malloc(sizeof(node));
  head->prev = (node*)NULL;
  head->next = (node*)NULL;
  q->head = head;
  q->tail = head;
  q->num = 0;
  return q;
}

void enqueue(queue* q, NODE_VALUE_TYPE v) {
  node* n = (node*)malloc(sizeof(node));
  n->value = v;
  q->tail->next = n;
  n->prev = q->tail;
  n->next = NULL;
  q->tail = n;
  q->num++;
}

NODE_VALUE_TYPE dequeue(queue* q) {
  node* n = q->head->next;
  q->head->next = n->next;
  if (n == q->tail) {
    q->tail = q->head;
  } else {
    n->next->prev = q->head;
  }
  NODE_VALUE_TYPE v = n->value;
  q->num--;
  free(n);
  return v;
}
#endif
