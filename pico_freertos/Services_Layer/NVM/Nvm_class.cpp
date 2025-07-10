#include "Nvm_class.h"
#include <iostream>
using namespace std; 

stTag_NVM_userbuffer V_stTag_NVM_userbuffer[NVM_BUFFER_SIZE]; 

/* Gives infiormation about the job beign processed  */
stTag_NVM_Internal V_stTag_NVM_Internal_prv_status; 

/**
 * @brief Initializes the NVM module and its internal data structures.
 *
 * This method initializes buffers, sets up the internal status structure, and resets other necessary variables.
 */
void NVM_Class :: NVM_Init()
{
    Initlize_Buffers(); 
    Queue obj_queue;
    V_stTag_NVM_Internal_prv_status.nvm_status = NVM_OK; 
    V_stTag_NVM_Internal_prv_status.ptr_current_buffer_processed = nullptr; /*No buffer is being currently processed*/
    V_stTag_NVM_Internal_prv_status.ptr_internal_Buffer = V_stTag_NVM_userbuffer[0].ptr_usr_buffer;
}



void NVM_Class :: NVM_ReadAll_sdcard()
{ 
       
}

void NVM_Class :: NVM_Writeall_sdcard()
{

}       


void NVM_MainFunction()
{
    
}

/**
 * @brief Writes data to a specific block on the SD card.
 *
 * This method prepares a user operation structure and enqueues it in the NVM queue.
 * The block number, operation type (write), and data pointer are set accordingly.
 *
 * @param block_number The block number to write data to on the SD card.
 * @param data A pointer to the data buffer containing the data to be written.
 */

void NVM_Class :: write_Data_sdcard(uint8_t block_number , uint8_t *data)
{
     stTag_NVM_userbuffer user_operation; 
     user_operation.block_number = block_number; 
     user_operation.operation_type = write; 
     user_operation.ptr_usr_buffer = data; 
     push_element_queue(NVM_Queue, data);  /*Not required to crate objects as NVM inherits queue*/
    
}

/**
 * @brief Initializes buffers and sets up the NVM user buffer queue.
 *
 * This method initializes the `V_stTag_NVM_userbuffer` array as a queue with specified size and capacity,
 * utilizing the fact that the `NVM_Class` inherits from the Queue class.
 */

void NVM_Class :: Initlize_Buffers()
{
    Queue_init(V_stTag_NVM_userbuffer , NVM_Queue , sizeof(V_stTag_NVM_userbuffer) , ((sizeof(V_stTag_NVM_userbuffer)) / (sizeof(V_stTag_NVM_userbuffer[0])))); /*Not required to crate objects as NVM inherits queue*/
}


uint8_t NVM_Class :: Get_Job_Requested_From_NVM(uint16_t block_name , uint8_t *ptr_data  , uint8_t operation)
{
    stTag_NVM_userbuffer user_operation;
    Queue_stat status_queue = Get_Queue_Status(NVM_Queue); 
    uint8_t return_type;

    if(status_queue != QUEUE_EMPTY)
    {
        (void)peek_element_queue(NVM_Queue, &user_operation); /*Not required to create objects as NVM inherits queue*/
        block_name = user_operation.block_number; 
        operation = user_operation.operation_type; 
        ptr_data =  user_operation.ptr_usr_buffer; 
        return_type = E_OK; 
    }

    else 
    {
       return_type = E_NOT_OK; 
    }

    return(return_type); 
    // block_name = V_ 
} 
