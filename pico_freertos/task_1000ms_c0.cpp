/******************************************************************************
 * File:        task_1000ms_c1.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        6/10/2025
 * Description:  cyclic task 1000ms for core 1 is run here.  
 *
 * Revision History: 
 *   <06/10/2025> - 1.0 : File created and modified to start core0 and core1 cyclic tasks :satish kumar 
 *  
 ******************************************************************************/
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
extern void OS_1000ms_task_c0(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);
	for(;;)
	{
		
		vTaskDelayUntil( &xLastWakeTime, xDelay1000ms);
	}
}
