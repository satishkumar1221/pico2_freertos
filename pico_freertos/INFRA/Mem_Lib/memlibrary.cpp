#include "memlibrary.h"
#include "../API_LIB/apilib.h"

/******************************************************************************
 * File:        mem_lib.cpp
 * Author:      satish kumar
 * copyright:   satish kumar
 * Date:        6/12/2025
 * Description:  This module contains memory related functions. 
 *
 * Revision History:
 *   <06/12/2025> - 1.0 : Initial implementation of the mem_lib  :satish kumar 
 *   
 *  
 ******************************************************************************/



/**
 * @brief memcopy function to copy the data from one location to another
 * 
 * 
 * 
 * @param[in] dest Pointer to teh destination buffer where the data has to be copied. 
 * @param[in] src Pointer to the source buffer where the data is present. 
 * @param[in] size size of the buffer passed by the user .
 * @return None
 *  @param[out] None 
 */

void MemLib ::lib_memcopy(void *dest ,const void *src , uint32_t size )
{
  auto itr = 0;  
  if( (src!= NULL && dest!=NULL) &&(size>0))
  {
    uint8_t *ds = (static_cast<uint8_t*>(dest)); 
   const uint8_t *sc = (static_cast<const uint8_t*>(src)); /*being const correct is very important in cpp .* Hence const used. : Kumars2 : learning*/
      while (itr < size) 
      {
          ds[itr] = sc[itr];
          itr++;  
      }
 }
 else 
 {
    /*Do nothing. We can add a no peration and while 1 loop  */
 }
}

/**
 * @brief memcopy_overlapprotection function to copy the data from one location to another with the overlap protection. 
 * 
 * 
 * 
 * @param[in] dest Pointer to teh destination buffer where the data has to be copied. 
 * @param[in] src Pointer to the source buffer where the data is present. 
 * @param[in] size size of the buffer passed by the user .
 * @return None
 *  @param[out] None 
 */


void MemLib ::memcopy_overlapprotection(void *dest ,const void *src , uint32_t size )
{

 auto itr = 0;
 uint8_t buffer_safe[MEM_CPY_COMMON_BUFFER_SIZE];   

 if( (src!= NULL && dest!=NULL) &&(size>0))
 {
    /* overlap protection .*/
    if (dest < src || dest >= (src + size))
    {
    /* safe memcopy. First copy to the destination buffer */ 
      lib_memcopy(buffer_safe,src,size);
    /*copy from buffer to the destination */
      lib_memcopy(dest,buffer_safe,size);
    }
    else 
    {
        MEMORY_EXCEPTION_HANDLING();  
    }    
 }

 else 
 {
    /*Do nothing. We can add a no operation and while 1 loop  */
 }

}


/**
 * @brief memset to set the user data to a defined value . 
 *
 * @param[in] dest Pointer to teh destination buffer where the data has to be copied. 
 * @param[in] src Pointer to the source buffer where the data is present. 
 * @param[in] size size of the buffer passed by the user .
 * @return None
 *  @param[out] None 
 */


void MemLib ::lib_memset (void *dest , uint8_t value , uint32_t size )
{
  auto itr = 0;

  if( (dest!= NULL) &&(size>0))
  {
     uint8_t *dst_ptr = static_cast<uint8_t*>(dest); 
     while(itr < size)
     {
      dst_ptr[itr] = value; 
      itr++;
     }
  }

  else 
  {
        MEMORY_EXCEPTION_HANDLING();  
  }

}

/**
 * @brief memmove` function to copy the data from one location to another with the overlap protection. 
 * 
 * 
 * 
 * @param[in] dest Pointer to teh destination buffer where the data has to be copied. 
 * @param[in] src Pointer to the source buffer where the data is present. 
 * @param[in] size size of the buffer passed by the user .
 * @return None
 *  @param[out] None 
 */

void MemLib ::lib_memmove(void *dest, const void *src, uint32_t size)
{
  auto itr = 0; 
  if( (src!= NULL && dest!=NULL) &&(size>0))
  {
      if (dest < src || dest >= (src + size))
      {
         lib_memcopy(dest,src,size);
      }
      else 
      {
            MEMORY_EXCEPTION_HANDLING();  
      }
  }
  else 
  {
           MEMORY_EXCEPTION_HANDLING();  
  }
}

/**
 * @brief memzero to set the user data to 0 . Very similar logic for GNU_Clear table.  
 *
 * @param[in] dest Pointer to teh destination buffer where the data has to be copied. 
 * @param[in] src Pointer to the source buffer where the data is present. 
 * @param[in] size size of the buffer passed by the user .
 * @return None
 *  @param[out] None 
 */
void MemLib:: lib_memzero(void *dest , uint32_t size )
{
    auto itr = 0;
    if((dest != NULL) && (size != 0 ))
    {
      uint8_t *dst = static_cast<uint8_t*>(dest); 
      while(itr  < size)
      {
        dst[itr] = 0;   
        itr++;
      }
   }
   else 
   {
        MEMORY_EXCEPTION_HANDLING();  
   } 
}