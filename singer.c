#include "singer.h"
#include "timer.h"
#include "altera_avalon_pio_regs.h" 
#include "system.h"
#include "alt_types.h"
#include <string.h>

#define INFINITY 2^31

SoftwareTimer beat_timer; // 节拍计时器
SoftwareTimer tone_timer; // 音调计时器

int tone_clock; // 扬声器信号
int music[200]; // 乐谱
int music_len; // 乐谱长度
int singer_current_index; // 当前第几个节拍

int timer_of_tone[21] = {5000/262, 5000/294, 5000/330, 5000/349, 5000/392, 5000/440, 5000/494,
                        5000/523, 5000/587, 5000/659, 5000/699, 5000/784, 5000/880, 5000/988,
                        5000/1046, 5000/1175, 5000/1319, 5000/1397, 5000/1568, 5000/1760, 5000/1796};

// 清空乐谱并将索引清零
void singer_clear_music(void) {
    music_len = 0;
    singer_current_index = -1;
}

// 写入乐谱
void singer_write_music(int m[], int len) {
    music_len = len;
    int i;
    for (i = 0; i < len; i++)
        music[i] = m[i];
}

// 初始化
void singer_init(void) {
    software_timer_init(&beat_timer, 2500); // 一秒4拍
    software_timer_init(&tone_timer, INFINITY); // 不发声
    singer_clear_music();
}

// 反转扬声器信号，反转频率决定音调高低
void singer_reverse_tone_clock(void) {
    if (tone_clock)
        IOWR_ALTERA_AVALON_PIO_DATA(SINGER_BASE, 0);
    else
        IOWR_ALTERA_AVALON_PIO_DATA(SINGER_BASE, 1);
}

// 更新当前所唱音调（index：要更新到乐谱的第几个音调）
void singer_update_tone(int index) {
    if (0 < index && index < music_len) {
        singer_current_index = index;
        int tone = music[singer_current_index];
        if (1 <= tone && tone <= 21) {
            software_timer_init(&tone_timer, timer_of_tone[tone]);
        }
        else {
            software_timer_init(&tone_timer, INFINITY);
        }
    }
    else {
        software_timer_init(&tone_timer, INFINITY);
    }
}

// 发声模块
void sing(void) {
    // 音调计时器超时，则音调时钟反转
    if (software_timer_expired(&tone_timer)) {
        singer_reverse_tone_clock();
    }
    // 节拍计时器超时，则进入下一拍
    if (software_timer_expired(&beat_timer)) {
        // 到达乐谱末尾
        if (singer_current_index == music_len - 1) {
            singer_clear_music(); // 清空乐谱，结束演奏
        }
        else {
            singer_update_tone(singer_current_index + 1);
        }
    }
}
    