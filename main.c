#include "timer.h"
#include "lcd.h"
#include "clock.h"
#include "ui.h"

// 各组件初始化
void init(void) {
    // 初始化全局时钟
    global_timer_init();
    // 初始化日期时间
    clock_init();
    // 初始化UI
    ui_init();
    // 初始化LCD
    lcd_init();
    // 开机动画
    change_ui(START_ANIMATION);
}

int main() {
    init();
    
    while(1) {
        show_ui();
        clock_process();
    }
    
    return 0;
}