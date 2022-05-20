#include "ht1621.h"
#include "delay.h"
//uint8_t const DisPlay_Time_Tab1[10] ={0xd7,0x06,0x65,0xf1,0x72,0xe3,0xe7,0x51,0xf7,0xf3};//��λ ��һ����λ����λ�ڶ�����λ

void Ht1621::Ht1621Wr_Data(uint8_t Data,uint8_t cnt)//First write High bit ,then wrist low bit
{ 
	uint8_t i;
	for (i = 0;i < cnt;i++)
	{
		HT1621_WR_L;
		_Nop();
		_Nop();
		if(((Data&0x80) >> 7))
			HT1621_DAT_H;
		else
			HT1621_DAT_L;
		_Nop();
		_Nop();
		HT1621_WR_H;
		_Nop();
		_Nop();
		Data <<= 1;
	}
} 
void Ht1621::Ht1621WrCmd(uint8_t Cmd) 
{ 
	HT1621_CS_L;
	_Nop();
	Ht1621Wr_Data(0x80,4);        //д�������־100 0//��������100 ��һλ���ݶ���0���������ʵ����д����λ��1000
	Ht1621Wr_Data(Cmd,8);         //д���������ݣ����λĬ����0
	HT1621_CS_H;
	_Nop();
} 
void Ht1621::Ht1621WrOneData(uint8_t Addr,uint8_t Data) 
{ 
	HT1621_CS_H;
	_Nop();
	HT1621_CS_L;
	Ht1621Wr_Data(0xa0,3);           //д�����ݱ�־101
	Ht1621Wr_Data(Addr<<2,6);        //д���ַ����
	Ht1621Wr_Data(Data<<4,4);        //д������
	HT1621_CS_H;
	_Nop();
}

void Ht1621::Ht1621WrByteData(uint8_t Addr,uint8_t Data) 
{ 
	uint8_t i;
	HT1621_CS_L; 
	Ht1621Wr_Data(0xa0,3);           //д�����ݱ�־101
	Ht1621Wr_Data(Addr<<2,6);        //д���ַ����
	for (i=0;i<8;i++)
	{
		HT1621_WR_L;
		_Nop();
		if((Data&0x80)>>7)
			HT1621_DAT_H;
		else
			HT1621_DAT_L;
		_Nop();
		HT1621_WR_H;
		_Nop();
		Data <<= 1;
	}
	HT1621_CS_H;
	_Nop();
}

void Ht1621::Ht1621CleanAllData(uint8_t Addr,uint8_t cnt) 
{ 
	uint8_t i;
	HT1621_CS_L;
	Ht1621Wr_Data(0xa0,3);       	  //д�����ݱ�־101
	Ht1621Wr_Data(Addr<<2,6);         //д���ַ����
	for (i=0;i<cnt;i++)
	{
		Ht1621Wr_Data(0,8);          //д������
	}
	HT1621_CS_H;
	_Nop();
}

void Ht1621::Ht1621FillData(uint8_t Addr,uint8_t	cnt) 
{ 
	uint8_t i;
	HT1621_CS_L;
	Ht1621Wr_Data(0xa0,3);        	//д�����ݱ�־101
	Ht1621Wr_Data(Addr<<2,6);         //д���ַ����
	for (i=0;i<cnt;i++)
	{
		Ht1621Wr_Data(0xFF,8);      //д������
	}
	HT1621_CS_H;
	_Nop();
}
void Ht1621::Ht1621_Init(void) 
{ 
	//HT1621_BL_OFF;
	//GPIO_Set(GPIOA,PIN1|PIN2|PIN3|PIN4,GPIO_MODE_OUT,GPIO_OTYPE_PP, GPIO_SPEED_100M,GPIO_PUPD_PU);
	//USART2->CR1 &= ~(USART_CR1_UE|USART_CR1_IDLEIE|USART_CR1_RE);//��ֹUSART2 ʹ�� 
	//LCD_CLK_DISABLE;	//must turn off the clock of LCD before initialization
	delay_us(50);
 	HT1621_CS_H; 
	HT1621_DAT_H; 
	HT1621_WR_H;
	delay_us(100);                   
	delay_us(100);
	Ht1621WrCmd(BIAS);//clock output disable
	Ht1621WrCmd(RC256);//Use internal osc��256k
	Ht1621WrCmd(SYSDIS);//close osc and LCD bias generator
	Ht1621WrCmd(WDTDIS);//close watch dog output
	Ht1621WrCmd(SYSEN);//open sys osc
	Ht1621WrCmd(LCDON);//open LCD bias generator
	Ht1621CleanAllData(0,16);     //clear	
	delay_us(50);
	//USART2->CR1 |= (USART_CR1_UE|USART_CR1_IDLEIE|USART_CR1_RE); 
	
	//LCD_CLK_ENABLE;
}

