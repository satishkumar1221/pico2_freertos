#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

#include "HAL/ADC/adc.h"

/**
 *  @brief Creates a new 50ms task for the scheduler in FreeRTOS. This task is created using xTaskCreate and is executed every 50ms.
 * @param pvParameters Pointer to task parameters. As of now task parameters in NULL
 * @code{cpp}
 *  TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay50ms = pdMS_TO_TICKS(50);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay50ms);
	}
 * @endcode

 * @ingroup cyclic_tasks
 */

void OS_50ms_task_c1(void *pvParameters)
{
   TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay50ms = pdMS_TO_TICKS(50);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay50ms);
	}
}
 