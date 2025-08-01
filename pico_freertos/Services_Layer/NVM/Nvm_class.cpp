#include "Nvm_class.h"
#include <iostream>
using namespace std; 

stTag_NVM_userbuffer V_stTag_NVM_userbuffer[NVM_BUFFER_SIZE]; 

/* Gives infiormation about the job beign processed  */
stTag_NVM_Internal V_stTag_NVM_Internal_prv_status; 

stTag_NVM_userbuffer V_stTag_debug_data; 

entag_nvmoperation V_entag_nvm_Operation[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED]; 


//entag_Nvm_States V_entag_Nvm_States_memif_if; 
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


/**
 * @brief Reads all data from the SD card.
 *
 * This function reads all available data from the SD card and performs necessary operations.
 * The specific details of how the data is read and handled are encapsulated within this method.
 *
 * @return A status code indicating success or failure.
 */

void NVM_Class :: NVM_ReadAll_sdcard()
{ 
    
}
/**
 * @brief Writes all data to the SD card.
 *
 * This function is responsible for writing all relevant data to an SD card.
 * It should handle any necessary operations such as opening a file, writing data,
 * and closing the file once the operation is complete.
 *
 * @note Ensure that the SD card is properly initialized before calling this function.
 */

void NVM_Class :: NVM_Writeall_sdcard()
{

}      


void  Init_NVM() 
{
    NVM_Class obj_nvm; 
    obj_nvm.NVM_Init(); 
}



uint8_t NVM_Class :: Validate_Blocks_Queue(uint16_t block_id)
{
    auto status = E_NOT_OK; 
    if((block_id >= 0 ) && (block_id < TOTAL_NUMBER_OF_BLOCKS_CONFIGURED))
    {
        status = E_OK; 
    }
    else 
    {
        status = E_NOT_OK; 
    }
    return(status); 
 }


/**
 * @brief Validates blocks in the NVM queue and processes them based on their status.
 *
 * This private method checks if there are any pending operations in the NVM queue. If so,
 * it retrieves the next user operation structure, validates the corresponding block,
 * and processes it accordingly:
 * - If validation fails, remove the block from the queue and handle the error.
 * - If validation passes, allow the Memory Interface (MemIF) to read the function from the queue.
 *
 * @note This method is intended for internal use within the NVM_Class. It is not meant to be called directly by other classes or functions.
 */
void NVM_Class :: NVM_Prv_MainFunction()
{  
    stTag_NVM_userbuffer usr_buffer;
    auto status = E_NOT_OK;  
    // Check if there are pending operations in the NVM queue
    
      if(QUEUE_EMPTY != Get_Queue_Status(NVM_Queue))
      {
         peek_element_queue(NVM_Queue , &usr_buffer); 
         status = Validate_Blocks_Queue(usr_buffer.block_number); 
         
         if(E_NOT_OK == status)
         {
            pop_element_queue(NVM_Queue , &V_stTag_debug_data); 

            /* Have to write a DET_Module*/
         }

         else 
         {
             /*Do nothing Mem_IF will read the function from the queue */
         }
      }
       
      Handle_Internal_NVM_Operations(); 
}   


void NVM_Class :: Handle_Internal_NVM_Operations()
{
   entag_Nvm_States memof_status = Get_MemIf_Status(); 

 



}

inline entag_Nvm_States NVM_Class ::  Get_MemIf_Status()
{
    return(V_entag_Nvm_States_memif_if);
}

void NVM_MainFunction()
{
    NVM_Class obj_nvm_class; 
     /* Validate all the blocks in the queue. In case of invalid block remove the block from queue */
     obj_nvm_class.NVM_Prv_MainFunction(); 
    
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

/**
 * @brief Retrieves job data from NVM based on the given block name and operation.
 *
 * This method checks if there are any pending operations in the NVM queue. If so,
 * it retrieves the next user operation structure and extracts the relevant data:
 * block number, operation type, and data pointer. The function then returns
 * `E_OK` to indicate success or `E_NOT_OK` if no job was found.
 *
 * @param block_name A pointer to store the retrieved block name with the current job status.
 * @param ptr_data A pointer to store the retrieved data buffer based on the operation type.
 * @param operation The operation type (read/write).
 *
 * @return `E_OK` if the job data was successfully retrieved, or `E_NOT_OK` if no job was found.
 */
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


