#ifndef DIO_CFG_H
#define DIO_CFG_H

#include <stdint.h> 
#include <iostream>

#define ACTIVE_LOW 0u
#define ACTIVE_HIGH 1u

typedef  enum 
{
   dio_pin25_led,  
  Total_number_Pins_configured  
}pins_configured; 
typedef struct 
{

   uint8_t pin_number; 
   uint8_t pin_mode; 
   uint8_t initial_pin_value; 


}DIO_CFG;


extern DIO_CFG C_Dio_Cfg[Total_number_Pins_configured]; 
#endif 