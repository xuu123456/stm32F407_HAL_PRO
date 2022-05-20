#ifndef __My_USART_H
#define __My_USART_H 
#include "sys.h"
#include "stdio.h"	
#include "mytask.h"

#define BUFFER_SIZE (255)

//#define USART_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
//	  	
//extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//extern u16 USART_RX_STA;         		//接收状态标记	

void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
uint8_t USART_ReviceCmd(char *cmd,char *data);
uint8_t USART_SendCmd(char *cmd, char *res);
#endif	   
















