#ifndef SINGER_H_
#define SINGER_H_

// 清空乐谱并将索引清零
void singer_clear_music(void);

// 写入乐谱
void singer_write_music(int m[], int len);

// 初始化
void singer_init(void);

// 更新当前所唱音调（index：要更新到乐谱的第几个音调）
void singer_update_tone(int index);

// 发声模块
void sing(void);

#endif /*SINGER_H_*/
