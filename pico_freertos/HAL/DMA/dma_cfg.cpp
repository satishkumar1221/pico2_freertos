#include "dma_cfg.h"


/* Declare the globalv ariable for the DPI. To be used for the DMA where the xfer is continuos and will not change */
 



uint8_t V_TX_BUFFER[512];  
uint8_t V_RX_BUFFER[512]; 

const st_DMA_config C_DMA_CONFIG[DMA_CHANNELS] = 
{
   {&V_TX_BUFFER[0] , &V_RX_BUFFER[0] ,channel0 , channel1 , 512 , 512 , SPI_CONFIGURED_BIT , SPI_BUS_TO_BE_CONFIGURED },
}; 