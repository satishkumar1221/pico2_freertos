
/**
 * @file task_20ms_c0.cpp
 * @brief Contains the 20ms periodic task implementation for FreeRTOS.
 */

#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

#include "apilib.h"
#include "memlib.h"
uint32_t V_Os_Task_Counter_20ms = 0; 

/**
 * @brief 20ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 20ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */

 uint32_t V_bitset = 0;
uint32_t src = 0xAABBCCDD; 
void OS_20ms_task_c0(void *pvParameters)
{
	
    TickType_t xLastWakeTime = xTaskGetTickCount ();
	#if 0 /*Test code for librareis will have a test folder later on*/
	MemLib lib; 
	lib.memcopy_overlapprotection(&V_bitset,&src,sizeof(src));
	API_LIB<uint32_t>temp ;
	lib.memzero(&V_bitset,sizeof(src)); 
	temp.set_bits(&V_bitset,(static_cast<uint32_t>(3)));
	#endif  
    const TickType_t xDelay20ms = pdMS_TO_TICKS(20);
	for(;;)
	{
		V_Os_Task_Counter_20ms++; 
		
		vTaskDelayUntil( &xLastWakeTime, xDelay20ms);
	}
}

