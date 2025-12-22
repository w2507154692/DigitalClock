#include "ui.h"
#include "lcd.h"
#include "clock.h"
#include "timer.h"
#include "clock_interface.h"
#include "start_animation.h"
#include "key.h"
#include <stdio.h>

// 当前是哪一个界面
int current_ui;
// ui刷新计时器
SoftwareTimer ui_timer;

// ui组件初始化
void ui_init(void) {
    // 10ms刷新一次
    software_timer_init(&ui_timer, 100);
}

// 切换当前ui
void change_ui(int ui) {
    current_ui = ui;
    switch(current_ui) {
        case START_ANIMATION:
            start_animation_init();
            break;
        case CLOCK_INTERFACE:
            break;
        case EDIT_CLOCK_INTERFACE:
            edit_clock_interface_init();
            break;
        case EDIT_INVALID_ANIMATION:
            edit_invalid_animation_init();
        case EDIT_SUCCESS_ANIMATION:
            edit_success_animation_init();
            break;
        default:
            break;
    }
}

void show_ui(void) {
    if (software_timer_expired(&ui_timer)) {
        char line1[16], line2[16];
        // 获取当前界面显示内容
        switch(current_ui) {
            // 开机动画
            case START_ANIMATION:
                start_animation_content(line1, line2);
                break;
            // 时钟界面
            case CLOCK_INTERFACE:
                clock_interface_content(line1, line2);
                break;
            // 修改界面
            case EDIT_CLOCK_INTERFACE:
                edit_clock_interface_content(line1, line2);
                break;
            // 修改非法动画
            case EDIT_INVALID_ANIMATION:
                edit_invalid_animation_content(line1, line2);
                break;
            // 修改成功动画
            case EDIT_SUCCESS_ANIMATION:
                edit_success_animation_content(line1, line2);
                break;
            default:
                clock_interface_content(line1, line2);
                break;
        }
        // 显示
        lcd_show_text(line1, line2);
    }
}

void ui_key(int key) {
    switch(current_ui) {
        case CLOCK_INTERFACE:
            clock_interface_key(key);
            break;
        case EDIT_CLOCK_INTERFACE:
            edit_clock_interface_key(key);
            break;
        default:
            break;
    }
}
