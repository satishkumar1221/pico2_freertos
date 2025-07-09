
#include "powermod.h"

#define TASK_COUNT_FIVE_SECOND 5

void powermod :: power_based_led_on_off(uint8_t value)
{
    Set_Digital_output(dio_pin25_led, value);
}




 void powermod_cyclic_task()
 {
      static uint16_t V_Counter;
      powermod obj_powermod;    
    
      obj_powermod.increment_counter(&V_Counter, 1, TASK_COUNT_FIVE_SECOND); 
      if(V_Counter == TASK_COUNT_FIVE_SECOND)
      {

        V_Counter = 0; 
        obj_powermod.power_based_led_on_off(ACTIVE_LOW); 
        /* code */
      }
      else 
      {
         obj_powermod.power_based_led_on_off(ACTIVE_HIGH); 
      }
      
      
 }