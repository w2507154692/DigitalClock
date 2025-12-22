#include "edit_invalid_animation.h"
#include "timer.h"
#include "ui.h"
#include <string.h>

// 动画持续时间
static SoftwareTimer duration_timer;
// 帧时间
static SoftwareTimer frame_timer;
// 当前动画状态
static int status;

void edit_invalid_animation_init(void) {
    // 动画持续3s
    software_timer_init(&duration_timer, 30000);
    // 帧时间0.5s
    software_timer_init(&frame_timer, 5000);
    // 当前状态
    status = 0;
}

void edit_invalid_animation_content(char *line1, char *line2) { 
    char c;
    switch(status) {
        case 0:
            c = 0x21; //感叹号
            break;
        case 1:
            c = 0x20; // 空格
            break;
        default:
            c = 0x20;
            break;
    }
    sprintf(line1, "%c%c%c INVALID %c%c%c%c", c, c, c, c, c, c, c);
    sprintf(line2, "%c%c%c%c%c EDIT %c%c%c%c%c", c, c, c, c, c, c, c, c, c, c);
    // 每过一帧时间状态切换
    if (software_timer_expired(&frame_timer)) {
        if (status == 1) {
            status = 0;
        }
        else
            status++;
    }
    // 动画结束，回到编辑
    if (software_timer_expired(&duration_timer)) {   
        change_ui(EDIT_CLOCK_INTERFACE);
    }
}