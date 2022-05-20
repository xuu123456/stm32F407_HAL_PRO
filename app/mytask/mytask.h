#ifndef _MY_TASK_
#define _MY_TASK_
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdio.h"
#define LED_TASK_TASK_PRIO		2
#define LED_TASK_STK_SIZE 		50  
extern TaskHandle_t Led_Task_Handler;
void led_task(void *pvParameters);
void Wifi_Task(void *p_agument);
void Wifi_CreateTask(void);
typedef struct
{
	TaskHandle_t wifi_task_handler  ;
	TaskHandle_t mode_task_handler  ;
	TaskHandle_t movement_task_handler;
	TaskHandle_t devbus_task_handler;
	TaskHandle_t debug_task_handler;
	TaskHandle_t calc_task_handler;
	
	TaskHandle_t imu_new_task_handler;

	uint32_t cpu_cycle;
} TaskStruct_t;

#endif
