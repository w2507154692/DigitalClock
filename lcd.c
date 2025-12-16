#include "lcd.h"
#include <stdio.h> 
#include "system.h" 
#include "altera_avalon_pio_regs.h" 
#include "alt_types.h" 
#include <unistd.h> 
#include <string.h> 

// 写数据
void lcd_write_data(alt_u8 data) 
{ 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_RS_BASE,1); 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_NWR_BASE,0); 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_DATA_BASE,data);   //地址计数器自动加1，显示屏不移动 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_NRD_BASE,1); 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_NRD_BASE,0); 
} 

// 写指令
void lcd_write_cmd(alt_u8 cmd) 
{ 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_RS_BASE,0); 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_NWR_BASE,0); 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_DATA_BASE,cmd);   //地址计数器自动加1，显示屏不移动 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_NRD_BASE,1); 
    IOWR_ALTERA_AVALON_PIO_DATA(TFT_LCD_NRD_BASE,0); 
}

// LCD初始化
void lcd_init(void) {
    lcd_write_cmd(0x3C); // 数据位宽8位，10点阵
    usleep(2000);
    lcd_write_cmd(0x06); // 设置修改DDRAM后，地址计数器自动加1
    usleep(2000);
    lcd_write_cmd(0x0C); // 开始显示，光标不闪烁，光标不显示
    usleep(2000);
    lcd_write_cmd(0x01); // 清屏
    usleep(2000);
    lcd_write_cmd(0x80); // 设置DDRAM地址为0
    usleep(2000);
}

// LCD打印一串字符
void lcd_show_one_line(char *text) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        lcd_write_data(text[i]);
        usleep(2000);
    }
}

// 切换到第一行首
void lcd_line1(void) {
    lcd_write_cmd(0x80);
    usleep(2000);
}

// 切换到第二行首
void lcd_line2(void) {
    lcd_write_cmd(0xC0);
    usleep(2000);
}

// 传入两行字符串，显示内容
void lcd_show_text(char *line1, char *line2) {
    lcd_line1();
    lcd_show_one_line(line1);
    lcd_line2();
    lcd_show_one_line(line2);
}