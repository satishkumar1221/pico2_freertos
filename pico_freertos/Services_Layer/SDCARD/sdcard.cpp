#include "sdcard.h"
#include "INFRA\API_LIB\crc16.h"
#include "Nvm_cfg.h"
#include "Memif.h"
#include <cstdint>
/*Internal cache block to identify if the data is writtena fter being
 * configured*/

using namespace std;

#define CRC_HEADER_SIZE 2U
uint32_t V_Internalblock_cache[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED];

sttag_Memif V_Sttag_Memif_Request;
entag_fee_hl V_entag_sdcard_state = no_operation_sdcard;

Block_struct V_sttag_sdcard_packet;
Block_struct_multiplesectorwrites V_sttag_sdcard_packet_multiple_Sectorwrites;

static uint8_t lock_packet;

static uint8_t  V_Packet_header_status;

Job_status_LLD V_SDCARD_JOb_Status;

cache_struct NV_cache_struct[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED];
entag_sdcard_States V_entag_sdcard_result[TOTAL_NUMBER_OF_BLOCKS_CONFIGURED];

/*Buffers used in DMA to communicate with sdcard */
uint8_t V_TX_BUFFER_DMA_LAYER[512];
uint8_t V_RX_BUFFER_DMA_LAYER[512];

#define LOCK_DATA(x) *x = true
#define UNLOCK_DATA(x) *x = FALSE

/* @brief Triggers the SD card read operation via the state machine.
 *
 * This function initiates a read request for a specific block by invoking the
 * state machine
 * (`sdcard_Statemachine_HL`) with the provided block name and memory interface
 * request.
 *
 * @param block_name   The identifier of the SD card block to be read.
 */
void SD_Card_Interface ::Read_Data_Sdcard(uint16_t block_name) {

  /* In autosar block_name is always asending . Lets consider that now. In
   * future need tp write a binary serch alogo and store the block headers in
   * asending order. Block_name == header_name . Incase of dynamic allocation.
   * the table will change */
  if (NV_cache_struct[block_name].cache_value ==
      CACHE_AVAILABLE_BLOCK_PROGRAMMED_ONCE) {
    sdcard_Statemachine_HL(block_name, &V_Sttag_Memif_Request);
  } else {
    V_entag_sdcard_result[block_name] = SDCARD_INTEGRITY_FAILED;
  }
}
void SD_Card_Interface ::Write_Data_Sdcard(uint16_t block_name) {
  sdcard_Statemachine_HL(block_name, &V_Sttag_Memif_Request);
}

/**
 * @brief Handles data reception from the SD card interface.
 *
 * This function sends data via the MemIf interface and processes
 * read/write operations based on the job status.
 *
 * @param memif_jobstat Pointer to the sttag_Memif structure containing
 *                      job statistics and operation parameters.
 *
 * @see MemIf::Send_Data_SdCard
 * @see Read_Data_Sdcard
 * @see Write_Data_Sdcard
 */

void SD_Card_Interface ::Recieve_Data_MemIf(sttag_Memif *memif_jobstat) {
  MemIf obj_memif;
  obj_memif.Send_Data_SdCard(memif_jobstat);
   V_Sttag_Memif_Request = *memif_jobstat;  /*temporary fix */
  if (memif_jobstat->operation == read) {
    Read_Data_Sdcard(memif_jobstat->block_name);
  }

  else if (memif_jobstat->operation == write) {
    Write_Data_Sdcard(memif_jobstat->block_name);
  }
}

void SD_Card_Interface ::process_sd_card_request()

{
  Recieve_Data_MemIf(&V_Sttag_Memif_Request);
}

/* @brief Main function for SD card operations.
 *
 * This function initializes an instance of the SD_Card_Interface class and
 * triggers the processing of SD card requests. It is designed to act as a
 * central entry point for handling SD card interactions.
 *
 */
void sd_card_main_function() {
  SD_Card_Interface obj_sd_card_main_function;
  obj_sd_card_main_function.process_sd_card_request();
#if 0
    sdcard_Statemachine_HL();
#endif
}

/* Kumar S2 :  HAve to write common to 16GB and 32GB. Pending implmentaions   */
uint64_t SD_Card_Interface ::rand64(void) {
  // build 64-bit random from rand(); works if RAND_MAX >= 32767
  uint64_t r = 0;
  for (int i = 0; i < 5; i++) {
    r = (r << 15) ^ (rand() & 0x7FFF);
  }
  return r;
}

uint32_t SD_Card_Interface ::random_sector(void)

{
  const uint32_t mask = (1u << 26) - 1u; // 0x03FFFFFF
  return (uint32_t)(rand64() & mask);
}

uint64_t SD_Card_Interface ::random_byte_offset(void)

{
  return ((uint64_t)random_sector()) << 9; // *512
}

/* Fix Me : To find duolicate numbers from the sector generated.*/
uint8_t
SD_Card_Interface ::Validate_sector_tobewritten(header_Struct &header_Struct) {
  auto itr = 0;
  MemLib obj_mem;
  const uint64_t total_logical_sectors =
      ((CONVERT_GB_TO_BYTES - BOOK_KEEPING_BLOCKS) / (SECTOR_SIZE_PHYSICAL));
  bool flag_found = false;
  for (itr = 0; itr < TOTAL_NUMBER_OF_BLOCKS_CONFIGURED; itr++) {
    if (NV_cache_struct[itr].header.block_id == header_Struct.block_id) {
      /* validate cache from the table */
      if (NV_cache_struct[itr].cache_value ==
          CACHE_INVALIDATED_BLOCK_NOT_PROGRAMMED) {
        flag_found = false;
      } else {
        flag_found = true;
      }
      break;
    }

    if (false == flag_found) {
      NV_cache_struct[header_Struct.block_id].header = header_Struct;
      // random
      uint64_t offset = random_byte_offset();
      NV_cache_struct[header_Struct.block_id].header.address_first_block =
          offset;
      NV_cache_struct[itr].cache_value = CACHE_AVAILABLE_BLOCK_PROGRAMMED_ONCE;
      /* Write the Book Keeping block to a particular adress */
      /*last 2GB is only for Book Keeping */
      if (sizeof(NV_cache_struct) <= 512) {
        obj_mem.memcopy_overlapprotection(((&V_TX_BUFFER_DMA_LAYER[0])),
                                          &NV_cache_struct[0],
                                          (sizeof(NV_cache_struct)));
        CRC16 obj_crc_16;
        V_sttag_sdcard_packet.CRC = obj_crc_16.processBuffer(
            reinterpret_cast<uint8_t *>(&NV_cache_struct[0]),
            sizeof(NV_cache_struct));
        /*Trigger a write to Sdcard */
        V_Packet_header_status = true;
      //  Trigger_Write_sdcard();

      }

      else {
        /*Write block by block */

      }
    }
  }

  // header_Struct

  return 0;
}




void SD_Card_Interface ::Trigger_Write_sdcard() {

 DMA_config obj_DMAconfig;
  obj_DMAconfig.start_dma();
}


/**
 * @brief State machine for handling SD card operations.
 *
 * This function implements a finite state machine to manage SD card
 * interactions. It processes requests based on the operation type,
 * transitions through states (e.g., read, write, pack_data, trigger_write),
 * and ensures proper data handling.
 *
 * @param block_name   The identifier for the block being processed.
 * @param memif_job    Pointer to the memory interface job structure
 * containing operation details.
 */

void SD_Card_Interface ::sdcard_Statemachine_HL(uint16_t block_name,
                                                sttag_Memif *memif_job) {
  static bool sticky_flag;
  if (sticky_flag == false) {
    V_entag_sdcard_state = static_cast<entag_fee_hl>(memif_job->operation);
    sticky_flag = true;
  }
  switch (V_entag_sdcard_state) {
  case read_sdcard:
    //Read_sdcard_data(memif_job , block_name);
    V_entag_sdcard_state = trigger_read; 
    break;

  case write_sdcard:
    V_entag_sdcard_state = pack_data;
    break;

  case pack_data:
    Pack_header_Struct(memif_job);
    Pack_UserData_CRC(memif_job);
    V_entag_sdcard_state = trigger_write;
    break;

  case unpack_data:
    break;

  case trigger_write:{
                       if(V_Packet_header_status == true)
                       {
                           /*First write to the book keeping block */
                           Trigger_Write_sdcard();
                           V_Packet_header_status = (uint8_t)false;
                       }
                       else
                       {
                           SET_MEMIF_STAT(Job_status_MemIf_BUSY);
                           /* Trigger Write to the Sd card. Donot go to next state unti data is written   */
                            Trigger_Write_sdcard();
                            V_entag_sdcard_state = result;
                       }
                    }
                      break;

  case trigger_read:   SET_MEMIF_STAT(Job_status_MemIf_BUSY);
                      Read_sdcard_data(memif_job , block_name);
                       if(Get_LLD_Status() != Job_status_LLD_BUSY)
                {
                    V_entag_sdcard_state = no_operation_sdcard;
                    /*Retury will be taken by NVM or Memif */
                } 

                      break;

  case result:  /*This interfaces with the low level driver */
                SET_MEMIF_STAT(Get_LLD_Status());
                if(Get_LLD_Status() != Job_status_LLD_BUSY)
                {
                    V_entag_sdcard_state = no_operation_sdcard;
                    /*Retury will be taken by NVM or Memif */
                }
  break;

  case no_operation_sdcard:
    SET_MEMIF_STAT(Get_LLD_Status()); 
    sticky_flag = false;
    break;

  default:
    sticky_flag = false;
    break;
  }
}


void SD_Card_Interface :: Read_sdcard_data(sttag_Memif *memif_job , uint16_t block_name)
{
    /* Implement the logic for reading data from the SD card */
    /* Use memif_job and block_name to perform the read operation */
    /* Update the status and state accordingly */
    //cache has been validated 
    const cache_struct *ptr_cache_struct = &NV_cache_struct[block_name] ; 
    MemLib obj_memlib; 
    /* validate CRC */
     CRC16 obj_crc_16;
     uint16_t CRC_Calculate =  obj_crc_16.processBuffer(reinterpret_cast<uint8_t *>(&NV_cache_struct[block_name].header.address_first_block),NV_cache_struct[0].header.size);
     if(CRC_Calculate == NV_cache_struct[block_name].header.CRC)
     {
         /*Figure out how to initalta a spi xsaction */
         obj_memlib.memcopy_overlapprotection(memif_job->ptr_data , &NV_cache_struct[block_name].header.address_first_block ,NV_cache_struct[0].header.size ); 
     }
     else 
     {
         /*Restore to defaults*/
     }


    
}


/**
 * @brief Packs header data into the SD card packet structure.
 *
 * This function initializes the header fields of the SD card packet,
 * computes the CRC checksum, and ensures the header structure size
 * matches the expected 6-byte layout.
 *
 * @param memif_job Pointer to the sttag_Memif structure containing
 *                  data size and configuration parameters.
 *
 * @pre The @c V_sttag_sdcard_packet structure must be properly
 *      initialized before calling this function.
 *
 * @note The CRC is calculated over the header excluding the CRC field
 *       itself (size = total size - CRC_HEADER_SIZE).
 * @note A static assert verifies the header structure size is exactly 6
 * bytes.
 *
 * @see CRC16::processBuffer
 * @see V_sttag_sdcard_packet
 * @see sttag_Memif
 */

void SD_Card_Interface ::Pack_header_Struct(sttag_Memif *memif_job) {
  CRC16 obj_crc_16;
  const uint32_t payload_len = memif_job->size;
  const uint32_t overhead = sizeof(header_Struct) +
                            sizeof(V_sttag_sdcard_packet.end_pattern) /*end*/ +
                            sizeof(V_sttag_sdcard_packet.CRC) /*crc*/;
  if (memif_job->size <= (SECTOR_SIZE_PHYSICAL - overhead)) {
    V_sttag_sdcard_packet.header.pattern = HEADER_PATTERN;
    V_sttag_sdcard_packet.header.size = memif_job->size;
    V_sttag_sdcard_packet.header.block_id = memif_job->block_name;
    V_sttag_sdcard_packet.header.block_type = single_block_operation;
    V_sttag_sdcard_packet.header.size = memif_job->size;
    static_assert(sizeof(header_Struct) == 24,
                  "header_Struct must be exactly 20 bytes");
    uint16_t crc_len = (uint16_t)offsetof(header_Struct, CRC);
    V_sttag_sdcard_packet.header.CRC = obj_crc_16.processBuffer(
        (reinterpret_cast<const uint8_t *>(&V_sttag_sdcard_packet.header)),
        crc_len);
    // NV_cache_struct[V_sttag_sdcard_packet.header.block_id].header =
    // V_sttag_sdcard_packet.header;

    auto result = Validate_sector_tobewritten(V_sttag_sdcard_packet.header);

    /* Write the bookkeeping block.  */
  }

  else {
    V_sttag_sdcard_packet_multiple_Sectorwrites.header.pattern = HEADER_PATTERN;
    V_sttag_sdcard_packet_multiple_Sectorwrites.header.size = memif_job->size;
    V_sttag_sdcard_packet_multiple_Sectorwrites.header.block_id =
        memif_job->block_name;
    V_sttag_sdcard_packet_multiple_Sectorwrites.header.block_type =
        multi_block_operation;
    V_sttag_sdcard_packet_multiple_Sectorwrites.header.size = memif_job->size;
    static_assert(sizeof(header_Struct) == 24,
                  "header_Struct must be exactly 24 bytes");
    uint16_t crc_len = (uint16_t)offsetof(header_Struct, CRC);
    V_sttag_sdcard_packet_multiple_Sectorwrites.header.CRC =
        obj_crc_16.processBuffer(
            (reinterpret_cast<const uint8_t *>(
                &V_sttag_sdcard_packet_multiple_Sectorwrites.header)),
            crc_len);
    NV_cache_struct[V_sttag_sdcard_packet_multiple_Sectorwrites.header.block_id]
        .header = V_sttag_sdcard_packet_multiple_Sectorwrites.header;
    /*Write code for multi blocks . Implementation Pending.  */
    auto result = Validate_sector_tobewritten(
        V_sttag_sdcard_packet_multiple_Sectorwrites.header);
  }
}

void SD_Card_Interface ::Pack_UserData_CRC(sttag_Memif *memif_job) {

  CRC16 obj_crc_16;
  /*chaining has to be done for multi blocks*/
  const uint32_t payload_len = memif_job->size;
  const uint32_t overhead = sizeof(header_Struct) +
                            sizeof(V_sttag_sdcard_packet.end_pattern) /*end*/ +
                            sizeof(V_sttag_sdcard_packet.CRC) /*crc*/;
  if (memif_job->size <= (SECTOR_SIZE_PHYSICAL - overhead)) {
    /*Validate what block to write */

    memcopy_overlapprotection(&V_TX_BUFFER_DMA_LAYER[0],
                              &V_sttag_sdcard_packet.header,
                              sizeof(header_Struct));
    memcopy_overlapprotection(
        ((&V_TX_BUFFER_DMA_LAYER[0]) + sizeof(header_Struct)),
        memif_job->ptr_data, memif_job->size);
    /*append end pattern */
    V_sttag_sdcard_packet.end_pattern = END_PATTERN;

    memcopy_overlapprotection(
        ((&V_TX_BUFFER_DMA_LAYER[0]) + sizeof(header_Struct) + memif_job->size),
        &V_sttag_sdcard_packet.end_pattern,
        (sizeof(V_sttag_sdcard_packet.end_pattern)));

    V_sttag_sdcard_packet.CRC = obj_crc_16.processBuffer(
        ((&V_TX_BUFFER_DMA_LAYER[0]) + sizeof(header_Struct)),
        memif_job->size + sizeof(V_sttag_sdcard_packet.end_pattern));

    memcopy_overlapprotection(
        ((&V_TX_BUFFER_DMA_LAYER[0]) + sizeof(header_Struct) + memif_job->size +
         sizeof(V_sttag_sdcard_packet.end_pattern)),
        &V_sttag_sdcard_packet.CRC, (sizeof(V_sttag_sdcard_packet.CRC)));
  }
}
