#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

uint32_t V_Os_Task_Counter_100ms = 0; 
extern void OS_100ms_task_c0(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay100ms = pdMS_TO_TICKS(100);
	for(;;)
	{
		V_Os_Task_Counter_100ms++;
		vTaskDelayUntil( &xLastWakeTime, xDelay100ms);
	}
}
