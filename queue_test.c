#define NODE_VALUE_TYPE int
#include "queue.h"
#include "gtest/gtest.h"

TEST(queue_test, Create) {
  queue* q = create_queue();
  EXPECT_EQ(NULL, q->head->prev);
  EXPECT_EQ(NULL, q->head->next);
  EXPECT_EQ(q->tail, q->head);
  EXPECT_EQ(0, q->num);
}

TEST(queue_test, Enqueue) {
  queue* q = create_queue();
  enqueue(q, 1);
  EXPECT_EQ(NULL, q->head->prev);
  EXPECT_EQ(1, q->head->next->value);
  EXPECT_EQ(1, q->tail->value);
  enqueue(q, 2);
  EXPECT_EQ(1, q->head->next->value);
  EXPECT_EQ(2, q->tail->value);
}

TEST(queue_test, Dequeue) {
  queue* q = create_queue();
  enqueue(q, 1);
  EXPECT_EQ(NULL, q->head->prev);
  EXPECT_EQ(1, q->head->next->value);
  EXPECT_EQ(1, q->tail->value);
  enqueue(q, 2);
  EXPECT_EQ(1, q->head->next->value);
  EXPECT_EQ(2, q->tail->value);
  NODE_VALUE_TYPE v = dequeue(q);
  EXPECT_EQ(1, v);
  EXPECT_EQ(2, q->head->next->value);
  EXPECT_EQ(2, q->tail->value);
  EXPECT_EQ(q->head->next, q->tail);
  v = dequeue(q);
  EXPECT_EQ(2, v);
  EXPECT_EQ(q->head, q->tail);
}
