#ifndef powermod_H
#define powermod_H

#include<iostream>
#include "../HAL/DIO/dio.h"
#include "../INFRA/API_LIB/apilib.h"





class powermod : public Digital_input_output , public API_LIB<uint16_t>
{
      public :  
      
      void power_based_led_on_off(uint8_t value); 


      private : 


      protected : 

};


/* common interface function to be called. Objects are mainteined in this module itself  */
extern void powermod_cyclic_task(); 
#endif