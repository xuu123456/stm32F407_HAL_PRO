#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	
#include "main.h"
#define USE_HORIZONTAL 0  //设置显示方向 0：正向显示，1：旋转180度显示

//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() PBout(13) = 0//SCL
#define OLED_SCL_Set() PBout(13) = 1

#define OLED_SDA_Clr() PBout(15) = 0//SDA
#define OLED_SDA_Set() PBout(15) = 1

#define OLED_RES_Clr() PBout(9) = 0//RES
#define OLED_RES_Set() PBout(9) = 1

#define OLED_DC_Clr()  PBout(10) = 0//DC
#define OLED_DC_Set()  PBout(10) = 1
 		     
#define OLED_CS_Clr()  PBout(11) = 0//CS
#define OLED_CS_Set()  PBout(11) = 0


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void Column_Address(uint8_t a, uint8_t b);
void Row_Address(uint8_t a, uint8_t b);
void OLED_Clear(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t sizey);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *dp,uint8_t sizey);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t sizey);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t sizey);
void OLED_DrawBMP(uint8_t x,uint8_t y,uint8_t width,uint8_t height,const uint8_t *BMP);
void Init_ssd1327(void);

#endif

