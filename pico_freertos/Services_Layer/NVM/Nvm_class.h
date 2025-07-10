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

  

    protected : 
  uint8_t  Get_Job_Requested_From_NVM(uint16_t block_name , uint8_t *ptr_data  , uint8_t operation); 

     private : 

};



        /**
     * @fn void NVM_MainFunction(void)
     * @brief The main function of the NVM module.
     */
    void NVM_MainFunction(void);  
#endif