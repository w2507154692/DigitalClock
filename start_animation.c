#include "start_animation.h"
#include "timer.h"
#include "ui.h"

// 动画持续时间
SoftwareTimer duration_timer;
// 帧时间
SoftwareTiemr frame_timer;
// 当前动画状态
int status;

void start_animation_init(void) {
    // 动画持续3s
    software_timer_init(&duration_timer, 3000);
    // 帧时间0.2s
    software_timer_init(&frame_timer, 200);
    // 当前状态
    status = 0;
}

void start_animation_content(char *line1, char *line2) { 
    char c;
    switch(status) {
        case 0:
            c = '-';
            break;
        case 1:
            c = '+';
            break;
        case 2:
            c = '#';
            break;
        case 3:
            c = '$';
            break;
        case 4:
            c = '*';
            break;
        case 5:
            c = 'x';
            break;
        case 6:
            c = 0x9D; // 爱心
            break;
        case 7:
            c = 0x01; // 右箭头
            break;
        case 8:
            c = 0x11; // 左箭头
            break;
        default:
            c = '-';
            break;
    }
    sprintf(line1, "%c%c%c%cDIGITAL%c%c%c%c%c", c, c, c, c, c, c, c, c, c);
    sprintf(line2, "%c%c%c%c%cCLOCK%c%c%c%c%c%c", c, c, c, c, c, c, c, c, c, c, c);
    // 每过一帧时间状态切换
    if (software_timer_expired(frame_timer)) {
        if (status == 8) {
            status = 0;
        }
        else
            status++;
    }
    // 动画结束，进入时钟界面
    change_ui(CLOCK_INTERFACE);
}
        
            
            