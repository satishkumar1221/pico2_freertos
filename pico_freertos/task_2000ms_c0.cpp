#include "../Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

/**
 * 
 * @code{cpp}
 * void OS_2000ms_task_c0(void *pvParameters)
 * @endcode
 *
 * Create a new 2000ms function called by the scheduler in from th efreertos. Used xtaskcrete to create the tasks  *
 *
 * @brief Creates a new 2000ms task for the scheduler in FreeRTOS. This task is created using xTaskCreate and is executed every 2000ms.
 * @param pvParameters Pointer to task parameters. As of now task parameters in NUL
 *
 *
 * 
 * \ingroup Cyclictasks_c0
 */

extern void OS_2000ms_task_c0(void *pvParameters)
{
     TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay2000ms = pdMS_TO_TICKS(2000);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay2000ms);
	}
}