#include "LCD_SEG48A.h"
uint8_t const DisPlay_Time_Tab[2][10] =//tab[0] 第一个四位，tab[1]第二个四位
                                        {
																				{0x0e,0x06,0x0a,0x08,0x04,0x0c,0x0e,0x08,0x0e,0x0c},
																				{0x0b,0x00,0x0d,0x0f,0x0e,0x07,0x07,0x0a,0x0f,0x0f},
																				};

																				
/*******************
num要显示的数字：0~9
bit:显示第几位  1~4
***********************/
void LCD_SEG48A ::LCD_SEG48A_DisplayNum(uint8_t num,uint8_t bit)
{
	if(num>9) num=9;
	if(bit>=4) bit=4;
	HT1621_CS_L;
	switch(bit)
	{
		case 1:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(0<<2,6);        //写入地址数据
			Ht1621Wr_Data(DisPlay_Time_Tab[0][num]<<4,4);//低字节写入
			Ht1621Wr_Data(DisPlay_Time_Tab[1][num]<<4,4);
			break;
		case 2:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(2<<2,6); 
			Ht1621Wr_Data(DisPlay_Time_Tab[0][num]<<4,4);//低字节写入
			Ht1621Wr_Data(DisPlay_Time_Tab[1][num]<<4,4);
			break;
		case 3:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(4<<2,6); 
			Ht1621Wr_Data(DisPlay_Time_Tab[0][num]<<4,4);//低字节写入
			Ht1621Wr_Data(DisPlay_Time_Tab[1][num]<<4,4);
			break;
		case 4:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(6<<2,6); 
			Ht1621Wr_Data(DisPlay_Time_Tab[0][num]<<4,4);//低字节写入
			Ht1621Wr_Data(DisPlay_Time_Tab[1][num]<<4,4);
			break;
		default:
			break;
	}

		HT1621_CS_H;
	_Nop();
}
/*******************
bit:显示第几个小数点  1~4
***********************/
void LCD_SEG48A ::LCD_SEG48A_DisplayPoint(uint8_t bit)
{
	if(bit>=4) bit=4;
	HT1621_CS_L;
	switch(bit)
	{
		case 1:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(0<<2,6);        //写入地址数据
			Ht1621Wr_Data(0x01<<4,4);
			break;
		case 2:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(2<<2,6); 
			Ht1621Wr_Data(0x01<<4,4);
			break;
		case 3:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(4<<2,6); 
			Ht1621Wr_Data(0x01<<4,4);
			break;
		case 4:
			Ht1621Wr_Data(0xa0,3);           //写入数据标志101
			Ht1621Wr_Data(6<<2,6); 
			Ht1621Wr_Data(0x01<<4,4);
			break;
		default:
			break;
	}

		HT1621_CS_H;
	_Nop();
}		


void LCD_SEG48A ::LCD_SEG48A_Init(void)
{
	Ht1621_Init();
}