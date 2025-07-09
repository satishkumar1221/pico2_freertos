#include "spi_hal.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
    /**
     * @brief Initializes the SPI HAL and configures the SPI controller according to platform-specific settings.
     *
     * This method initializes the SPI HAL and sets up the SPI controller registers based on platform-specific
     * configuration. It enables the clock for the specified SPI bus and configures the data mode, clock polarity,
     * and clock phase according to predefined settings.
     */
void spi_config :: spi_hal_init()
{
    auto itr = 0 ; 
    for(itr  =0 ; itr < TOTAL_SPI_BUSES ; itr++)
    {
        // As there are only 2 spi busses we can use if else 
        if(C_SPI_Cfg[itr].spi_bus_id == 0)
        {
            spi_init(spi_default, C_SPI_Cfg[itr].baud_rate);
            intilize_gpio_spi(C_SPI_Cfg[itr].spi_bus_id);
        }

        else 
        {
           // spi_init(spi1, C_SPI_Cfg[itr].baud_rate); // configure when u configure spi1. 
        }
        
    } 
     
}
/**
 * @brief Initializes GPIO pins for SPI communication based on the specified SPI bus ID.
 *
 * This method initializes the GPIO pins required for SPI communication on the given `spi_bus_id`.
 * It configures the data (MOSI and MISO), clock (SCLK), and chip select (CS) lines according to platform-specific
 * pin assignments. The function also sets up pull-up resistors and drive strengths for each GPIO pin.
 *
 * @param spi_bus_id The ID of the SPI bus to initialize (e.g., `spi0`, `spi1`, etc.).
 */
void spi_config :: intilize_gpio_spi(uint8_t spi_bus_id )
{
 
    gpio_set_function(C_SPI_Cfg[spi_bus_id].miso_pin, GPIO_FUNC_SPI);
    gpio_init(C_SPI_Cfg[spi_bus_id].cs_pin);
    if(spi_bus_id == 0)
    {
        spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST);
    }
    else 
    {
        //spi_set_format(spi1, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);  // configure when u configure spi1. 
    }
    
    gpio_set_function(C_SPI_Cfg[spi_bus_id].sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(C_SPI_Cfg[spi_bus_id].mosi_pin, GPIO_FUNC_SPI);

     bi_decl(bi_3pins_with_func(C_SPI_Cfg[spi_bus_id].miso_pin, C_SPI_Cfg[spi_bus_id].mosi_pin, C_SPI_Cfg[spi_bus_id].sck_pin, GPIO_FUNC_SPI));
     bi_decl(bi_1pin_with_name(C_SPI_Cfg[spi_bus_id].cs_pin, "SPI CS")); 

}