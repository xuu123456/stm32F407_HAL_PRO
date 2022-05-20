#ifndef _HT1621_H
#define _HT1621_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "main.h"
#include "delay.h"

#ifdef __cplusplus
}
#endif
#define HT1621_DAT_H                (GPIOE->ODR |= (0x01<<6))
#define HT1621_DAT_L                (GPIOE->ODR  &= ~(0x01<<6))
#define HT1621_WR_H                 (GPIOE->ODR  |= (0x01<<4))
#define HT1621_WR_L	                (GPIOE->ODR  &= ~(0x01<<4))
#define HT1621_CS_H                 (GPIOE->ODR  |= (0x01<<2))
#define HT1621_CS_L	                (GPIOE->ODR  &= ~(0x01<<2))
//#define HT1621_BL_OFF               (GPIOE->BSRRL |= (0x01<<4))
//#define HT1621_BL_ON	              (GPIOE->BSRRH |= (0x01<<4))

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

class Ht1621
{
	protected:
		void Ht1621Wr_Data(uint8_t Data,uint8_t cnt);
		void Ht1621WrCmd(uint8_t Cmd) ;
		void Ht1621WrOneData(uint8_t Addr,uint8_t Data) ;
		void Ht1621WrByteData(uint8_t Addr,uint8_t Data) ;
		void Ht1621CleanAllData(uint8_t Addr,uint8_t cnt) ;
		void Ht1621FillData(uint8_t Addr,uint8_t	cnt) ;
		void Ht1621_Init(void) ;
};


#endif