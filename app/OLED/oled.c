#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"

void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCL_Clr();
		if(dat&0x80)
		   OLED_SDA_Set();
		else 
		   OLED_SDA_Clr();
		OLED_SCL_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
}
//******************************************************************************
//    函数说明：OLED显示列的起始终止地址
//    入口数据：a  列的起始地址
//              b  列的终止地址
//    返回值：  无
//******************************************************************************
void Column_Address(uint8_t a, uint8_t b)
{
	OLED_WR_Byte(0x15,OLED_CMD);			    // Set Column Address
	OLED_WR_Byte(a,OLED_CMD);				//   Default => 0x00
	OLED_WR_Byte(b,OLED_CMD);				//   Default => 0x77
}

//******************************************************************************
//    函数说明：OLED显示行的起始终止地址
//    入口数据：a  行的起始地址
//              b  行的终止地址
//    返回值：  无
//******************************************************************************
void Row_Address(uint8_t a, uint8_t b)
{
	OLED_WR_Byte(0x75,OLED_CMD);			// Set Row Address
	OLED_WR_Byte(a,OLED_CMD);				//   Default => 0x00
	OLED_WR_Byte(b,OLED_CMD);				//   Default => 0x3F
}

//******************************************************************************
//    函数说明：OLED清屏显示
//    入口数据：无
//    返回值：  无
//******************************************************************************
void OLED_Clear(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
	uint8_t i,m=0;
	x1/=2;x2/=2;
	Column_Address(x1,x2-1);
	Row_Address(y1,y2-1);
	for (m=0;m<y2-y1;m++) 
	{ 
		for (i=0;i<x2-x1;i++)
		{
			 OLED_WR_Byte(color,OLED_DATA);
		}
	}
}

//******************************************************************************
//    函数说明：OLED显示字符函数 
//    此函数适用范围：字符宽度是2的倍数  字符高度是宽度的2倍
//    入口数据：x,y   起始坐标
//              chr   要写入的字符
//              sizey 字符高度 
//    返回值：  无
//******************************************************************************
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t sizey)
{
	uint8_t i,j,c,k;
	uint8_t data1,data2,DATA1=0;
	c=chr-' ';
	for(i=0;i<sizey/8;i++)
	{
	  Column_Address(x/2,x/2+sizey/4-1);//设置列地址
	  Row_Address(y+i*8,y+i*8+7);//设置行地址
		for(j=0;j<sizey/4;j++)
		{
			if(sizey==16)//8x16 ASCII码
			{
				data1=F8X16[c][2*j+i*sizey/2+0];
				data2=F8X16[c][2*j+i*sizey/2+1];
			}
			else if(sizey==24)//12x24 ASCII码
			{
				data1=F12X24[c][2*j+i*sizey/2+0];
				data2=F12X24[c][2*j+i*sizey/2+1];

			}
			else if(sizey==32)//16x32 ASCII码
			{
				data1=F16X32[c][2*j+i*sizey/2+0];
				data2=F16X32[c][2*j+i*sizey/2+1];
			}
			for(k=0;k<8;k++)
			{
				if(data1&(0x01<<k))
				{
					DATA1=0xf0;
				}
				if(data2&(0x01<<k))
				{
					DATA1|=0x0f;
				}
				OLED_WR_Byte(DATA1,OLED_DATA);
				DATA1=0;
			}
		}
	}
}

//******************************************************************************
//    函数说明：OLED显示字符串
//    入口数据：x,y  起始坐标
//              *dp  要写入的字符串
//    返回值：  无
//******************************************************************************
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *dp,uint8_t sizey)
{
	while(*dp!='\0')
	{
	  OLED_ShowChar(x,y,*dp,sizey);
		dp++;
		x+=sizey/2;
	}
}


//******************************************************************************
//    函数说明：m^n
//    入口数据：m:底数 n:指数
//    返回值：  result
//******************************************************************************
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)result*=m;    
	return result;
}


//******************************************************************************
//    函数说明：OLED显示字符码值
//    入口数据：x,y :起点坐标	 
//              len :数字的位数
//              size:字体大小
//    返回值：  无
//******************************************************************************
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(sizey/2)*t,y,' ',sizey);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(sizey/2)*t,y,temp+'0',sizey); 
	}
}

//******************************************************************************
//    函数说明：OLED显示汉字
//    入口数据：x,y :起点坐标
//              len :数字的位数
//              size:字体大小
//    返回值：  无
//******************************************************************************
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t sizey)
{
	uint8_t i,j,k;
	uint8_t data1,data2,DATA1=0;
	for(i=0;i<sizey/8;i++)
	{
	  Column_Address(x/2,x/2+sizey/2-1);//设置列地址
	  Row_Address(y+i*8,y+i*8+7);//设置行地址
		for(j=0;j<sizey/2;j++)
		{
			if(sizey==16)//8x16 ASCII码
			{
				data1=Hzk16x16[num][2*j+i*sizey+0];
				data2=Hzk16x16[num][2*j+i*sizey+1];
			}
			else if(sizey==24)//12x24 ASCII码
			{
				data1=Hzk24x24[num][2*j+i*sizey+0];
				data2=Hzk24x24[num][2*j+i*sizey+1];

			}
			else if(sizey==32)//16x32 ASCII码
			{
				data1=Hzk32x32[num][2*j+i*sizey+0];
				data2=Hzk32x32[num][2*j+i*sizey+1];
			}
			for(k=0;k<8;k++)
			{
				if(data1&(0x01<<k))
				{
					DATA1=0xf0;
				}
				if(data2&(0x01<<k))
				{
					DATA1|=0x0f;
				}
				OLED_WR_Byte(DATA1,OLED_DATA);
				DATA1=0;
			}
		}
	}
}

void OLED_DrawBMP(uint8_t x,uint8_t y,uint8_t width,uint8_t height,const uint8_t *BMP)
{
	uint16_t k,num;
	x/=2;width/=2;
	Column_Address(x,x+width-1);
	Row_Address(y,y+height-1);
	num=width*height;
	for (k=0;k<num;k++) 
	{ 
		 OLED_WR_Byte(BMP[k],OLED_DATA);
	}
}	


//初始化				    
void Init_ssd1327(void)
{
	GPIO_Set(GPIOB,PIN9|PIN10|PIN11|PIN12|PIN13|PIN15,GPIO_MODE_OUT,GPIO_OTYPE_PP, 
	GPIO_SPEED_100M,GPIO_PUPD_PU);	
	OLED_RES_Clr();
	//delay_ms(200);
	OLED_RES_Set();
	
	OLED_WR_Byte(0xae,OLED_CMD);//Set display off
	OLED_WR_Byte(0xa0,OLED_CMD);//Set re-map
	if(USE_HORIZONTAL){OLED_WR_Byte(0x66,OLED_CMD);}
	else{OLED_WR_Byte(0x55,OLED_CMD);}
	OLED_WR_Byte(0xa1,OLED_CMD);//Set display start line
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xa2,OLED_CMD);//Set display offset
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xa4,OLED_CMD);//Normal Display
	OLED_WR_Byte(0xa8,OLED_CMD);//Set multiplex ratio
	OLED_WR_Byte(0x7f,OLED_CMD);
	OLED_WR_Byte(0xab,OLED_CMD);//Function Selection A
	OLED_WR_Byte(0x01,OLED_CMD);//Enable internal VDD regulator
	OLED_WR_Byte(0x81,OLED_CMD);//Set contrast
	OLED_WR_Byte(0x77,OLED_CMD);
	OLED_WR_Byte(0xb1,OLED_CMD);//Set Phase Length
	OLED_WR_Byte(0x31,OLED_CMD);
	OLED_WR_Byte(0xb3,OLED_CMD);//Set Front Clock Divider /Oscillator Frequency
	OLED_WR_Byte(0xb1,OLED_CMD);
  OLED_WR_Byte(0xb5,OLED_CMD);//
  OLED_WR_Byte(0x03,OLED_CMD);//0X03 enable
	OLED_WR_Byte(0xb6,OLED_CMD);//Set Second pre-charge Period
	OLED_WR_Byte(0x0d,OLED_CMD);
	OLED_WR_Byte(0xbc,OLED_CMD);//Set Pre-charge voltage
	OLED_WR_Byte(0x07,OLED_CMD);
	OLED_WR_Byte(0xbe,OLED_CMD);//Set VCOMH
	OLED_WR_Byte(0x07,OLED_CMD);
	OLED_WR_Byte(0xd5,OLED_CMD);//Function Selection B
	OLED_WR_Byte(0x02,OLED_CMD);//Enable second pre-charge
	OLED_Clear(0,0,127,127,0x00);
	OLED_WR_Byte(0xaf,OLED_CMD);//Display on
}

