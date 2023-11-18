#ifndef __SCREEN_H
#define __SCREEN_H

#include "st7789/st7789.h"
#include "MAX17262/MAX17262.h"
#include "stdbool.h"

//FLAG
static char lcd_str[40]; // lcd message
static bool sd_cnt=true;
static bool ble_cnt=false;
static bool bat_cnt;


void screen_init(TIM_HandleTypeDef *htim9);
void main_screen(bool left_btn, bool ok_btn, bool right_btn, uint16_t micData, float lpsData);
void menu_screen(bool left_btn, bool ok_btn, bool right_btn, uint8_t subScreen);
void fifo_screen(bool left_btn, bool ok_btn, bool right_btn, uintmax_t timeT, float lpsData);
void general_screen(bool left_btn, bool ok_btn, bool right_btn);
void reset_screen(void);
#endif
