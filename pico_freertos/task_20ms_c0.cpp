#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

uint32_t V_Os_Task_Counter_20ms = 0; 
void OS_20ms_task_c0(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay20ms = pdMS_TO_TICKS(20);
	for(;;)
	{
		V_Os_Task_Counter_20ms++; 
		vTaskDelayUntil( &xLastWakeTime, xDelay20ms);
	}
}

