#ifndef MEMIF_H
#define MEMIF_H

#include "Nvm_class.h"

#define JOB_ACCEPTED 1U 
#define JOB_REJECTED 2U 
#define NO_JOB_REQUESTED 0U 


typedef struct Memif
{
    uint16_t block_name; 
    uint8_t *ptr_data; 
    uint8_t operation;
    uint8_t operation_status; 
    uint8_t job_status; 
    /* data */
}sttag_Memif;


class MemIf : public NVM_Class 
{
    public :  
    void Get_Memif_status(); 
    void Set_Memif_status(entag_Nvm_States state ,entag_Nvm_States *ptr_nvm); 
    void Set_NVM_status(); 
    void Get_NVM_Status();  
    void MemIf_Interface_function(); 
    void Send_Data_SdCard(sttag_Memif *memif_jobstat); 
    
    private : 
     
    protected :

}; 

/*Function used for calling cyclically in the cyclic task. Done to avoid efficient object managemet. 
Creating objects to call functiosn takes up stack spacce*/


extern void MemIf_MainFunction(); 

#endif