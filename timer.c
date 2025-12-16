#include "timer.h"
#include "altera_avalon_timer_regs.h"
#include "system.h" 
#include <stddef.h>

volatile unsigned int global_timer = 0;

void timer_disruption(void *context) {
    // 清中断
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);
    global_timer++;
}

void global_timer_init(void) {
    // 50MHz -> 1000Hz
    IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_BASE, 50000); // 低位
    IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_BASE, 0); // 高位
    
    IOWR_ALTERA_AVALON_TIMER_CONTROL(
        TIMER_BASE,
        ALTERA_AVALON_TIMER_CONTROL_ITO_MSK |
        ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
        ALTERA_AVALON_TIMER_CONTROL_START_MSK
    );
    
    alt_irq_register(TIMER_IRQ, NULL, timer_disruption);
}

void software_timer_init(SoftwareTimer *t, unsigned int interval) {
    t->last_time = global_timer;
    t->interval = interval;
}

bool software_timer_expired(SoftwareTimer *t) {
    // 如果当前系统计时器减去上次时间大于预先设定的间隔
    if (global_timer - t->last_time >= t->interval) {
        // 更新上次时间加上间隔
        t->last_time += t->interval;
        return true;
    }
    return false;
}
        