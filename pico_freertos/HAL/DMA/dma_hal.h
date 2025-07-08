#ifndef DMA_HAL_H
#define DMA_HAL_H
 
#include "../SPI/spi_hal.h"
#include "../../INFRA/Mem_Lib/memlibrary.h"
#include "../../INFRA/API_LIB/apilib.h"
#include "dma_cfg.h"



/**
 * @brief Structure representing the current status of the DMA module.
 */
typedef struct 
{
   /**
     * @var uint32_t channel_used
     * @brief The DMA channel currently in use.
     */
     uint32_t channel_used;  
      /**
     * @var uint8_t is_interrupt_enabled
     * @brief Flag indicating if interrupts are enabled for the DMA channel.
     */
     uint8_t is_interrupt_enabled; 
        /**
     * @var uint8_t status
     * @brief Current operational status of the DMA module.
     */
     uint8_t status;
         /**
     * @var uint8_t dma_mode
     * @brief Operating mode of the DMA module (e.g., peripheral-to-memory, memory-to-peripheral).
     */
     uint8_t dma_mode; 
         /**
     * @var uint8_t dma_status
     * @brief Detailed status information about the current DMA operation.
     */
     uint8_t dma_status; 
}DMA_Stat;  


class DMA_config : public MemLib , public spi_config, public API_LIB<uint32_t>
{
    public : 
     /**
     * @var DMA_Stat V_DMA_Status
     * @brief The current status of the DMA module.
     */
    DMA_Stat V_DMA_Status; 
     /**
     * @fn DMA_config()
     * @brief Default constructor for the DMA configuration class.
     */
    DMA_config();
     /**
     * @fn void DMA_Init()
     * @brief Initializes the DMA module.
     */
    void DMA_Init(); 
      /**
     * @fn void start_dma()
     * @brief Starts a DMA operation.
     */
    void start_dma(); 
      /**
     * @fn void abort_dma(uint8_t channel)
     * @brief Aborts a DMA operation on the specified channel.
     */
    void abort_dma(uint8_t channel); 
      /**
     * @fn void DMA_Reset()
     * @brief Resets the DMA module.
     */
    void DMA_Reset(); 
     /**
     * @fn void sniffer_enable_dma(uint channel, uint mode, bool force_channel_enable)
     * @brief Enables or disables the sniffer for DMA operations.
     */
    void sniffer_enable_dma(uint32_t channel, uint32_t mode, bool force_channel_enable); 
    private: 
     /**
     * @fn bool is_channel_free(uint8_t channel)
     * @brief Checks if a DMA channel is free.
     */
    bool is_channel_free(uint8_t channel);  
     /**
     * @fn bool get_channel_irq_status(uint8_t channel)
     * @brief Gets the IRQ status of a DMA channel.
     */
    bool get_channel_irq_status(uint8_t channel); 
        /**
     * @fn bool is_channel_busy(uint8_t channel)
     * @brief Checks if a DMA channel is busy.
     */
    bool is_channel_busy(uint8_t channel); 
    /**
     * @fn void Configure_DMA_based_on_peripherals(const st_DMA_config *ptr_dma_structs)
     * @brief Configures the DMA based on peripheral settings.
     */
    void Configure_DMA_based_on_peripherals(const st_DMA_config *ptr_dma_structs); 
    /**
     * @fn uint32_t dma_get_interrupt_number(uint32_t irq_index)
     * @brief Gets the interrupt number for a specific IRQ index.
     */
    uint32_t dma_get_interrupt_number(uint32_t irq_index); 
    protected: 


};
#endif 