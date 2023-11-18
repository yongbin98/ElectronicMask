#include "lcdscreen.h"

extern bool sd_cnt; // sd init -> true
extern bool bat_cnt;
extern bool ble_cnt;

void screen_init(TIM_HandleTypeDef *htim9){
	ST7789_Init();
	ST7789_Fill_Color(0, 0, 240, 40, FLIP_RGB(WHITE));
	
	sprintf(lcd_str, "BAMI_AIWM");
	ST7789_WriteString(0, 80, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	
	HAL_TIM_PWM_Start(htim9, TIM_CHANNEL_1);
	for(int i=0; i<500; i=i+10){ TIM9->CCR1 = i;	HAL_Delay(1);}
}

void main_screen(bool left_btn, bool ok_btn, bool right_btn, uint16_t micData, float lpsData){

	general_screen(left_btn,ok_btn,right_btn);
			
	sprintf(lcd_str, "BAMI_AIWM");
	ST7789_WriteString(0, 80, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	
	ST7789_WriteString(0, 130, "MIC : ", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));		
	sprintf(lcd_str, "%d", micData);
	ST7789_WriteString(96, 130, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	
	ST7789_WriteString(0, 160, "hPa : ", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));		
	sprintf(lcd_str, "%6.3f", lpsData);
	ST7789_WriteString(96, 160, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));		
}

void reset_screen(){
	ST7789_Fill_Color(0, 0, 240, 240, FLIP_RGB(BLACK));	
	ST7789_Fill_Color(0, 0, 240, 40, FLIP_RGB(WHITE));	
}
void menu_screen(bool left_btn, bool ok_btn, bool right_btn, uint8_t subScreen){
		
	general_screen(left_btn,ok_btn,right_btn);
			
//	sprintf(lcd_str, "temp : %3d", micData);
//	ST7789_WriteString(0, 180, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	
	ST7789_WriteString(16, 100, "Start", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	ST7789_WriteString(112, 100, "MIC LPS", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	ST7789_WriteString(56, 150, "Press OK", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
}

void fifo_screen(bool left_btn, bool ok_btn, bool right_btn, uintmax_t timeT, float lpsData){
	
	ST7789_WriteString(0, 80, "Save", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));		
	ST7789_WriteString(96, 80, "Data", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));		
	
	uint16_t min = ((timeT/1000)/60)%60;
	uint16_t sec = ((timeT/1000)%60);
	
	ST7789_WriteString(0, 120, "min : ", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));		
	sprintf(lcd_str, "%3d", min);
	ST7789_WriteString(96, 120, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));			
	
	ST7789_WriteString(0, 160, "sec : ", Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));		
	sprintf(lcd_str, "%3d", sec);
	ST7789_WriteString(96, 160, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));			
}

void general_screen(bool left_btn, bool ok_btn, bool right_btn){
	bat_cnt = !HAL_GPIO_ReadPin(BAT_CG_POK_GPIO_Port,BAT_CG_POK_Pin);
	sd_cnt = !HAL_GPIO_ReadPin(SD_SW_GPIO_Port,SD_SW_Pin);
	
	if(ble_cnt == false)
		ST7789_DrawImage(1, 1, 37, 37, (uint16_t *)IMG_37x37_BT_NC);
	else
		ST7789_DrawImage(1, 1, 37, 37, (uint16_t *)IMG_37x37_BT_CN);
	
	if(sd_cnt == false)
		ST7789_DrawImage(40, 1, 37, 37, (uint16_t *)IMG_37x37_SD_UM);
	else
		ST7789_DrawImage(40, 1, 37, 37, (uint16_t *)IMG_37x37_SD_MT);
	
	if(bat_cnt == false)
		ST7789_DrawImage(210, 1, 24, 37, (uint16_t *)IMG_24x37_BAT_CAN);
	else
		ST7789_DrawImage(210, 1, 24, 37, (uint16_t *)IMG_24x37_BAT_CG);
	
	uint8_t battery_value=MAX17262_Get_BatPercent();
	sprintf(lcd_str, "%3d%%", battery_value);
	ST7789_WriteString(140, 10, lcd_str, Font_16x26, FLIP_RGB(BLACK), FLIP_RGB(WHITE));
	
	sprintf(lcd_str, "<<");
	if(left_btn == false)
		ST7789_WriteString(5, 214, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	else
		ST7789_WriteString(5, 214, lcd_str, Font_16x26, FLIP_RGB(RED), FLIP_RGB(BLACK));
	
	sprintf(lcd_str, "OK");
	if(ok_btn == false)
		ST7789_WriteString(100, 214, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	else
		ST7789_WriteString(100, 214, lcd_str, Font_16x26, FLIP_RGB(RED), FLIP_RGB(BLACK));
	
	sprintf(lcd_str, ">>");
	if(right_btn == false)
		ST7789_WriteString(200, 214, lcd_str, Font_16x26, FLIP_RGB(WHITE), FLIP_RGB(BLACK));
	else
		ST7789_WriteString(200, 214, lcd_str, Font_16x26, FLIP_RGB(RED), FLIP_RGB(BLACK));
			
}