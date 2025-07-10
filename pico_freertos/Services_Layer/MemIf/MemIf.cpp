#include "Memif.h"

sttag_Memif V_sttag_Memif; 

void MemIf_MainFunction()
{
    MemIf obj_memif_class; 
    obj_memif_class.MemIf_Interface_function();
    
} 

void MemIf:: MemIf_Interface_function()
{
    //sttag_Memif Memif_data;
   uint8_t status = Get_Job_Requested_From_NVM(V_sttag_Memif.block_name, V_sttag_Memif.ptr_data , V_sttag_Memif.operation); 
   

}





