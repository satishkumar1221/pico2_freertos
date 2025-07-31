#ifndef SDCARD_H
#define SDCARD_H 

#include "Memif.h"
#include "dma_hal.h"
/*Currently th  */
#define HEADER_PATTERN 0xFADE
#define END_PATTERN    0xFACE 
extern uint32_t V_Internalblock_cache[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED]; 

#pragma pack(push, 1)


/**
 * @brief Header structure containing packet pattern, size, and CRC.
 *
 * This struct defines the header of a data packet, including:
 * - A unique identifier (`pattern`) for the packet type or version.
 * - The size of the associated data payload.
 * - A CRC value for error detection in the header.
 */

typedef struct 

{
     uint16_t pattern; 
     uint16_t size;
     uint16_t CRC;  
     /* data */
}header_Struct;


#pragma pack(pop)



/**
 * @brief Structure representing a single block of data with associated metadata.
 *
 * This struct contains:
 * - A `header_Struct` for packet identification and size.
 * - A pointer to the user data payload (`ptr_user_data`).
 * - The size of the user data payload.
 * - An end pattern for packet detection.
 * - A CRC value for error detection in the block.
 */
#pragma pack(push, 1)
typedef struct 
{
     header_Struct header; 
     uint8_t  *ptr_user_data;  
     uint16_t size;
     uint16_t end_pattern; 
     uint16_t CRC;
}Block_struct; 
#pragma pack(pop)


/**
 * @brief Structure representing a complete data packet.
 *
 * This struct contains:
 * - A `header_Struct` for packet identification and size.
 * - A `Block_struct` containing the actual data block with its metadata.
 */

#pragma pack(push, 1)
typedef struct 

{
     header_Struct header; 
     Block_struct  block_data;
}Data_packet; 

#pragma pack(pop)


typedef enum 
{
    no_operation_sdcard,
    write_sdcard, /*made it equal to memif nad nvm */
    read_sdcard, /*made it equal to memif nad nvm */
    pack_data, 
    unpack_data, 
    trigger_write,
    trigger_read, 
    result
}entag_fee_hl; 



class SD_Card_Interface : public Memif,DMA_config
{
     public : 
        /**
     * @brief Processes SD card requests via the state machine.
     *
     * This method acts as the entry point for handling SD card operations, triggering the state machine
     * to manage the request lifecycle.
     */
     void process_sd_card_request(); 
     
    /**
     * @brief Receives data from the memory interface.
     *
     * This method handles incoming data from the memory interface, preparing it for processing.
     *
     * @param memif_jobstat Pointer to the memory interface job structure containing data.
     */
     void Recieve_Data_MemIf(sttag_Memif *memif_jobstat); 
      /**
     * @brief Initiates a read operation for a specific SD card block.
     *
     * This method triggers the high-level state machine to read data from the specified block.
     *
     * @param block_name The identifier of the SD card block to read.
     */
     void Read_Data_Sdcard(uint16_t block_name);
       /**
     * @brief Initiates a write operation for a specific SD card block.
     *
     * This method triggers the high-level state machine to write data to the specified block.
     *
     * @param block_name The identifier of the SD card block to write.
     */
     void Write_Data_Sdcard(uint16_t block_name); 
     
     protected  : 

     private : 
      /**
     * @brief Friend function for the main SD card function.
     *
     * This function is a friend of the class, allowing it to access private members for testing or
     * integration purposes.
     */

     friend void sd_card_main_function();

      /**
     * @brief Packs data for SD card transmission.
     *
     * This method prepares raw data for transmission to the SD card, ensuring proper formatting.
     *
     * @param memif_jobstat Pointer to the memory interface job structure containing data.
     * @return uint8_t Status code (1 for success, 0 for failure).
     */

     uint8_t pack_data_sd_card(sttag_Memif *memif_jobstat); 

         /**
     * @brief Validates data before SD card operations.
     *
     * This method checks the integrity of data before it is written to or read from the SD card.
     *
     * @param memif_jobstat Pointer to the memory interface job structure containing data.
     * @return uint8_t Status code (1 for valid, 0 for invalid).
     */

     uint8_t validate_data_sd_card(sttag_Memif *memif_jobstat); 
     /**
     * @brief Unpacks data received from the SD card.
     *
     * This method processes data received from the SD card, preparing it for further use.
     *
     * @param memif_jobstat Pointer to the memory interface job structure containing data.
     * @return uint8_t Status code (1 for success, 0 for failure).
     */

     uint8_t un_pack_data_sd_card(sttag_Memif *memif_jobstat); 

      /**
     * @brief Adds a block header to the data.
     *
     * This method appends a header to the data structure before writing to the SD card.
     *
     * @param memif_jobstat Pointer to the memory interface job structure containing data.
     * @return uint8_t Status code (1 for success, 0 for failure).
     */
    
     uint8_t add_block_header(sttag_Memif *memif_jobstat ); 

      /**
     * @brief Maintains internal SD card blocks.
     *
     * This method manages the internal state of SD card blocks, ensuring consistency and integrity.
     */
     void maintain_internal_blocks(); 

        /**
     * @brief High-level state machine for SD card operations.
     *
     * This state machine handles the overall flow of SD card operations, including read/write,
     * data packing, and state transitions.
     *
     * @param block_name The identifier of the SD card block.
     * @param memif_job Pointer to the memory interface job structure containing operation details.
     */

     void  sdcard_Statemachine_HL(uint16_t block_name , sttag_Memif *memif_job ); 

       /**
     * @brief Low-level state machine for SD card operations.
     *
     * This state machine handles detailed, low-level operations such as data transfer and DMA
     * configuration.
     *
     * @param block_name The identifier of the SD card block.
     * @param memif_job Pointer to the memory interface job structure containing operation details.
     */

     void  sdcard_Statemachine_LL(uint16_t block_name , sttag_Memif *memif_job ); 

     /**
     * @brief Packs the header structure for SD card data.
     *
     * This method prepares the header structure for data to be written to the SD card.
     *
     * @param memif_job Pointer to the memory interface job structure containing data.
     */

     void Pack_header_Struct (sttag_Memif *memif_job); 
     /**
     * @brief Packs user data with CRC for SD card transmission.
     *
     * This method appends CRC (Cyclic Redundancy Check) to user data before writing to the SD card.
     *
     * @param memif_job Pointer to the memory interface job structure containing data.
     */

     void  Pack_UserData_CRC(sttag_Memif *memif_job); 
}; 


void sd_card_main_function(); 



#endif 