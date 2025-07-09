#ifndef DIO_H
#define DIO_H

#include "dio_cfg.h"

  
    /**
 * @brief Class for configuring and managing digital input/output operations on GPIO pins.
 *
 * This class provides methods to initialize GPIO pins as digital inputs or outputs,
 * set the output value of digital pins, and read the input value of digital pins.
 */
class Digital_input_output
{
      public : 
    /**
     * @brief Constructs a `Digital_input_output` object with default settings.
     *
     * The default constructor initializes internal variables and settings for digital input/output operations.
     */
    Digital_input_output(); 
   /**
     * @brief Sets the output value of a digital pin.
     *
     * This method sets the output value (`value`) of the specified `pin` to either HIGH (1) or LOW (0).
     *
     * @param pin The GPIO pin number to set as a digital output.
     * @param value The desired output value (HIGH: 1, LOW: 0).
     */
    void Digital_input_output_init();

  /**
     * @brief Sets the output value of a digital pin.
     *
     * This method sets the output value (`value`) of the specified `pin` to either HIGH (1) or LOW (0).
     *
     * @param pin The GPIO pin number to set as a digital output.
     * @param value The desired output value (HIGH: 1, LOW: 0).
     */

    void Set_Digital_output(uint8_t pin , uint8_t value ); 
        /**
     * @brief Reads the input value of a digital pin.
     *
     * This method reads the input value (`true` for HIGH, `false` for LOW) from the specified `pin_number`.
     *
     * @param pin_number The GPIO pin number to read as a digital input.
     */
    void Read_Digital_input(uint8_t pin_number );

    private : 

    protected :  

}; 

#endif 
