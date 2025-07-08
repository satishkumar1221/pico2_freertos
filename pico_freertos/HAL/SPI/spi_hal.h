#ifndef SPI_HAL_H
#define SPI_HAL_H


#include "spi_cfg.h"

/**
 * @brief Class for configuring and managing SPI operations.
 *
 * This class provides methods to initialize the SPI hardware abstraction layer (HAL),
 * configure GPIO pins for SPI communication, and perform other SPI-related tasks.
 */
class spi_config
{
    public: 
     /**
     * @brief Initializes the SPI HAL and configures the SPI controller according to platform-specific settings.
     *
     * This method initializes the SPI HAL and sets up the SPI controller registers based on platform-specific
     * configuration. It enables the clock for the specified SPI bus and configures the data mode, clock polarity,
     * and clock phase according to predefined settings.
     */
    void spi_hal_init(); 
    /**
 * @brief Initializes GPIO pins for SPI communication based on the specified SPI bus ID.
 *
 * This method initializes the GPIO pins required for SPI communication on the given `spi_bus_id`.
 * It configures the data (MOSI and MISO), clock (SCLK), and chip select (CS) lines according to platform-specific
 * pin assignments. The function also sets up pull-up resistors and drive strengths for each GPIO pin.
 *
 * @param spi_bus_id The ID of the SPI bus to initialize (e.g., `spi0`, `spi1`, etc.).
 */
    void intilize_gpio_spi(uint8_t spi_bus_id); 
     
    private: 

    protected:  

}; 

#endif 