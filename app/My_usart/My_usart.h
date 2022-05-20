#ifndef __My_USART_H
#define __My_USART_H 
#include "sys.h"
#include "stdio.h"	
#include "mytask.h"

#define BUFFER_SIZE (255)

//#define USART_REC_LEN  			200  	//�����������ֽ��� 200
//#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
//	  	
//extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
//extern u16 USART_RX_STA;         		//����״̬���	

void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
uint8_t USART_ReviceCmd(char *cmd,char *data);
uint8_t USART_SendCmd(char *cmd, char *res);
#endif	   
















