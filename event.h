#ifndef _EVENT
#define _EVENT
#include <stdlib.h>
#include "part.h"
struct event {
  double deadline;
  part *p;
};

int event_compare(event* event1, event* event2) {
  double a = event1->deadline - event2->deadline;
  if (a > 0) {
    return 1;
  }
  if (a < 0) {
    return -1;
  }
  return 0;
}

event* create_event(double deadline, part* p) {
  event* e = (event*)malloc(sizeof(event));
  e->deadline = deadline;
  e->p = p;
  return e;
}
#endif
