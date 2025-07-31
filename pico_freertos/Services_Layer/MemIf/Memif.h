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
    entag_Nvm_States operation_status; 
    uint8_t job_status; 
    uint16_t size; 
    /* data */
}sttag_Memif;

extern sttag_Memif V_sttag_Memif; 


class MemIf : public NVM_Class 
{
    public :  
    void Get_Memif_status(); 
    void Set_Memif_status(entag_Nvm_States state ,entag_Nvm_States *ptr_nvm); 
    void Set_NVM_status(); 
    void Get_NVM_Status();  
    void MemIf_Interface_function(); 
    void Send_Data_SdCard(sttag_Memif *memif_jobstat);
    
    void set_job_status_sdcard(entag_Nvm_States job_status_sdcard); 

    void set_operation_status_sdcard(entag_Nvm_States job_status_sdcard); 
    /**
 * @brief Overrides the base class method to check the current status of an NVM operation.
 *
 * This function provides a specific implementation for NVM (Non-Volatile Memory) devices. It checks the operational
 * status of an NVM operation and returns the result as an `entag_Nvm_States` value.
 *
 * @return The current status of the NVM operation:
 * - `E_OK`: Indicates a successful or valid state.
 * - Other values: May include error conditions or specific states defined in `entag_Nvm_States`.
 */
    entag_Nvm_States checkStatusInMemIf() const override 
    {
        return(V_sttag_Memif.operation_status); // Will use SDCard’s override if called via SDCard instance.    
    }
    
    
    private : 
     
    protected :

}; 

/*Function used for calling cyclically in the cyclic task. Done to avoid efficient object managemet. 
Creating objects to call functiosn takes up stack spacce*/


extern void MemIf_MainFunction(); 

#endif