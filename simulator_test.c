#include "gtest/gtest.h"
#include "simulator.c"
#include "part.h"
#include "event.h"
#include "pq.h"
#include "queue.h"

TEST(simulator, Create) {
  simulator* a_sim = create_simulator();
  EXPECT_EQ(0, a_sim->time);
  EXPECT_TRUE(is_emtpy_pq(a_sim->event_pq));
  for (int i = 0; i < STATE_NUM; ++i) {
    EXPECT_TRUE(is_empty_queue(a_sim->state_queues[i]));
    EXPECT_EQ(0, a_sim->finish_times[i]);
  }
}

TEST(simulator, nextPart) {
  simulator* a_sim = create_simulator();
  a_sim->time = 100.0;
  part* p1 = next_part(a_sim, 10.0, 20.0);
  EXPECT_DOUBLE_EQ(20.0, p1->process_duration);
  part* p2 = next_part(a_sim, 30.0, 40.0);
  EXPECT_DOUBLE_EQ(40.0, p2->process_duration);
  event* e1 = pop_item(a_sim->event_pq);
  event* e2 = pop_item(a_sim->event_pq);
  EXPECT_DOUBLE_EQ(110.0, e1->deadline);
  EXPECT_EQ(p1, e1->p);
  EXPECT_DOUBLE_EQ(140.0, e2->deadline);
  EXPECT_EQ(p2, e2->p);
  EXPECT_EQ(p1, dequeue(a_sim->state_queues[SOURCE]));
  EXPECT_EQ(p2, dequeue(a_sim->state_queues[SOURCE]));
  EXPECT_DOUBLE_EQ(140.0, a_sim->finish_times[SOURCE]);
}

TEST(simulator, processOne) {
  simulator* a_sim = create_simulator();
  part* p1 = next_part(a_sim, 10.0, 20.0);
  while(!is_emtpy_pq(a_sim->event_pq)) {
    process_event(a_sim);
  }
  EXPECT_DOUBLE_EQ(10.0 + 20.0 * 3, a_sim->time);
  EXPECT_DOUBLE_EQ(10.0, p1->finish_time[SOURCE]);
  EXPECT_DOUBLE_EQ(30.0, p1->finish_time[STATE1]);
  EXPECT_DOUBLE_EQ(50.0, p1->finish_time[STATE2]);
  EXPECT_DOUBLE_EQ(70.0, p1->finish_time[STATE3]);
  EXPECT_DOUBLE_EQ(70.0, p1->finish_time[SINK]);
}

TEST(simulator, process) {
  simulator* a_sim = create_simulator();
  part* p1 = next_part(a_sim, 10.0, 40.0);
  part* p2 = next_part(a_sim, 30.0, 20.0);
  while(!is_emtpy_pq(a_sim->event_pq)) {
    process_event(a_sim);
  }
  EXPECT_DOUBLE_EQ(150.0, a_sim->time);
  EXPECT_DOUBLE_EQ(10.0, p1->finish_time[SOURCE]);
  EXPECT_DOUBLE_EQ(50.0, p1->finish_time[STATE1]);
  EXPECT_DOUBLE_EQ(90.0, p1->finish_time[STATE2]);
  EXPECT_DOUBLE_EQ(130.0, p1->finish_time[STATE3]);
  EXPECT_DOUBLE_EQ(130.0, p1->finish_time[SINK]);

  EXPECT_DOUBLE_EQ(40.0, p2->finish_time[SOURCE]);
  EXPECT_DOUBLE_EQ(70.0, p2->finish_time[STATE1]);
  EXPECT_DOUBLE_EQ(110.0, p2->finish_time[STATE2]);
  EXPECT_DOUBLE_EQ(150.0, p2->finish_time[STATE3]);
  EXPECT_DOUBLE_EQ(150.0, p2->finish_time[SINK]);
}
