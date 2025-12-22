#ifndef CLOCK_H_
#define CLOCK_H_
#include <stdbool.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
}Time;

extern Time current_time;

// 初始化时间
void clock_init(void);

// 时间流动
void clock_process(void);

// 计算周几
int get_weekday(int y, int m, int d);

bool is_time_valid(Time t);

#endif /*CLOCK_H_*/
