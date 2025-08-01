
/**
 * @file task_20ms_c0.cpp
 * @brief Contains the 20ms periodic task implementation for FreeRTOS.
 */

#include "Os_usr.h"
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"

#include "apilib.h"
#include "memlibrary.h"
#include "queue_custom.h"

#include "../Services_Layer/NVM/Nvm_class.h"
#include "../Services_Layer/MemIf/Memif.h"
#include "../Services_Layer/SDCARD/sdcard.h"
uint32_t V_Os_Task_Counter_20ms = 0; 

uint8_t stickyflag; 
/**
 * @brief 20ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 20ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */


uint16_t V_arr_queue[5]; 
uint16_t test_data[5] = {1,2,3,4,5};
//Queue_stat stat; 


 uint32_t V_bitset = 0;
uint32_t src = 0xAABBCCDD; 
 
void OS_20ms_task_c0(void *pvParameters)
{
	
    TickType_t xLastWakeTime = xTaskGetTickCount ();

    const TickType_t xDelay20ms = pdMS_TO_TICKS(20);
	for(;;)
	{
		V_Os_Task_Counter_20ms++; 
            /*NVM should be calle first */
    NVM_MainFunction();
    /*MemIf should be called later on. MemIf should never be called befor NVM as the data validation is done as a part of NVM */ 
    MemIf_MainFunction(); 
    /*sd card main function to process the request related to sd card . As filesytem is not used user must specify the persistant ID of the blocks or can be auto generated*/
    sd_card_main_function(); 
		
		vTaskDelayUntil( &xLastWakeTime, xDelay20ms);
	}
}

