#ifndef _PART
#define _PART
const int STATE_NUM = 5;
typedef enum {SOURCE = 0, STATE1, STATE2, STATE3, SINK} state;

struct part {
  state s; // part in which state
  double process_duration;
  double schedule_time[STATE_NUM];
  double finish_time[STATE_NUM];
};
#endif
