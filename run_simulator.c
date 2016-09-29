#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "simulator.c"
const double INTERVAL_E = 10.0;
const double DURATION_E = 20.0;

double urand() {
  return (double)rand() / RAND_MAX;
}

double randexp() {
  double d = -(log(1.0 - urand()));
  return d;
}


int main() {
  srand(time(NULL));
  int part_num = 20;
  simulator* a_sim = create_simulator();
  for (int i = 0; i < part_num; ++i) {
    next_part(a_sim,
              INTERVAL_E * randexp(),
              DURATION_E * randexp());
  }
  while(!is_emtpy_pq(a_sim->event_pq)) {
    process_event(a_sim);
  }

  // calculate all the statics
  while(!is_empty_queue(a_sim->state_queues[SINK])) {
    part* p = dequeue(a_sim->state_queues[SINK]);
    printf("%f->%f %f->%f %f->%f %f->%f %f->%f\n",
           p->schedule_time[SOURCE], p->finish_time[SOURCE],
           p->schedule_time[STATE1], p->finish_time[STATE1],
           p->schedule_time[STATE2], p->finish_time[STATE2],
           p->schedule_time[STATE3], p->finish_time[STATE3],
           p->schedule_time[SINK], p->finish_time[SINK]);
  }

  printf("hello");
  delete_simulator(a_sim);
}
