#include "../Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

extern void OS_2000ms_task_c0(void *pvParameters)
{
     TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay2000ms = pdMS_TO_TICKS(2000);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay2000ms);
	}
}