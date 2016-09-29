#define ITEM_TYPE int
#include "pq.h"
#include "gtest/gtest.h"


ITEM_TYPE compare(ITEM_TYPE a, ITEM_TYPE b) {
  return a - b;
}

TEST(pq_test, Create) {
  pq* a_pq = create_pq(compare);
  EXPECT_EQ(0, a_pq->num);
  EXPECT_EQ(compare, a_pq->compare);
}

TEST(pq_test, PopItem) {
  pq* a_pq = create_pq(compare);
  ITEM_TYPE init_array[] = {
    0, 4, 3, 5, 1, 7, 2, 6, 8, 9, 0
  };
  for(int i = 0; i < 10; ++i) {
    add_item(a_pq, init_array[i]);
  }

  int num = 10;
  for(int i = 0; i < 10; ++i) {
    ITEM_TYPE item = pop_item(a_pq);
    num--;
    EXPECT_EQ(num, a_pq->num);
    EXPECT_EQ(i, item);
  }
}

TEST(pq_test, IsEmpty) {
  pq* a_pq = create_pq(compare);
  EXPECT_TRUE(is_emtpy_pq(a_pq));
  add_item(a_pq, 1);
  EXPECT_FALSE(is_emtpy_pq(a_pq));
}
