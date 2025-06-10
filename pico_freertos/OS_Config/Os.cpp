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
