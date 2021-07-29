
#ifndef STOP_WATCH_H_
#define STOP_WATCH_H_
// use in display number on 7-segments
void counter_wirte (unsigned int display, unsigned char current_time);
// use in display single row of number
void first_show(unsigned int display, unsigned int current_time);
// use in display multiple rows of data by apply first_show.
void multi_show(unsigned int display, unsigned int current_time);

void start_show(unsigned int display);
#endif
