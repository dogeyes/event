#include "event.h"
#include "gtest/gtest.h"

TEST(event, compare) {
  event* e1 = create_event(0.01, NULL);
  event* e2 = create_event(0.02, NULL);
  EXPECT_TRUE(event_compare(e1, e2) < 0);
  EXPECT_TRUE(event_compare(e2, e1) > 0);

}
