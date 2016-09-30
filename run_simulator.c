#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "simulator.h"
const double INTERVAL_E = 10.0;		//mean interarrival time (A)
const double DURATION_E = 10.0;		//mean service time (S)
int PART_NUM = 500;

double urand() {
  return (double)rand() / RAND_MAX;
}

double randexp() {
  double d = -(log(1.0 - urand()));
  return d;
}


int main() {
  srand(time(NULL));
  int count=0;
  double in_sys_time, delay, sum_sys=0, sum_delay=0;
  simulator* a_sim = create_simulator();
  for (int i = 0; i < PART_NUM; ++i) {
    next_part(a_sim, INTERVAL_E * randexp(),DURATION_E * randexp());
  }
  while(!is_empty_pq(a_sim->event_pq)) {
    process_event(a_sim);
  }

  printf("Part#\t    Time_in_the_System\t      Queuing Delay\t    Total Serv.Time\n");
  printf("---------------------------------------------------------------------------------\n");
  while(!is_empty_queue(a_sim->state_queues[SINK])) {
    part* p = dequeue(a_sim->state_queues[SINK]);
    //time in the system for each part
    in_sys_time = p->schedule_time[SINK] - p->schedule_time[SOURCE];
    delay = in_sys_time - p->process_duration;

    sum_sys += in_sys_time;
    sum_delay += delay;
    printf(" %d  \t\t%f\t\t%f\t\t%f\n", ++count, in_sys_time, delay, p->process_duration);

  }
    printf("\nAverage time in the system:\t%f\n", (double)sum_sys/PART_NUM);
    printf("Average queuing delay:\t\t%f\n", (double)sum_delay/PART_NUM);

    delete_simulator(a_sim);

}

