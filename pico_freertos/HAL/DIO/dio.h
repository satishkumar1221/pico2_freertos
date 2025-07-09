#ifndef DIO_H
#define DIO_H

#include "dio_cfg.h"


class Digital_input_output
{
    public : 
    
    Digital_input_output(); 
    
    void Digital_input_output_init();

    void Set_Digital_output(uint8_t pin , uint8_t value ); 
    
    void Read_Digital_input(uint8_t pin_number );

    private : 

    protected :  

}; 

#endif 
