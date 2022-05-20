#include "mytask.h"
#include "My_usart.h"
#define WIFI_TASK_STK_SIZE             200		

static TaskStruct_t MytaskHandle;

void Wifi_CreateTask(void)
{
	portBASE_TYPE xTaskStatus;
	xTaskStatus = xTaskCreate(Wifi_Task,"Wifi_Task",WIFI_TASK_STK_SIZE,NULL,osPriorityAboveNormal,&MytaskHandle.wifi_task_handler);
	if (xTaskStatus != pdPASS)
	{
		printf("Error,Wifi_Task create fail!!\n");
	}
}

void Wifi_Task(void *p_agument)
{
	portTickType xLastWakeTime = xTaskGetTickCount();;		
	while (1)
	{	
//		if(USART_SendCmd("AT+RST\r\n","WIFI GOT IP")==0)
//		if(USART_SendCmd("AT+RST\r\n","ready")==0)
//		{
////			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);
//			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_5);
//		}
		HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_2);
		vTaskDelay(500);
	}
}


