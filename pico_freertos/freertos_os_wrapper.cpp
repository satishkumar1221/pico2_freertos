#include <stdio.h>
#include "pico/stdlib.h"

/*Fix me : As of now only included in this file. Including in other files causes erros . Hence scheduler function have to written here. */
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"
#include "Os_usr.h"

//xTaskCreate(temp_func, "temp", 1024, NULL, 4, NULL);
typedef struct
{
   TaskFunction_t func_ptr_task;
   const char *pc_name; 
    const uint32_t stack_depth; 
    void * const pvParameters;
    unsigned long uxPriority;
    TaskHandle_t * const pxCreatedTask; 
}sttag_task_config_struct; 


TaskHandle_t V_taskhandle_c0[TOTAL_NUMBER_OF_TASKS_C0]; 
TaskHandle_t V_taskhandle_c1[TOTAL_NUMBER_OF_TASKS_C1];
//fix me : have to make it more better based  
//xTaskCreate(temp_func, "temp", 1024, NULL, 4, NULL);

 const sttag_task_config_struct C_OS_Cyclictasks[TOTAL_NUMBER_OF_TASKS_C0] = 
 {
    /*core 0 related tasks*/
    {Os(20,0)  ,"20ms_task", TASK_STACK_DEPTH(20,0)   , NULL , TASK_Prio(20,0)   , &V_taskhandle_c0[task_20ms_c0]   },
    {Os(50,0)  , "50ms_task",TASK_STACK_DEPTH(50,0)   , NULL , TASK_Prio(50,0)   , &V_taskhandle_c0[task_50ms_c0]   },
    {Os(100,0) , "100ms_task",TASK_STACK_DEPTH(100,0)  , NULL , TASK_Prio(100,0)  , &V_taskhandle_c0[task_100ms_c0]  }, 
    {Os(1000,0), "1000ms_task",TASK_STACK_DEPTH(1000,0) , NULL , TASK_Prio(1000,0) , &V_taskhandle_c0[task_1000ms_c0] }, 
    {Os(2000,0), "2000ms_task", TASK_STACK_DEPTH(2000,0) , NULL , TASK_Prio(2000,0) , &V_taskhandle_c0[task_2000ms_c0] }
    /*core 1 related tasks*/
 };


  

OS_start::OS_start()
{
    OS_startup_code();

}

void OS_start:: start_scheduler()
{
    int core_num = get_core_num(); 
    uint8_t itr = 0; 
    if(core_num == 0)
    {
       for(itr  = 0 ; itr< TOTAL_NUMBER_OF_TASKS_C0 ; itr++)
       {
         xTaskCreate(C_OS_Cyclictasks[itr].func_ptr_task , C_OS_Cyclictasks[itr].pc_name , C_OS_Cyclictasks[itr].stack_depth , C_OS_Cyclictasks[itr].pvParameters,
                        C_OS_Cyclictasks[itr].uxPriority   ,  C_OS_Cyclictasks[itr].pxCreatedTask);
       }

       vTaskStartScheduler(); 
       /*the control should not come here */
         while (1) {

    }
    }
    
}





