#ifndef TIMER_H_
#define TIMER_H_
#include <stdbool.h>

// 全局计时器，毫秒级
extern volatile unsigned int global_timer;

// 软件定时器（记录上次时间和触发的时间间隔）
typedef struct {
    unsigned int last_time;
    unsigned int interval;
}SoftwareTimer;

// 初始化系统定时器，并设置CPU定时器中断，模拟1000Hz时钟
void global_timer_init(void);

// 初始化软件定时器
void software_timer_init(SoftwareTimer *t, unsigned int interval);

// 判断是否到期，如果到期，更新软件定时器的last，并返回true
bool software_timer_expired(SoftwareTimer *t);

#endif /*TIMER_H_*/
