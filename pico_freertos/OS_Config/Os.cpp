/******************************************************************************
 * File:        Os.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        6/10/2025
 * Description:  Contaoins functions of OS class. All the functions are intilized form here.  
 *
 * Revision History: 
 *   <06/08/2025> - 1.0 : Initlial version :satish kumar 
* 
 *  
 ******************************************************************************/
#include "../Os_usr.h"
//#include "../HAL/DMA/dma_hal.h"

/*Global variables. Should not be destroyed. Hence not using any unioque pointers. Low level code*/
//#include "../Services_Layer/NVM/Nvm_class.h"


void OS_start :: OS_startup_code(void)
{
    Initlize_const_tables(); 
    Initlize_Ram_Lowleveldriver(); 
    Initlize_ASW_Components();
    Initlize_CDD_Components(); 
    Initlize_ServiceLayer_Components(); 
    start_scheduler(); 


}




void OS_start:: Initlize_Ram_Lowleveldriver()
{
    DMA_config object_DMA_Config; 
    Digital_input_output object_dio; 
    object_DMA_Config.DMA_Init(); 
    object_dio.Digital_input_output_init(); 
}

void OS_start:: Initlize_ASW_Components()
{
    
}

/*TO DO: To create a interface file for the OS . This is a temporary fix :Kumar Satish */
extern void  Init_NVM();
void OS_start:: Initlize_ServiceLayer_Components()
{
     Init_NVM(); 
}


void OS_start:: Initlize_CDD_Components()
{
        
}

void OS_start:: Initlize_const_tables()
{

}
