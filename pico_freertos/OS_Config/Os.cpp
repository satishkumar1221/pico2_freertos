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

void OS_start :: OS_startup_code(void)
{
    Initlize_const_tables(); 
    Initlize_Ram_Lowleveldriver(); 
    Initlize_ASW_Components();
    Initlize_CDD_Components(); 
    
    start_scheduler(); 


}


void OS_start:: Initlize_Ram_Lowleveldriver()
{

}

void OS_start:: Initlize_ASW_Components()
{
    
}

void OS_start:: Initlize_CDD_Components()
{
    
}

void OS_start:: Initlize_const_tables()
{

}
