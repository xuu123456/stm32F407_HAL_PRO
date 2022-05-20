#ifndef _LCD_SEG48A_H
#define _LCD_SEG48A_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "main.h"
#include "delay.h"
#include "ht1621.h"
#ifdef __cplusplus
}
#endif


#define BIAS     					0x52		  			//0x4A//0x50//0x48//         //0b1000 0101 0010  1/3duty 4com
#define SYSDIS 						0X00            //0b1000 0000 0000  关振系统荡器和LCD偏压发生器 
#define SYSEN  						0X02            //0b1000 0000 0010 打开系统振荡器 
#define LCDOFF					 	0X04            //0b1000 0000 0100  关LCD偏压 
#define LCDON  						0X06            //0b1000 0000 0110  打开LCD偏压 
#define XTAL   						0x28            //0b1000 0010 1000 外部接时钟 
#define RC256  						0X30            //0b1000 0011 0000  内部时钟 
#define TONEON  					0X12          	//0b1000 0001 0010  打开声音输出
#define TONEOFF 					0X10          	//0b1000 0001 0000 关闭声音输出
#define WDTDIS  					0X0A       	  	//0b1000 0000 1010  禁止看门狗
#define _Nop()  					delay_us(2)
#define WriteCmd  (uint16_t)0x140


class LCD_SEG48A :public Ht1621
{
	
	public:
		void LCD_SEG48A_DisplayNum(uint8_t num,uint8_t bit);
		void LCD_SEG48A_DisplayPoint(uint8_t bit);
		void LCD_SEG48A_Init(void);
}	;

#endif