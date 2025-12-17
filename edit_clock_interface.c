#include "edit_clock_interface.h"
#include "timer.h"
#include "clock.h"

#define YEAR4 0
#define YEAR3 1
#define YEAR2 2
#define YEAR1 3
#define MONTH2 4
#define MONTH1 5
#define DAY2 6
#define DAY1 7
#define HOUR2 8
#define HOUR1 9
#define MINUTE2 10
#define MINUTE1 11
#define SECOND2 12
#define SECOND1 13

// 光标闪烁频率
SoftwareTimer twinkle_timer;
// 当前光标位置
int edit_clock_interface_cursor;
// 当前闪烁状态（0暗1亮）
int current_status;
// 待修改时钟
Time temp_time;

void edit_clock_interface_init(void) {
    // 0.7s闪烁一次
    software_timer_init(&twinkle_timer, 7000);
    // 当前光标位置为年份最高位
    edit_clock_interface_cursor = YEAR4;
    current_status = 0;
    // 获得当前时钟
    temp_time = current_time;
}

// 光标左移
void edit_clock_interface_move_cursor_left(void) {
    if (edit_clock_interface_cursor == YEAR4)
        edit_clock_interface_cursor = SECOND1;
    else
        edit_clock_interface_cursor--;
}

// 光标右移
void edit_clock_interface_move_cursor_right(void) {
    if (edit_clock_interface_cursor == SECOND1)
        edit_clock_interface_cursor = YEAR4;
    else
        edit_clock_interface_cursor++;
}

void edit_clock_interface_content(char *line1, char *line2) {
    sprintf(line1, "%04d-%02d-%02d", current_time.year, current_time.month, current_time.day);
    sprintf(line2, "%02d:%02d:%02d", current_time.hour, current_time.minute, current_time.second);
    if (current_status == 0) {
        switch(current_status) {
            case YEAR4:
                line1[0] = 0x20;
                break;
            case YEAR3:
                line1[1] = 0x20;
                break;
            case YEAR2:
                line1[2] = 0x20;
                break;
            case YEAR1:
                line1[3] = 0x20;
                break;
            case MONTH2:
                line1[5] = 0x20;
                break;
            case MONTH1:
                line1[6] = 0x20;
                break;
            case DAY2:
                line1[8] = 0x20;
                break;
            case DAY1:
                line1[9] = 0x20;
                break;
            case HOUR2:
                line2[0] = 0x20;
                break;
            case HOUR1:
                line2[1] = 0x20;
                break;
            case MINUTE2:
                line2[3] = 0x20;
                break;
            case MINUTE1:
                line2[4] = 0x20;
                break;
            case SECOND2:
                line2[6] = 0x20;
                break;
            case SECOND1:
                line2[7] = 0x20;
                break;
            default:
                break;
        }
    }
    if (software_timer_expired(&twinkle_timer)) {
        if (current_status == 1)
            current_status = 0;
        else
            current_status = 1;
    }
}