

#ifndef MEMLIBRARY_H
#define MEMLIBRARY_H
//#include<iostream> 
#include <stdint.h>



using namespace std;


#define MEM_CPY_COMMON_BUFFER_SIZE 512

#define MEMLIB_DEBUG_ENABLE 0



#define MEMORY_EXCEPTION_HANDLING() if(MEMLIB_DEBUG_ENABLE == 1) {CATCH_EXCEPTION();}
/**
 * @class MemLib
 */
/**
 * @brief Defines a library of basic memory operations.
 */
class MemLib
{
    public: 
     /**
     * @fn void lib_memcopy(void *dest,const void *src, uint32_t size)
     * @brief Copies data from the source to the destination.
     */
      void lib_memcopy(void *dest,const void *src, uint32_t size); 
        /**
     * @fn void memcopy_overlapprotection(void *dest,const void *src, uint32_t size)
     * @brief Performs memory copy with overlap protection.
     */
      void memcopy_overlapprotection(void *dest,const void *src, uint32_t size);
       /**
     * @fn void lib_memset (void *dest , uint8_t value , uint32_t size)
     * @brief Sets all bytes of the destination array to the specified value.
     */
      void lib_memset (void *dest , uint8_t value , uint32_t size);
       /**
     * @fn void lib_memmove(void *dest, const void *src, uint32_t size)
     * @brief Moves the data from the source to the destination.
     */
      void lib_memmove(void *dest, const void *src, uint32_t size);
       /**
     * @fn void lib_memzero(void *dest , uint32_t size)
     * @brief Sets all bytes of the destination array to zero.
     */
      void lib_memzero(void *dest , uint32_t size);
      
      void __malloc_pico0(int size); /* To Do : Have to write custom memory allocator */
    
};

#endif 

