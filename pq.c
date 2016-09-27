struct pq {
  int capacity;
  int num;
  ITEM_TYPE* items;
  int (*compare)(ITEM_TYPE, ITEM_TYPE);
};

pq* create_pq(int capacity, int(*compare)(ITEM_TYPE, ITEM_TYPE)) {
  pq* a_pq = (pq*)malloc(sizeof(pq));
  a_pq.capacity = capacity;
  a_pq.num = 0;
  a_pq.items = (ITEM_TYPE*)malloc(sizeof(ITEM_TYPE) * capacity);
  a_pq.compare = compare;
  return a_pq
}

pq* add_item(pq* a_pq, ITEM_TYPE item) {
  int cur_pos = a_pq.num;
  a_pq.num++;
  while(cur_pos >0) {
    a_pq.items[cur_pos] = item;
    if (a_pq.compare(item, a_pq.items[cur_pos / 2]) < 0) {
      a_pq.items[cur_pos] = a_pq.items[cur_pos / 2];
      a_pq.items[cur_pos / 2] = item;
      cur_pos = cur_pos / 2;
    } else {
      break;
    }
  }
  return a_pq;
}

ITEM_TYPE pop_item(pq a_pq) {
  ITEM_TYPE item = a_pq.items[0];
  a_pq.items[0] = a_pq.items[--a_pq.num];
  int cur_pos = 0;
  while(2 * cur_pos < a_pq.num) {
    int min_pos = cur_pos;
    if (a_pq.compare(a_pq.items[min_pos], a_pa.items[cur_pos * 2]) > 0) {
      min_pos = cur_pos * 2;
    }
    if (cur_pos * 2 + 1 < a_pq.num &&
        a_pq.compare(a_pq.items[min_pos], a_pa.items[cur_pos * 2 + 1]) > 0) {
      min_pos = cur_pos * 2 + 1;
    }
    if (min_pos == cur_pos) {
      break;
    }
    a_pq.items[cur_pos] = a_pq.items[min_pos];
    a_pq.items[min_pos] = item;
    cur_pos = min_pos;
  }
  return item;
}
