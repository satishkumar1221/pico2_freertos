/******************************************************************************
 * File:        task_100ms_c1.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        6/10/2025
 * Description:  cyclic task 100ms for core 1 is run here.  
 *
 * Revision History: 
 *   <06/10/2025> - 1.0 : File created and modified to start core0 and core1 cyclic tasks :satish kumar 
 *  
 ******************************************************************************/


#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

uint32_t V_Os_Task_Counter_100ms_c1 = 0; 


/**
 * 
 *
 * @brief Creates a new 100ms task for the scheduler in FreeRTOS. This task is created using xTaskCreate and is executed every 100ms.
 * @param pvParameters Pointer to task parameters. As of now task parameters in NULL
 * Create a new 100ms function called by the scheduler in from th efreertos. Used xtaskcrete to create the tasks  *
 *  @code{cpp}
 * {
  *  TickType_t xLastWakeTime = xTaskGetTickCount ();
 *   const TickType_t xDelay100ms = pdMS_TO_TICKS(100);
*	for(;;)
*	{
	*	V_Os_Task_Counter_100ms++;
	*	vTaskDelayUntil( &xLastWakeTime, xDelay100ms);
*	}
 * @endcode
 *
 *
 * 
 * \ingroup cyclic_tasks
 */

extern void OS_100ms_task_c1(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay100ms = pdMS_TO_TICKS(100);
	for(;;)
	{
		V_Os_Task_Counter_100ms_c1++;
		vTaskDelayUntil( &xLastWakeTime, xDelay100ms);
	}
}
