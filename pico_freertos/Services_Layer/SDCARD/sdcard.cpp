#include "sdcard.h"
#include "INFRA\API_LIB\crc16.h"
/*Internal cache block to identify if the data is writtena fter being configured*/

using namespace std;



#define CRC_HEADER_SIZE 2U
uint32_t V_Internalblock_cache[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED]; 

sttag_Memif V_Sttag_Memif_Request; 
entag_fee_hl V_entag_sdcard_state = no_operation_sdcard; 

Data_packet V_sttag_sdcard_packet;

static uint8_t lock_packet; 

#define LOCK_DATA(x) *x = true
#define UNLOCK_DATA(x) *x = FALSE

/* @brief Triggers the SD card read operation via the state machine.
 *
 * This function initiates a read request for a specific block by invoking the state machine
 * (`sdcard_Statemachine_HL`) with the provided block name and memory interface request.
 *
 * @param block_name   The identifier of the SD card block to be read.
 */
void SD_Card_Interface :: Read_Data_Sdcard(uint16_t block_name)
{
       sdcard_Statemachine_HL(block_name , &V_Sttag_Memif_Request); 
}

void SD_Card_Interface :: Write_Data_Sdcard(uint16_t block_name)
{
     sdcard_Statemachine_HL(block_name , &V_Sttag_Memif_Request);
}


void SD_Card_Interface :: Recieve_Data_MemIf(sttag_Memif *memif_jobstat)
{
    MemIf obj_memif; 
    obj_memif.Send_Data_SdCard(memif_jobstat); 

    if(memif_jobstat->operation == read)
    {
        Read_Data_Sdcard(memif_jobstat->block_name);
    }

    else if(memif_jobstat->operation == write)
    {
         Write_Data_Sdcard(memif_jobstat->block_name);
    }
}


void SD_Card_Interface ::process_sd_card_request()

{
    Recieve_Data_MemIf(&V_Sttag_Memif_Request); 

}



 /* @brief Main function for SD card operations.
 *
 * This function initializes an instance of the SD_Card_Interface class and triggers
 * the processing of SD card requests. It is designed to act as a central entry point
 * for handling SD card interactions.
 *
 */
void sd_card_main_function()
{
    SD_Card_Interface obj_sd_card_main_function; 
    obj_sd_card_main_function.process_sd_card_request(); 
    #if 0
    sdcard_Statemachine_HL(); 
    #endif 
}

/**
 * @brief State machine for handling SD card operations.
 *
 * This function implements a finite state machine to manage SD card interactions.
 * It processes requests based on the operation type, transitions through states
 * (e.g., read, write, pack_data, trigger_write), and ensures proper data handling.
 *
 * @param block_name   The identifier for the block being processed.
 * @param memif_job    Pointer to the memory interface job structure containing operation details.
 */

void SD_Card_Interface ::sdcard_Statemachine_HL(uint16_t block_name , sttag_Memif *memif_job )
{
    static bool sticky_flag; 
    if(sticky_flag == false )
    {
        V_entag_sdcard_state = static_cast<entag_fee_hl>(memif_job->operation); 
        sticky_flag = true; 
    }
    switch(V_entag_sdcard_state)
    {
        case read_sdcard : break; 

        case write_sdcard :  V_entag_sdcard_state = pack_data; 
                     break; 

        case pack_data : Pack_header_Struct(memif_job); 
                         Pack_UserData_CRC(memif_job);   
                         V_entag_sdcard_state = trigger_write; 
                         break; 

        case unpack_data :   break; 

        case trigger_write :   
                             break; 

        case trigger_read :  break; 

        case result :
                         break; 

        case no_operation_sdcard :  sticky_flag = false;  break; 
        
        default     :  sticky_flag = false;   break; 
        
    }
      
}

void SD_Card_Interface :: Pack_header_Struct(sttag_Memif *memif_job)
{
    CRC16 obj_crc_16; 
    V_sttag_sdcard_packet.header.pattern = HEADER_PATTERN; 
    V_sttag_sdcard_packet.header.size = memif_job->size; 
    static_assert(sizeof(header_Struct) == 6,"header_Struct must be exactly 6 bytes");

    V_sttag_sdcard_packet.header.CRC = obj_crc_16.processBuffer((reinterpret_cast<const uint8_t*>(&V_sttag_sdcard_packet.header)) ,  ((sizeof(V_sttag_sdcard_packet.header)) -CRC_HEADER_SIZE)); 


}
 
void SD_Card_Interface :: Pack_UserData_CRC(sttag_Memif *memif_job)
{
    
}
 


