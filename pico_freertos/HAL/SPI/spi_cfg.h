#ifndef SPI_CFG_H
#define SPI_CFG_H


#include <iostream> 
#include <stdint.h> 




typedef enum 
{
   spi_bus0, 
   //spi_bus1, 
   TOTAL_SPI_BUSES
}SPI_BUS; 

#define spi(x) spi##x 

#define SPI_BAUDRATE_CFG_Hz(x) ((x) (*) (1000 *1000))

typedef struct 
{
    const uint8_t spi_bus_id; 
    uint32_t baud_rate; 
    uint8_t sck_pin; 
    uint8_t mosi_pin; 
    uint8_t miso_pin; 
    uint8_t cs_pin;; 
}SPI_cfg; 




extern const SPI_cfg C_SPI_Cfg[TOTAL_SPI_BUSES] ; 
#endif 