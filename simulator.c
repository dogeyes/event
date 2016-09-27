#include <assert.h>
#include <stdlib.h>
#include "part.h"
#include "event.h"
#define ITEM_TYPE event*
#define NODE_VALUE_TYPE part*
#include "pq.h"
#include "queue.h"

const int MAX_EVENT_QUEUE = 100000;

struct simulator{
  queue* state_queues[STATE_NUM];
  double finish_times[STATE_NUM];
  pq* event_pq;
  double time;
};

double max(double a, double b) {
  return a > b? a: b;
}

simulator* create_simulator() {
  simulator* a_sim = (simulator*)malloc(sizeof(simulator));
  for (int i = 0; i < STATE_NUM; ++i) {
    a_sim->state_queues[i] = create_queue();
    a_sim->finish_times[i] = 0;
  }
  a_sim->event_pq = create_pq(MAX_EVENT_QUEUE, event_compare);
  a_sim->time = 0;
  return a_sim;
}

void delete_simulator(simulator* a_sim) {
  while(!is_empty_queue(a_sim->state_queues[SINK])) {
    part* p = dequeue(a_sim->state_queues[SINK]);
    free(p);
  }
  for(int i = 0; i < STATE_NUM; ++i) {
    delete_queue(a_sim->state_queues[i]);
  }
  delete_pq(a_sim->event_pq);
  free(a_sim);
  a_sim = NULL;
}

part* next_part(simulator* a_sim, double interval, double duration) {
  part* p = (part*)malloc(sizeof(part));
  p->s = SOURCE;
  p->schedule_time[SOURCE] = max(a_sim->time, a_sim->finish_times[SOURCE])
      + interval;
  p->finish_time[SOURCE] = p->schedule_time[SOURCE];
  a_sim->finish_times[SOURCE] = p->schedule_time[SOURCE];
  p->process_duration = duration;
  event* e = create_event(p->schedule_time[SOURCE], p);
  add_item(a_sim->event_pq, e);
  enqueue(a_sim->state_queues[SOURCE], p);
  return p;
}

state process_event(simulator* a_sim) {
  event* e = pop_item(a_sim->event_pq);
  part* p = e->p;
  a_sim->time = e->deadline;
  free(e);
  e = NULL;
  part* de_p = dequeue(a_sim->state_queues[p->s]);
  assert(p == de_p);
  // part go to next state
  p->s =(state)(p->s + 1);
  if (p->s == SINK) {
    p->schedule_time[SINK] = a_sim->time;
    p->finish_time[SINK] = a_sim->time;
    return SINK;
  }

  p->schedule_time[p->s] = max(a_sim->time, a_sim->finish_times[p->s]);
  p->finish_time[p->s] = p->schedule_time[p->s] + p->process_duration;
  a_sim->finish_times[p->s] = p->finish_time[p->s];
  e = create_event(p->finish_time[p->s], p);
  add_item(a_sim->event_pq, e);
  enqueue(a_sim->state_queues[p->s], p);
  return p->s;
}
