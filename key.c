#include "key.h"
#include "system.h" 
#include "altera_avalon_pio_regs.h" 
#include "alt_types.h" 
#include "timer.h"
#include "ui.h"
#include <stdio.h>
#include <unistd.h> 

SoftwareTimer check_timer; //轮询定时器
int count;
int last_key; // 记录上次按键

void key_init(void) {
    software_timer_init(&check_timer, 10); // 轮询周期1ms
    last_key = -1;
    count=0;
}

int key_read(void) {
    alt_u16 keys;
    keys = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);
    int i;
    for (i = 0; i < 10; i++) {
        if (!(keys & (1 << i))) {   // 第i位为0，表示按下
            return i;
        }
    }
    return -1;  
}

void key_update(void) {
    if (software_timer_expired(&check_timer)) {
        int key = key_read();
        if (key != last_key) {
            // 长按键
            if (count >= 5) {
                switch(last_key) {
                    case 0:
                        ui_key(F1_LONG);
                        break;
                    case 1:
                        ui_key(F2_LONG);
                        break;
                    case 2:
                        ui_key(F3_LONG);
                        break;
                    case 3:
                        ui_key(F4_LONG);
                        break;
                    case 4:
                        ui_key(F5_LONG);
                        break;
                    case 5:
                        ui_key(F6_LONG);
                        break;
                    case 6:
                        ui_key(F7_LONG);
                        break;  
                    case 7:
                        ui_key(F8_LONG);
                        break;
                    case 8:
                        ui_key(F9_LONG);
                        break;
                    case 9:
                        ui_key(F10_LONG);
                        break;
                    default:
                        ui_key(NONE);
                        break;
                }
            }
            // 短按键
            else if (count >= 1) {
                switch(last_key) {
                    case 0:
                        ui_key(F1);
                        break;
                    case 1:
                        ui_key(F2);
                        break;
                    case 2:
                        ui_key(F3);
                        break;
                    case 3:
                        ui_key(F4);
                        break;
                    case 4:
                        ui_key(F5);
                        break;
                    case 5:
                        ui_key(F6);
                        break;
                    case 6:
                        ui_key(F7);
                        break;
                    case 7:
                        ui_key(F8);
                        break;
                    case 8:
                        ui_key(F9);
                        break;
                    case 9:
                        ui_key(F10);
                        break;
                    default:
                        ui_key(NONE);
                        break; 
                }
            }
            last_key = key;
            count = 0;
        }
        else if (key != -1) {
            count ++;
        }
    }
}