#include "pico/stdlib.h"
#include "dio.h"



Digital_input_output :: Digital_input_output ()
{
   Digital_input_output_init(); 
}


void Digital_input_output :: Digital_input_output_init()
{
    auto itr = 0 ; 
    while(itr < Total_number_Pins_configured)
    {
        gpio_init(C_Dio_Cfg[itr].pin_number);
        gpio_set_dir(C_Dio_Cfg[itr].pin_number, C_Dio_Cfg[itr].pin_mode);
        gpio_put(C_Dio_Cfg[itr].pin_number, ACTIVE_LOW); 
        itr++; 
    }
} 


void Digital_input_output :: Set_Digital_output(uint8_t pin , uint8_t value )
{
       gpio_put(C_Dio_Cfg[pin].pin_number, value); 
}


 void Digital_input_output :: Read_Digital_input(uint8_t pin_number )
 {

 }






