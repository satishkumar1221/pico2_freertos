#include "pico/stdlib.h"
#include "dio.h"
/******************************************************************************
 * File:        dio_hal.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        7/08/2025
 * Description: Contains logic for setting and clearing of digital_input_output
 *
 * Revision History: 
 *   <07/08/2025> - 1.0 : Initlial version :satish kumar 
 * 
 *  
 ******************************************************************************/


Digital_input_output :: Digital_input_output ()
{
   //Digital_input_output_init(); 
}


void Digital_input_output :: Digital_input_output_init()
{
    auto itr = 0 ; 
    /*using the static variable here as we cannot crate a static variable within the constructor scope */
    //static uint8_t sticky_flag =0;
  //  if(sticky_flag == 0)
  //  { 
        while(itr < Total_number_Pins_configured)
        {
            gpio_init(C_Dio_Cfg[itr].pin_number);
            gpio_set_dir(C_Dio_Cfg[itr].pin_number, C_Dio_Cfg[itr].pin_mode);
            gpio_put(C_Dio_Cfg[itr].pin_number, ACTIVE_LOW); 
            itr++; 
        }
        /*The function should only be executed once*/
        //sticky_flag = 1; 
  //}
} 


void Digital_input_output :: Set_Digital_output(uint8_t pin , uint8_t value )
{
       gpio_put(C_Dio_Cfg[pin].pin_number, value); 
}


 void Digital_input_output :: Read_Digital_input(uint8_t pin_number )
 {

 }






