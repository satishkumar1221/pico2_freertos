/******************************************************************************
 * File:        task_20ms_c1.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        6/10/2025
 * Description:  cyclic task 20ms for core 1 is run here.  
 *
 * Revision History: 
 *   <06/10/2025> - 1.0 : File created and modified to start core0 and core1 cyclic tasks :satish kumar 
 *  
 ******************************************************************************/


/**
 * @file task_20ms_c1.cpp
 * @brief Contains the 20ms periodic task implementation for FreeRTOS.
 */

#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"



uint32_t V_Os_Task_Counter_20ms_c1 = 0; 

/**
 * @brief 20ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 20ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */


void OS_20ms_task_c1(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay20ms = pdMS_TO_TICKS(20);
	for(;;)
	{
		V_Os_Task_Counter_20ms_c1++; 
		vTaskDelayUntil( &xLastWakeTime, xDelay20ms);
	}
}

