#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simulator.c"
const double INTERVAL_E = 10.0;
const double DURATION_E = 20.0;

double urand() {
  return rand() / RAND_MAX;
}

double randexp() {
  return -(log(1.0 - urand()));
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
  // TODO
  delete_simulator(a_sim);
}