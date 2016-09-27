#ifndef _EVENT
#define _EVENT
#include "part.h"
struct event {
  double deadline;
  part *p;
};

int event_compare(event* event1, event* event2) {
  return event1->deadline - event2->deadline;
}

event* create_event(double deadline, part* p) {
  event* e = (event*)malloc(sizeof(event));
  e->deadline = deadline;
  e->p = p;
  return e;
}
#endif
