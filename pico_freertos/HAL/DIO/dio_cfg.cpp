#include "dio_cfg.h"
#include "pico/stdlib.h"




DIO_CFG C_Dio_Cfg[Total_number_Pins_configured] = 
{
    {PICO_DEFAULT_LED_PIN , GPIO_OUT , ACTIVE_LOW}, 
}; 