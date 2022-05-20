#include "sys.h"
#include "My_usart.h"
#include "string.h"
static uint8_t cmd_flag;//����������֮�󣬴�Ϊ��1
static uint8_t res_flag;//�����յ����ݣ���λΪ1��
#if 1
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (uint8_t) ch;      
	return ch;
}
#endif 
extern UART_HandleTypeDef huart1;
extern uint8_t receive_buff[255];    
extern DMA_HandleTypeDef hdma_usart1_rx;//�����ⲿ���� 
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
    HAL_UART_DMAStop(&huart1);                                                     //��ֹ����DMA����
    
    uint8_t data_length  = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   //������յ������ݳ���

//    printf("Receive Data(length = %d): ",data_length);
   // HAL_UART_Transmit(&huart1,receive_buff,data_length,0x200);                     //���Ժ����������յ������ݴ�ӡ��ȥ
	
//    printf("\r\n");
	if(cmd_flag == 1)
	{
		cmd_flag = 0;
		res_flag = 1;
	}

    //memset(receive_buff,0,data_length);                                            //������ջ�����
    data_length = 0;
    HAL_UART_Receive_DMA(&huart1, (uint8_t*)receive_buff, 255);                    //������ʼDMA���� ÿ��255�ֽ�����
}


void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    if(USART1 == huart1.Instance)                                   //�ж��ǲ��Ǵ���1
    {
        if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //�ж��ǲ��ǿ����ж�
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);                     //��������жϱ�־����Ȼ��һֱ���Ͻ����жϣ�
            //printf("\r\nUART1 Idle IQR Detected\r\n");
            USAR_UART_IDLECallback(huart);                          //�����жϴ�����
        }
    }
}


//==========================================================
//	�������ƣ�	ReviceCmd
//
//	�������ܣ�	���ҽ����������Ƿ���cmd����
//
//	��ڲ�����	res����Ҫ���ķ���ָ��
//				data���������ݻ���
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
uint8_t USART_ReviceCmd(char *res,char *data)
{	

	if(strstr((const char *)data, res) != NULL)		//����������ؼ���
		return 0;
	else
		return 1;
}

//==========================================================
//	�������ƣ�	ESP8266_SendCmd
//
//	�������ܣ�	��������
//
//	��ڲ�����	cmd������
//				res����Ҫ���ķ���ָ��
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================

uint8_t USART_SendCmd(char *cmd, char *res)
{	
	uint32_t timeOut = 100;

	HAL_UART_Transmit_DMA(&huart1, (uint8_t *)cmd,strlen(cmd)); //��������
	cmd_flag = 1;	
	while(timeOut--)
	{
		if(res_flag == 1)//����յ�����
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









