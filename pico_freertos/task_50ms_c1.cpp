/******************************************************************************
 * File:        task_50ms_c1.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        6/10/2025
 * Description:  cyclic task 50ms for core 1 is run here.  
 *
 * Revision History: 
 *   <06/10/2025> - 1.0 : File created and modified to start core0 and core1 cyclic tasks :satish kumar 
 *  
 ******************************************************************************/


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
 