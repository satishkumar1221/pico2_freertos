#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"
extern void OS_1000ms_task_c0(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay1000ms);
	}
}
