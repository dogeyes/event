#ifndef _PQ_H
#define _PQ_H
#include <stdlib.h>

typedef int (*COMPARE_FUN)(ITEM_TYPE, ITEM_TYPE);

typedef struct pq_type {
  int capacity;
  int num;
  ITEM_TYPE* items;
  int (*compare)(ITEM_TYPE, ITEM_TYPE);
} pq;

pq* create_pq(int capacity, COMPARE_FUN compare) {
  pq* a_pq = (pq*)malloc(sizeof(pq));
  a_pq->capacity = capacity;
  a_pq->num = 0;
  // start from 1, left is 2*current, right is 2*current+1
  a_pq->items = (ITEM_TYPE*)malloc(sizeof(ITEM_TYPE) * (capacity + 1));
  a_pq->compare = compare;
  return a_pq;
}

pq* add_item(pq* a_pq, ITEM_TYPE item) {
  int cur_pos = ++a_pq->num;
  a_pq->items[cur_pos] = item;
  while(cur_pos > 1) {
    if (a_pq->compare(item, a_pq->items[cur_pos / 2]) < 0) {
      a_pq->items[cur_pos] = a_pq->items[cur_pos / 2];
      a_pq->items[cur_pos / 2] = item;
      cur_pos = cur_pos / 2;
    } else {
      break;
    }
  }
  return a_pq;
}

ITEM_TYPE pop_item(pq* a_pq) {
  ITEM_TYPE item = a_pq->items[1];
  int cur_pos = 1;
  a_pq->items[cur_pos] = a_pq->items[a_pq->num--];
  while(2 * cur_pos <= a_pq->num) {
    int min_pos = cur_pos;
    if (a_pq->compare(a_pq->items[min_pos], a_pq->items[cur_pos * 2]) > 0) {
      min_pos = cur_pos * 2;
    }
    if (cur_pos * 2 + 1 <= a_pq->num &&
        a_pq->compare(a_pq->items[min_pos], a_pq->items[cur_pos * 2 + 1]) > 0) {
      min_pos = cur_pos * 2 + 1;
    }
    if (min_pos == cur_pos) {
      break;
    }
    ITEM_TYPE tmp = a_pq->items[cur_pos];
    a_pq->items[cur_pos] = a_pq->items[min_pos];
    a_pq->items[min_pos] = tmp;
    cur_pos = min_pos;
  }
  return item;
}

int is_emtpy_pq(pq* a_pq) {
  return a_pq->num == 0;
}

//can only delete empty pq;
void delete_pq(pq* a_pq) {
  free(a_pq->items);
  free(a_pq);
}
#endif
