/******************************************************************************
 * File:        dma_hal.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        6/10/2025
 * Description: Contains logic for dimrect memory access in hardware abstraction layer
 *
 * Revision History: 
 *   <07/08/2025> - 1.0 : Initlial version :satish kumar 
* 
 *  
 ******************************************************************************/

#include "dma_hal.h"
#include "hardware/spi.h"

#include "hardware/dma.h"
#if 0 

static inline dma_channel_config dma_channel_get_default_config(uint channel) {
    dma_channel_config c = {0};
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    channel_config_set_dreq(&c, DREQ_FORCE);
    channel_config_set_chain_to(&c, channel);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    channel_config_set_ring(&c, false, 0);
    channel_config_set_bswap(&c, false);
    channel_config_set_irq_quiet(&c, false);
    channel_config_set_enable(&c, true);
    channel_config_set_sniff_enable(&c, false);
    channel_config_set_high_priority( &c, false);
    return c;
}

#endif 



/**
 * @brief Configures the DMA based on peripheral settings.
 *
 * This method takes a pointer to an array of `@ref st_DMA_config` structures,
 * each containing configuration settings for a specific peripheral. It iterates through
 * the provided configurations, configuring the DMA channel and enabling/disabling interrupts
 * according to the specified settings.
 *
 * @param ptr_dma_structs Pointer to an array of `@ref st_DMA_config` structures.
 * @param num_configs The number of configurations in the input array.
 *
 * @dot
 * digraph G {
   rankdir=TB;
   node [shape=box];
   "Start" [shape=plaintext];
   "End" [shape=plaintext];

   "Start" -> "Check ptr_dma_structs";
   "Check ptr_dma_structs" -> "Invalid pointer?";
   "Invalid pointer?" -> "Return error code";
   "Invalid pointer?" -> "Initialize DMA channel" [label="No"];
   "Initialize DMA channel" -> "Configure DMA based on settings";
   "Configure DMA based on settings" -> "Enable/disable interrupts";
   "Enable/disable interrupts" -> "Check if all configurations processed";
   "Check if all configurations processed" -> "Process next configuration" [label="No"];
   "Check if all configurations processed" -> "Return success code";
   "Process next configuration" -> "Initialize DMA channel";
   "End" -> "Check if all configurations processed";
 }
 * @enduml
 */

void DMA_config :: Configure_DMA_based_on_peripherals(const st_DMA_config *ptr_dma_structs)
{
    uint32_t bitmask; 
    set_bits(&bitmask,ptr_dma_structs->peripherals_used);

    switch(bitmask)
    {
       case CONFIGURE_SPI_BUS :  
                              if(ptr_dma_structs->peri_bus_configured == SPI_BUS_TO_BE_CONFIGURED)
                              {
                                
                                 dma_channel_config c = dma_channel_get_default_config(ptr_dma_structs->channel_used_tx);
                                 channel_config_set_transfer_data_size(&c, DMA_SIZE_8);

                                 dma_channel_configure(ptr_dma_structs->channel_used_tx, 
                                                        &c,
                                                        &spi_get_hw(spi_default)->dr, // write address
                                                        ptr_dma_structs->ptr_txbuffer, // read address
                                                        ptr_dma_structs->size_txbuffer, // element count
                                                        false); // don't start yet
                              /*Configure DMA_RX */
                              auto rx = dma_channel_get_default_config(ptr_dma_structs->channel_used_rx); 
                              dma_channel_configure(ptr_dma_structs->channel_used_rx, 
                                                        &rx,
                                                        &spi_get_hw(spi_default)->dr, // write address
                                                        ptr_dma_structs->ptr_destbuffer, // rx buffer
                                                        ptr_dma_structs->size_rxbuffer, // element count
                                                        false); // don't start yet

                              }

                  break;  
       
       case CONFIGURE_I2C_BUS : 
                  break ; 
      case CONFIGURE_GPIO : 
                  break ; 
    }
}

/**
 * @brief Initializes the DMA module.
 *
 * This method sets up the DMA controller and initializes its registers according to the specified configuration.
 * It performs the following steps:
 *
 * - Resets the DMA controller.
 * - Configures DMA clock settings.
 * - Sets up DMA channel properties.
 * - Enables or disables interrupts based on configuration.
 *
 * @dot
 * digraph G {
   rankdir=TB;
   node [shape=box];
   "Start" [shape=plaintext];
   "End" [shape=plaintext];

   "Start" -> "Reset DMA controller";
   "Reset DMA controller" -> "Configure DMA clock settings";
   "Configure DMA clock settings" -> "Set up DMA channel properties";
   "Set up DMA channel properties" -> "Enable/disable interrupts";
   "Enable/disable interrupts" -> "End";
 }
 * @enduml
 */

/**
 * @brief Initializes the DMA module.
 *
 * @details This method initializes the DMA controller and sets up its registers according to the specified configuration.
 */

void DMA_config :: DMA_Init ()
{
   /*Initlize TX and RX buffers to 0x20 which is Blacnk space  */
   const uint8_t blank_space = 0x20; 
   auto itr  =0 ; 

   for(itr  =0 ; itr < DMA_CHANNELS ; itr++)
   {
    lib_memset(C_DMA_CONFIG[itr].ptr_txbuffer , blank_space,C_DMA_CONFIG[itr].size_txbuffer);
    lib_memset(C_DMA_CONFIG[itr].ptr_destbuffer , blank_space,C_DMA_CONFIG[itr].size_rxbuffer);
   }

   /*configure SPI */
   spi_hal_init(); 
   /*configure DMA and check if the channl is avaiable*/ 
   if(C_DMA_CONFIG[itr].peripherals_used >= 0u)
   { 
      if(is_channel_free(C_DMA_CONFIG[SPI_CHANNEL].channel_used_tx) && (is_channel_free(C_DMA_CONFIG[SPI_CHANNEL].channel_used_rx)))
      {
      /*Both the channels are free . Now configure those channels*/
        Configure_DMA_based_on_peripherals(&C_DMA_CONFIG[SPI_CHANNEL]);
      }
   }
  else 
  {

  }
   

}

DMA_config :: DMA_config()
{

}

void DMA_config :: start_dma ()
{
  auto itr = 0 ; 
  uint32_t tx_mask;  
  uint32_t rx_mask; 
     for(itr  = 0 ; itr < TOTAL_DMA_CHANNELS ; itr++)
     {
        set_bits(&tx_mask,C_DMA_CONFIG[itr].channel_used_tx);
        set_bits(&rx_mask,C_DMA_CONFIG[itr].channel_used_rx);
        dma_start_channel_mask((rx_mask) | (tx_mask));
     }
}

void DMA_config :: abort_dma (uint8_t channel )
{
    dma_channel_abort(channel); 
}

#if 0



#endif 
void DMA_config :: DMA_Reset ()
{
 
}   

bool DMA_config :: is_channel_busy(uint8_t channel)
{
    return(false);
}    

bool DMA_config :: is_channel_free(uint8_t channel)
{
   auto status = dma_channel_is_claimed(channel); 
    return(status);
}

bool DMA_config :: get_channel_irq_status(uint8_t channel)
{
   return(false);
}

uint32_t DMA_config :: dma_get_interrupt_number(uint32_t irq_index)
{
  return(false);
}

void DMA_config :: sniffer_enable_dma(uint32_t channel, uint32_t mode, bool force_channel_enable)
{

}   