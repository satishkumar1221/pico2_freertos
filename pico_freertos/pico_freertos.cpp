#include <stdio.h>
#include "pico/stdlib.h"

/*Fix me : As of now only included in this file. Including in other files causes erros . Hence scheduler function have to written here. */
#include "FreeRTOS.h"
#include "mpu_wrappers.h" 
#include "task.h"
#include "Os_usr.h"




int main()
{
    stdio_init_all();
    /*start core 1 before starting os */
   

   OS_start start_os; 
   //start_os.OS_startup_code();
  
    return 0; 
}
