#ifndef SDCARD_H
#define SDCARD_H

#include "Memif.h"
#include "dma_hal.h"
/*Currently th  */

/*Configurabnle by user */
#define CHAINING_ARRAY_LENGTH 10

#define MEMORY_CARD_SIZE  32 /*Memory card size in GB*/

#define BOOK_KEEPING_BLOCKS               2 /*2GB reserved fo*/
#define CONVERT_GB_TO_BYTES MEMORY_CARD_SIZE * 125000000U

constexpr uint32_t HEADER_PATTERN = 0xFADEFADE;
constexpr uint16_t END_PATTERN = 0xFACE;


constexpr uint16_t SECTOR_SIZE_PHYSICAL =
    512; /*secot size can be changed for external eeproms as well*/
/*Using the uint16_t for alignment.  Uint8_t or enum types will result in me
 * adding paddign or alignment. Wanted to avoid it*/
constexpr uint16_t single_block_operation = (uint16_t)0;
constexpr uint16_t multi_block_operation = (uint16_t)0;


/*cache invalidated stat  */
constexpr uint32_t CACHE_INVALIDATED_BLOCK_NOT_PROGRAMMED = 0xAABBCCDD;
constexpr uint32_t CACHE_AVAILABLE_BLOCK_PROGRAMMED_ONCE = 0x01;

extern uint32_t V_Internalblock_cache[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED];

#if 0
typedef enum 
{
  single_block_operation = (uint8_t) 0 ,   
  multi_block_operation
}block_types;
#endif

typedef enum {
  SDCARD_OK,
  SDCARD_BUSY,
  SDCARD_INTEGRITY_FAILED,
  SDCARD_RESTORED_DEFAULTS,
  SDCARD_NOT_OKAY
} entag_sdcard_States;

// #pragma pack(push, 1)

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
  uint32_t pattern;
  uint32_t size;
  uint64_t address_first_block;
  uint16_t block_type;
  uint16_t block_id;
  uint16_t CRC;
  /* data */
} header_Struct;

// #pragma pack(pop)

/**
 * @brief Structure representing a single block of data with associated
 * metadata.
 *
 * This struct contains:
 * - A `header_Struct` for packet identification and size.
 * - A pointer to the user data payload (`ptr_user_data`).
 * - The size of the user data pay load.
 * - An end pattern for packet detection.
 * - A CRC value for error detection in the block.
 */
#pragma pack(push, 1)
typedef struct {

  header_Struct header;
 // uint8_t  *ptr_reserve_data; /*Removing as it is useless*/
  // uint32_t size;
  uint16_t end_pattern;
  uint16_t CRC;
} Block_struct;

typedef struct {

  header_Struct header;
  // uint8_t  *ptr_user_data; /*Removing as it is useless*/
  // uint32_t size;
  //uint16_t block_id;
  uint64_t
      address_next_block[CHAINING_ARRAY_LENGTH]; /*Only valid for  multi block
                                                    operation 0 for single block
                                                    operations*/
  uint16_t end_pattern;
  uint16_t CRC;
} Block_struct_multiplesectorwrites;
#pragma pack(pop)

/**
 * @brief Structure representing a complete data packet.
 *
 * This struct contains:
 * - A `header_Struct` for packet identification and size.
 * - A `Block_struct` containing the actual data block with its metadata.
 */
#if 0
#pragma pack(push, 1)
typedef struct

{
  header_Struct header;
  Block_struct block_data;
} Data_packet;


typedef struct

{
  header_Struct header;
  Block_struct_multiplesectorwtites block_data;
} Data_packet_multiplesectorwrites;

#pragma pack(pop)
#endif 
typedef enum {
  no_operation_sdcard,
  write_sdcard, /*made it equal to memif nad nvm */
  read_sdcard,  /*made it equal to memif nad nvm */
  pack_data,
  unpack_data,
  trigger_write,
  trigger_read,
  result
} entag_fee_hl;

typedef struct {
  header_Struct header;
  uint32_t cache_value;
  uint32_t cache_address; 
  uint16_t CRC_Value;  

} cache_struct;

extern cache_struct
    NV_cache_struct[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED]; /*strored in nvm. Used
                        for wasy lookup . Mostly used for the nvm_read */

class SD_Card_Interface : public Memif, DMA_config {
public:
  /**
   * @brief Processes SD card requests via the state machine.
   *
   * This method acts as the entry point for handling SD card operations,
   * triggering the state machine to manage the request lifecycle.
   */
  void process_sd_card_request();

  /**
   * @brief Receives data from the memory interface.
   *
   * This method handles incoming data from the memory interface, preparing it
   * for processing.
   *
   * @param memif_jobstat Pointer to the memory interface job structure
   * containing data.
   */
  void Recieve_Data_MemIf(sttag_Memif *memif_jobstat);
  /**
   * @brief Initiates a read operation for a specific SD card block.
   *
   * This method triggers the high-level state machine to read data from the
   * specified block.
   *
   * @param block_name The identifier of the SD card block to read.
   */
  void Read_Data_Sdcard(uint16_t block_name);
  /**
   * @brief Initiates a write operation for a specific SD card block.
   *
   * This method triggers the high-level state machine to write data to the
   * specified block.
   *
   * @param block_name The identifier of the SD card block to write.
   */
  void Write_Data_Sdcard(uint16_t block_name);

protected:
private:
  /**
   * @brief Friend function for the main SD card function.
   *
   * This function is a friend of the class, allowing it to access private
   * members for testing or integration purposes.
   */

  friend void sd_card_main_function();

  /**
   * @brief Packs data for SD card transmission.
   *
   * This method prepares raw data for transmission to the SD card, ensuring
   * proper formatting.
   *
   * @param memif_jobstat Pointer to the memory interface job structure
   * containing data.
   * @return uint8_t Status code (1 for success, 0 for failure).
   */

  uint8_t pack_data_sd_card(sttag_Memif *memif_jobstat);

  /**
   * @brief Validates data before SD card operations.
   *
   * This method checks the integrity of data before it is written to or read
   * from the SD card.
   *
   * @param memif_jobstat Pointer to the memory interface job structure
   * containing data.
   * @return uint8_t Status code (1 for valid, 0 for invalid).
   */

  uint8_t validate_data_sd_card(sttag_Memif *memif_jobstat);
  /**
   * @brief Unpacks data received from the SD card.
   *
   * This method processes data received from the SD card, preparing it for
   * further use.
   *
   * @param memif_jobstat Pointer to the memory interface job structure
   * containing data.
   * @return uint8_t Status code (1 for success, 0 for failure).
   */

  uint8_t un_pack_data_sd_card(sttag_Memif *memif_jobstat);

  /**
   * @brief Adds a block header to the data.
   *
   * This method appends a header to the data structure before writing to the SD
   * card.
   *
   * @param memif_jobstat Pointer to the memory interface job structure
   * containing data.
   * @return uint8_t Status code (1 for success, 0 for failure).
   */

  uint8_t add_block_header(sttag_Memif *memif_jobstat);

  /**
   * @brief Maintains internal SD card blocks.
   *
   * This method manages the internal state of SD card blocks, ensuring
   * consistency and integrity.
   */
  void maintain_internal_blocks();

  /**
   * @brief High-level state machine for SD card operations.
   *
   * This state machine handles the overall flow of SD card operations,
   * including read/write, data packing, and state transitions.
   *
   * @param block_name The identifier of the SD card block.
   * @param memif_job Pointer to the memory interface job structure containing
   * operation details.
   */

  void sdcard_Statemachine_HL(uint16_t block_name, sttag_Memif *memif_job);

  /**
   * @brief Low-level state machine for SD card operations.
   *
   * This state machine handles detailed, low-level operations such as data
   * transfer and DMA configuration.
   *
   * @param block_name The identifier of the SD card block.
   * @param memif_job Pointer to the memory interface job structure containing
   * operation details.
   */

  void sdcard_Statemachine_LL(uint16_t block_name, sttag_Memif *memif_job);

  /**
   * @brief Packs the header structure for SD card data.
   *
   * This method prepares the header structure for data to be written to the SD
   * card.
   *
   * @param memif_job Pointer to the memory interface job structure containing
   * data.
   */

  void Pack_header_Struct(sttag_Memif *memif_job);
  /**
   * @brief Packs user data with CRC for SD card transmission.
   *
   * This method appends CRC (Cyclic Redundancy Check) to user data before
   * writing to the SD card.
   *
   * @param memif_job Pointer to the memory interface job structure containing
   * data.
   */

  void Pack_UserData_CRC(sttag_Memif *memif_job);

  uint8_t Validate_sector_tobewritten(header_Struct &header_Struct );

  uint64_t rand64(void);
uint32_t random_sector(void) ;
uint64_t random_byte_offset(void) ;

};

void sd_card_main_function();

#endif
