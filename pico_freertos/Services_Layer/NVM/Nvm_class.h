#ifndef NVM_H
#define NVM_H



#include "queue_custom.h"
#include  "memlibrary.h"
#include "apilib.h"
#include "dma_hal.h"
#include "Nvm_cfg.h"

typedef enum 
{
    no_operation, 
    write, 
    read,
    read_all, 
    write_all,
    Total_operations
}entag_nvmoperation; 

typedef struct 
{
    uint8_t *ptr_usr_buffer;
    uint8_t block_number;
    entag_nvmoperation operation_type;
}stTag_NVM_userbuffer; 


typedef enum 
{
   NVM_OK, 
   NVM_BUSY, 
   NVM_INTEGRITY_FAILED,  
   NVM_RESTORED_DEFAULTS, 
   NVM_NOT_OKAY
}entag_Nvm_States;

typedef struct 
{
  uint16_t block_id; 


}sttag_NVM_stat; 
typedef struct 
{
    uint8_t *ptr_internal_Buffer;  
    uint8_t nvm_status;
    stTag_NVM_userbuffer *ptr_current_buffer_processed; 

}stTag_NVM_Internal;

extern entag_Nvm_States V_entag_Nvm_States_memif_if; 
extern stTag_NVM_Internal V_stTag_NVM_Internal_prv_status; 
 /**
 * @class NVM_Class
 */
/**
 * @brief Defines a class for handling non-volatile memory operations.
 */
extern stTag_NVM_Internal V_stTag_NVM_Internal_prv_status;
class NVM_Class : public Queue,public API_LIB<uint8_t>, public DMA_config
{
    public :

      /**
     * @fn void NVM_Init(void)
     * @brief Initializes the NVM module.
     */

    void NVM_Init(void); 

   
 
    /**
 * @brief Checks the current status of a memory interface operation.
 *
 * This virtual function provides an interface to check the current operational status of the memory
 * interface. It is designed to be overridden by subclasses to implement specific status-checking logic.
 *
 * Subclasses should return appropriate values based on the actual state of the memory operation.
 *
 * @return The current status of the memory interface:
 * - `E_OK`: Operation is successful or in a valid state.
 * - Other statuses as defined in `entag_Nvm_States` for error conditions or specific states.
 */
    virtual entag_Nvm_States checkStatusInMemIf() const {
    /* In C++, when you declare a method as const, it signals:
   “This method will not (and cannot) change any member variables of the class (unless they’re marked mutable).”
   
   It's a contract to the compiler that calling getSDCardJobStatus() won’t alter the internal state of the object.
  */ 
      return NVM_OK; // default or stub
    }


    /**
     * @fn void NVM_ReadAll_sdcard(void)
     * @brief Reads all data from the SD card.
     */
    void NVM_ReadAll_sdcard(void);

      /**
     * @fn void NVM_Writeall_sdcard(void)
     * @brief Writes all data to the SD card.
     */
    void NVM_Writeall_sdcard(void); 
     /**
     * @fn uint8_t write_Data_sdcard(uint8_t block_number , uint8_t *data )
     * @brief Writes data to a specific block on the SD card.
     */

    void write_Data_sdcard(uint8_t block_number , uint8_t *data );
    
    /**
     * @fn uint8_t read_Data_sdcard(uint8_t block_number , uint8_t *data )
     * @brief Reads data from a specific block on the SD card.
     */
    uint8_t read_Data_sdcard(uint8_t block_number , uint8_t *data );
     /**
     * @fn uint8_t get_Status_sdcard(uint8_t block_number, uint8_t *ptr_usrvariable)
     * @brief Gets the status of the specified block on the SD card.
     */ 
    uint8_t get_Status_sdcard(uint8_t block_number, uint8_t *ptr_usrvariable);
      /**
     * @fn uint8_t get_current_jobstatus(uint8_t *block_number);
     * @brief Gets the current job status for a specific block.
     */
    uint8_t get_current_jobstatus(uint8_t *block_number);  
    private: 
      /**
     * @fn void Initlize_Buffers(void)
     * @brief Initializes buffers for data operations.
     */
    void Initlize_Buffers(); 
       /**
     * @fn void Send_Data_MemIF(void)
     * @brief Sends data to the memory interface.
     */
    void Send_Data_MemIF(); 

    friend void NVM_MainFunction(); /*Friend function used as I want t access a provate member of the class. NVM_Mainfunction() is a interface function called in RTOS */
    
    entag_nvmoperation Get_MemIf_Status();  
    
    protected : 
      uint8_t  Get_Job_Requested_From_NVM(uint16_t block_name , uint8_t *ptr_data  , uint8_t operation); 

    private : 
    
      uint8_t Validate_Blocks_Queue(uint16_t block_number); 
      void Handle_Internal_NVM_Operations();
    
    void NVM_Prv_MainFunction(); 

};



        /**
     * @fn void NVM_MainFunction(void)
     * @brief The main function of the NVM module.
     */
    void NVM_MainFunction(void);  
#endif