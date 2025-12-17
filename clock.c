#include "clock.h"
#include "timer.h"
#include <time.h>
#include <stdbool.h>

static SoftwareTimer clock_timer;
Time current_time;

// 获取系统时间
Time get_system_time(void) {
    time_t t;
    struct tm *tm_info;
    // 获取当前系统时间（自1970年起的秒数）
    time(&t);
    // 将time_t时间转换为本地时间并分解
    tm_info = localtime(&t);
    // 提取年月日时分秒为int类型
    int year  = tm_info->tm_year + 1900; // 年份要加1900
    int month = tm_info->tm_mon + 1;     // 月份要加1 (0~11 -> 1~12)
    int day   = tm_info->tm_mday;
    int hour  = tm_info->tm_hour;
    int min   = tm_info->tm_min;
    int sec   = tm_info->tm_sec;
    // 转换为结构体并返回
    Time system_time;
    system_time.year = year;
    system_time.month = month;
    system_time.day = day;
    system_time.hour = hour;
    system_time.minute = min;
    system_time.second = sec;
    return system_time;
}

// 是否闰年
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 该月有几天
int days_in_month(int year, int month) {
    static const int days_per_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days_per_month[month - 1];
}

// 初始化时间
void clock_init(void) {
    software_timer_init(&clock_timer, 10000);
    current_time = get_system_time();
}

// 传入公历年月日，返回0~6分别对应周一~周日
int get_weekday(int y, int m, int d) {
    if(m==1 || m==2) {
        m += 12;
        y -= 1;
    }
    int w = (d + 26*(m+1)/10 + y + y/4 + 6*y/100 + y/400) % 7;
    return w;
}

void clock_process(void) {
    if (software_timer_expired(&clock_timer)) {
        current_time.second++;
        if (current_time.second >= 60) {
            current_time.second = 0;
            current_time.minute++;
            if (current_time.minute >= 60) {
                current_time.minute = 0;
                current_time.hour++;
                if (current_time.hour >= 24) {
                    current_time.hour = 0;
                    current_time.day++;
                    int dim = days_in_month(current_time.year, current_time.month);
                    if (current_time.day > dim) {
                        current_time.day = 1;
                        current_time.month++;
                        if (current_time.month > 12) {
                            current_time.month = 1;
                            current_time.year++;
                        }
                    }
                }
            }
        }
    }
}
    