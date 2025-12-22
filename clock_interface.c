#include "clock_interface.h"
#include "clock.h"
#include "key.h"
#include "ui.h"
#include <stdio.h>

void clock_interface_content(char *line1, char *line2) {
    char *weekday_name[] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    int weekday = get_weekday(current_time.year, current_time.month, current_time.day);
    sprintf(line1, "%04d-%02d-%02d      ", current_time.year, current_time.month, current_time.day);
    sprintf(line2, "%02d:%02d:%02d  %s   ", current_time.hour, current_time.minute, current_time.second, weekday_name[weekday]);
    line2[15] = 0x02;
}

void clock_interface_key(int key) {
    switch(key) {
        case F10:
            change_ui(EDIT_CLOCK_INTERFACE);
            break;
        default:
            break;
    }
}