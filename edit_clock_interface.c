#include "edit_clock_interface.h"
#include "timer.h"
#include "clock.h"
#include "key.h"
#include "ui.h"

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
    // 0.3s闪烁一次
    software_timer_init(&twinkle_timer, 3000);
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

// 设置当前光标位置的数值
void edit_clock_interface_set_number(int number) {
    switch(edit_clock_interface_cursor) {
        case YEAR4:
            temp_time.year = number * 1000 + temp_time.year % 1000;
            break;
        case YEAR3:
            temp_time.year = (temp_time.year / 1000) * 1000 + number * 100 + temp_time.year % 100;
            break;
        case YEAR2:
            temp_time.year = (temp_time.year / 100) * 100 + number * 10 + temp_time.year % 10;
            break;
        case YEAR1:
            temp_time.year = (temp_time.year / 10) * 10 + number;
            break;
        case MONTH2:
            temp_time.month = number * 10 + temp_time.month % 10;
            break;
        case MONTH1:
            temp_time.month = (temp_time.month / 10) * 10 + number;
            break;
        case DAY2:
            temp_time.day = number * 10 + temp_time.day % 10;
            break;
        case DAY1:
            temp_time.day = (temp_time.day / 10) * 10 + number;
            break;
        case HOUR2:
            temp_time.hour = number * 10 + temp_time.hour % 10;
            break;
        case HOUR1:
            temp_time.hour = (temp_time.hour / 10) * 10 + number;
            break;
        case MINUTE2:
            temp_time.minute = number * 10 + temp_time.minute % 10;
            break;
        case MINUTE1:
            temp_time.minute = (temp_time.minute / 10) * 10 + number;
            break;
        case SECOND2:
            temp_time.second = number * 10 + temp_time.second % 10;
            break;
        case SECOND1:
            temp_time.second = (temp_time.second / 10) * 10 + number;
            break;
        default:
            break;
    }
}

void edit_clock_interface_confirm(void) {
    if (is_time_valid(temp_time)) {
        current_time = temp_time;
        change_ui(EDIT_SUCCESS_ANIMATION);
    }
    else {
        change_ui(EDIT_INVALID_ANIMATION);
    }
}

void edit_clock_interface_key(int key) {
    switch(key) {
        case F1:
            edit_clock_interface_set_number(1);
            edit_clock_interface_move_cursor_right();
            break;
        case F2:
            edit_clock_interface_set_number(2);
            edit_clock_interface_move_cursor_right();
            break;
        case F3:
            edit_clock_interface_set_number(3);
            edit_clock_interface_move_cursor_right();
            break;
        case F4:
            edit_clock_interface_set_number(4);
            edit_clock_interface_move_cursor_right();
            break;
        case F5:
            edit_clock_interface_set_number(5);
            edit_clock_interface_move_cursor_right();
            break;
        case F6:
            edit_clock_interface_set_number(6);
            edit_clock_interface_move_cursor_right();
            break;
        case F7:
            edit_clock_interface_set_number(7);
            edit_clock_interface_move_cursor_right();
            break;
        case F8:
            edit_clock_interface_set_number(8);
            edit_clock_interface_move_cursor_right();
            break;
        case F9:
            edit_clock_interface_set_number(9);
            edit_clock_interface_move_cursor_right();
            break;
        case F10:
            edit_clock_interface_set_number(0);
            edit_clock_interface_move_cursor_right();
            break;
        case F1_LONG:
            edit_clock_interface_confirm();
            break;
        case F6_LONG:
            edit_clock_interface_move_cursor_left();
            break;
        case F7_LONG:
            edit_clock_interface_move_cursor_right();
            break;
        case F5_LONG:
            change_ui(CLOCK_INTERFACE);
            break;
        default:
            break;
    }
}

void edit_clock_interface_content(char *line1, char *line2) {
    sprintf(line1, "%04d-%02d-%02d      ", temp_time.year, temp_time.month, temp_time.day);
    sprintf(line2, "%02d:%02d:%02d      ", temp_time.hour, temp_time.minute, temp_time.second);
    line1[15] = 0x01; // 上箭头
    line2[15] = 0x02; // 下箭头
    if (current_status == 0) {
        switch(edit_clock_interface_cursor) {
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