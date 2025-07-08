#ifndef DMA_CFG_H
#define DMA_CFG_H


#include <iostream> 
#include <stdint.h> 
#define SPI_CONFIGURED_BIT 0

#define SPI_BUS_TO_BE_CONFIGURED 0

#define NO_PERIPHERAL_CONFIGURED_DMA -1


#define CONFIGURE_SPI_BUS 1
#define CONFIGURE_I2C_BUS 2
#define CONFIGURE_GPIO    3 
typedef union 
{
    uint32_t R; 
    struct 
    {
        uint32_t spi:1;
        uint32_t i2c:1;
        uint32_t gpio:1; 
        uint32_t reserved :29;
    }B;

}peripherals;  

typedef enum 
{
    SPI_CHANNEL, 
    SW_INTERRUPT_CHANNEL, 
    DMA_CHANNELS
}entag_dma;


typedef enum 
{
   channel0 = 0, 
   channel1, 
   channel2,  
   channel3, 
   channel4,    
   channel5, 
   channel6, 
   channel7, 
   channel8,    
   channel9, 
   channel10, 
   channel11, 
   TOTAL_DMA_CHANNELS 
}enTag_DMA_CHANNELS; 

typedef struct 
{
    uint8_t *ptr_txbuffer;
    uint8_t *ptr_destbuffer; 
    enTag_DMA_CHANNELS channel_used_rx; 
    enTag_DMA_CHANNELS channel_used_tx;
    uint32_t size_txbuffer;
    uint32_t size_rxbuffer;
    uint32_t peripherals_used;
    uint8_t peri_bus_configured; 
    
}st_DMA_config; 




extern const st_DMA_config C_DMA_CONFIG[DMA_CHANNELS]; 
#endif 