#include "Memif.h"

sttag_Memif V_sttag_Memif; 
/*externed in NVM to get the job status. Want to avoid the virtual keyword*/
entag_Nvm_States V_entag_Nvm_States_memif_if; 
void MemIf_MainFunction()
{
    MemIf obj_memif_class; 
    obj_memif_class.MemIf_Interface_function();
    
} 


void MemIf:: Set_Memif_status(entag_Nvm_States state ,entag_Nvm_States *ptr_nvm)
{
    if(ptr_nvm != nullptr)
    {
        *ptr_nvm = state;  
    }
    else 
    {

    }
}

void MemIf:: MemIf_Interface_function()
{
    //sttag_Memif Memif_data;
   uint8_t status = Get_Job_Requested_From_NVM(V_sttag_Memif.block_name, V_sttag_Memif.ptr_data , V_sttag_Memif.operation); 
   if(status == E_OK)
   {
        if(V_sttag_Memif.job_status == NO_JOB_REQUESTED)
        {
          
            Set_Memif_status(NVM_BUSY , &V_entag_Nvm_States_memif_if); 
            V_sttag_Memif.job_status = JOB_ACCEPTED; 
        }
        else
        {

        }
        
   }
   else 
   {
      /*Either Queue is empty or something is wrong with the block*/
   }
    

}



void MemIf :: Send_Data_SdCard(sttag_Memif *memif_jobstat)
{
    memif_jobstat = &V_sttag_Memif; 
}

void  MemIf :: set_job_status_sdcard(entag_Nvm_States job_status_sdcard)
{
    //V_sttag_Memif.job_status = job_status_sdcard; 
}

void  MemIf :: set_operation_status_sdcard(entag_Nvm_States job_status_sdcard)
{
    V_sttag_Memif.operation_status = job_status_sdcard; 
}






