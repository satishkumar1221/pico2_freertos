#pragma once 
#ifndef _OS_USR_H_
#define _OS_USR_H_

#include "HAL/DMA/dma_hal.h"
//#include "HAL/SPI/spi_hal.h"
//#include "INFRA/API_LIB/apilib.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "FreeRTOS.h"
//#include "task.h"
#include "HAL/DIO/dio.h"
//

extern void OS_startup(); 

extern void Start_OS(); 

#define TOTAL_NUMBER_OF_CORES 2 
#define CORE0 0u
#define CORE1 0u 


#define Os(x,c) OS_##x##ms_task_c##c 

#define TASK_STACK_DEPTH(x,c) TASK_STACK_DEPTH_##x##ms_core##c

#define TASK_Prio(x,core) TASK_Prio_##x##ms_core##core

/*Define the task prio for newly created tasks */
#define TASK_Prio_20ms_core0 4
#define TASK_Prio_50ms_core0 4
#define TASK_Prio_100ms_core0 4
#define TASK_Prio_1000ms_core0 4
#define TASK_Prio_2000ms_core0 4
/*Define the task prio for newly created tasks */
#define TASK_Prio_20ms_core1 4
#define TASK_Prio_50ms_core1 4
#define TASK_Prio_100ms_core1 4
#define TASK_Prio_1000ms_core1 4
#define TASK_Prio_2000ms_core1 4

/*Stack depth configuration for individual tasks*/

#define TASK_STACK_DEPTH_20ms_core0 1024 
#define TASK_STACK_DEPTH_50ms_core0 1024 
#define TASK_STACK_DEPTH_100ms_core0 1024 
#define TASK_STACK_DEPTH_1000ms_core0 1024 
#define TASK_STACK_DEPTH_2000ms_core0 1024 

#define TASK_STACK_DEPTH_20ms_core1 1024 
#define TASK_STACK_DEPTH_50ms_core1 1024 
#define TASK_STACK_DEPTH_100ms_core1 1024 
#define TASK_STACK_DEPTH_1000ms_core1 1024 
#define TASK_STACK_DEPTH_2000ms_core1 1024 

typedef enum 
{
   task_20ms_c0, 
   task_50ms_c0, 
   task_100ms_c0, 
   task_1000ms_c0, 
   task_2000ms_c0, 
   TOTAL_NUMBER_OF_TASKS_C0
}tasks_core0;  

typedef enum 
{
   task_20ms_c1, 
   task_50ms_c1, 
   task_100ms_c1, 
   task_1000ms_c1, 
   task_2000ms_c1, 
   TOTAL_NUMBER_OF_TASKS_C1
}tasks_core1;  

/*Extern OS functions*/


/**
 * @brief 20ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 20ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_20ms_task_c0(void *pvParameters); 


/**
 * @brief 50ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 50ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_50ms_task_c0(void *pvParameters);

/**
 * @brief 100ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 100ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
/**
 * @brief 100ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 100ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_100ms_task_c0(void *pvParameters);

/**
 * @brief 1000ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 1000ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_1000ms_task_c0(void *pvParameters);
/**
 * @brief 2000ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 2000ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_2000ms_task_c0(void *pvParameters); 



/**
 * @brief 20ms periodic task for FreeRTOS scheduler for core 1 .
 * 
 * This task increments a counter and delays for 20ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_20ms_task_c1(void *pvParameters); 


/**
 * @brief 50ms periodic task for FreeRTOS scheduler for core 1.
 * 
 * This task increments a counter and delays for 50ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_50ms_task_c1(void *pvParameters);

/**
 * @brief 100ms periodic task for FreeRTOS scheduler for core 1 .
 * 
 * This task increments a counter and delays for 100ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
/**
 * @brief 100ms periodic task for FreeRTOS scheduler.
 * 
 * This task increments a counter and delays for 100ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_100ms_task_c1(void *pvParameters);

/**
 * @brief 1000ms periodic task for FreeRTOS scheduler for core 1.
 * 
 * This task increments a counter and delays for 1000ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_1000ms_task_c1(void *pvParameters);
/**
 * @brief 2000ms periodic task for FreeRTOS scheduler for core 1.
 * 
 * This task increments a counter and delays for 2000ms in each loop iteration.
 * 
 * @param[in] pvParameters Pointer to task parameters (currently unused, should be NULL).
 * @return None
 */
extern void OS_2000ms_task_c1(void *pvParameters); 




class OS_start : public DMA_config 
{
    public :
    OS_start();
    void OS_startup_code(void);
    private :
    
    void Initlize_const_tables(); 
    void Initlize_Ram_Lowleveldriver();
    void Initlize_ASW_Components();
    void Initlize_CDD_Components(); 
    void start_scheduler(); 
    void Initlize_ServiceLayer_Components(); 
    

}; 
#endif 