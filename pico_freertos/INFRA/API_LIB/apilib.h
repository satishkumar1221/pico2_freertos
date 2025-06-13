/******************************************************************************
 * File:        api_lib.h
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

#ifndef APILIB_H
#define APILIB_H


#include<stdio.h> 
#include<stdint.h>
#include <iostream> 
//#include "pico/stdio.h"



using namespace std;  

#define CATCH_EXCEPTION() while(1) {  }

template <typename T>
class API_LIB
{
   public :
      API_LIB(); 
      void set_bits(T* src_ptr , const T bit_num); 
      void clear_bits(T* src_ptr , const T bit_num);
      void set_bits_mask(T* src_ptr , const T bit_mask);
      void clear_bits_mask(T* src_ptr , const T bit_mask);
      void toggle_bits(T* src_ptr , const T bit_num);
     T  add_uint_overflow_protection(T* result , T A , T B );
     T subs_uint_overflow_protection(T* result , T A , T B );
      T mul_uint_overflow_protection(T* result , T A , T B );

};

#define NUMBER_BITS_TO_BYTES 8u
typedef enum 
{
  None = 0,
  en_uint8 =1 ,
  en_uint16, 
  en_uint32 =4,
  en_uint64 =8 
}entag_datatype; 



template <typename T>
API_LIB<T> :: API_LIB()
{

}

template <typename T>
void API_LIB<T> :: set_bits(T* src_ptr , const T bit_num)
{ 
   auto total_bits  = ((sizeof(T)) * NUMBER_BITS_TO_BYTES); 
   if(((bit_num < total_bits) && (bit_num >= 0)) && (src_ptr != NULL))
   {
      *src_ptr |= (static_cast<T>(1) << bit_num); 
   }
   else 
   {
      CATCH_EXCEPTION(); 
   }
}

template <typename T>
void API_LIB<T>:: clear_bits(T* src_ptr , const T bit_num)
{
     auto total_bits  = ((sizeof(T)) * NUMBER_BITS_TO_BYTES); 
   if(((bit_num < total_bits) && (bit_num >= 0)) && (src_ptr != NULL))
   {
      *src_ptr &= (~(static_cast<T>(1) << bit_num))  ; 
   }
   else 
   {
      CATCH_EXCEPTION(); 
   }
}
template <typename T>

void API_LIB<T>:: set_bits_mask(T* src_ptr , const T bit_mask)
{ 

   if((src_ptr != NULL))
   {
      *src_ptr |= bit_mask; 
   }
   else 
   {
      CATCH_EXCEPTION(); 
   }
}
template <typename T>
void API_LIB<T>:: clear_bits_mask(T* src_ptr , const T bit_mask)
{ 
    if((src_ptr != NULL))
   {
      *src_ptr &= bit_mask; 
   }
   else 
   {
      CATCH_EXCEPTION(); 
   }
}


#endif

