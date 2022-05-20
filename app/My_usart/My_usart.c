#include "sys.h"
#include "My_usart.h"
#include "string.h"
static uint8_t cmd_flag;//若发出命令之后，此为置1
static uint8_t res_flag;//若接收到数据，此位为1，
#if 1
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (uint8_t) ch;      
	return ch;
}
#endif 
extern UART_HandleTypeDef huart1;
extern uint8_t receive_buff[255];    
extern DMA_HandleTypeDef hdma_usart1_rx;//声明外部变量 
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
    HAL_UART_DMAStop(&huart1);                                                     //中止本次DMA传输
    
    uint8_t data_length  = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   //计算接收到的数据长度

//    printf("Receive Data(length = %d): ",data_length);
   // HAL_UART_Transmit(&huart1,receive_buff,data_length,0x200);                     //测试函数：将接收到的数据打印出去
	
//    printf("\r\n");
	if(cmd_flag == 1)
	{
		cmd_flag = 0;
		res_flag = 1;
	}

    //memset(receive_buff,0,data_length);                                            //清零接收缓冲区
    data_length = 0;
    HAL_UART_Receive_DMA(&huart1, (uint8_t*)receive_buff, 255);                    //重启开始DMA传输 每次255字节数据
}


void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    if(USART1 == huart1.Instance)                                   //判断是不是串口1
    {
        if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //判断是不是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);                     //清楚空闲中断标志（不然会一直不断进入中断）
            //printf("\r\nUART1 Idle IQR Detected\r\n");
            USAR_UART_IDLECallback(huart);                          //调用中断处理函数
        }
    }
}


//==========================================================
//	函数名称：	ReviceCmd
//
//	函数功能：	查找接收数据中是否有cmd数据
//
//	入口参数：	res：需要检查的返回指令
//				data：接收数据缓存
//
//	返回参数：	0-成功	1-失败
//
//	说明：		
//==========================================================
uint8_t USART_ReviceCmd(char *res,char *data)
{	

	if(strstr((const char *)data, res) != NULL)		//如果检索到关键词
		return 0;
	else
		return 1;
}

//==========================================================
//	函数名称：	ESP8266_SendCmd
//
//	函数功能：	发送命令
//
//	入口参数：	cmd：命令
//				res：需要检查的返回指令
//
//	返回参数：	0-成功	1-失败
//
//	说明：		
//==========================================================

uint8_t USART_SendCmd(char *cmd, char *res)
{	
	uint32_t timeOut = 100;

	HAL_UART_Transmit_DMA(&huart1, (uint8_t *)cmd,strlen(cmd)); //发送命令
	cmd_flag = 1;	
	while(timeOut--)
	{
		if(res_flag == 1)//如果收到数据
		{
			res_flag = 0;
			if(USART_ReviceCmd(res,(char *)receive_buff) == 0)
			{
				//printf("OK\r\n");	
				return 0;				
			}
//			else
//			{
//				//printf("fail\r\n");	
//				return 1;
//			}
				
		}	
		vTaskDelay(50);
	}	
	return 1;
}









