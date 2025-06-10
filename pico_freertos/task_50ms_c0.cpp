#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

void OS_50ms_task_c0(void *pvParameters)
{
   TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay50ms = pdMS_TO_TICKS(50);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay50ms);
	}
}
 