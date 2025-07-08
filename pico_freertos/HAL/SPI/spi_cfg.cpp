#include "spi_cfg.h"

#include "hardware/spi.h"
 const SPI_cfg C_SPI_Cfg[TOTAL_SPI_BUSES] = 
{
    /*10 Mhz */
     {0, (10 *1000 *1000 ) , PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_RX_PIN , PICO_DEFAULT_SPI_CSN_PIN}
}; 

