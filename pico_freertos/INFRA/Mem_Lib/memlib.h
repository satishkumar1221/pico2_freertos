

#ifndef MEMLIB_H
#define MEMLIB_H
//#include<iostream> 
//#include <stdint.h>
#include "apilib.h"


using namespace std;


#define MEM_CPY_COMMON_BUFFER_SIZE 512

#define MEMLIB_DEBUG_ENABLE 0



#define MEMORY_EXCEPTION_HANDLING() if(MEMLIB_DEBUG_ENABLE == 1) {CATCH_EXCEPTION();}

class MemLib
{
    public: 
      void memcopy(void *dest,const void *src, uint32_t size); 
      void memcopy_overlapprotection(void *dest,const void *src, uint32_t size);
      void memset (void *dest , uint8_t value , uint32_t size);
      void memmove(void *dest, const void *src, uint32_t size);
      void memzero(void *dest , uint32_t size);
      void __malloc_pico0(int size); /* To Do : Have to write custom memory allocator */
    
};

#endif 

