#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

/**
 * 
 * @code{cpp}
 * void OS_1000ms_task_c0(void *pvParameters)
 * @endcode
 *@brief Creates a new 1000ms task for the scheduler in FreeRTOS. This task is created using xTaskCreate and is executed every 100s0ms.
 * @param pvParameters Pointer to task parameters. As of now task parameters in NUL
 * 
 *
 *
 *
 * 
 * \ingroup cyclic_tasks
 */
extern void OS_1000ms_task_c1(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay1000ms);
	}
}
