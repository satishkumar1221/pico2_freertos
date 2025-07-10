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


#define E_OK 0u 

#define E_NOT_OK 1u

#define CATCH_EXCEPTION() while(1) {  }
/**
 * @brief Template class for bit manipulation and arithmetic operations with overflow protection.
 *
 * This template class provides methods to manipulate bits, apply masks, and perform arithmetic operations
 * with built-in overflow protection. The template parameter `T` represents the data type used for bitwise
 * operations (e.g., `uint32_t`, `uint16_t`, etc.).
 */
template <typename T>
class API_LIB
{
   public :
    /**
     * @brief Default constructor for the API library class.
     *
     * Initializes internal variables and settings for bit manipulation and arithmetic operations.
     */
      API_LIB(); 
         /**
     * @brief Sets specific bits in a given memory location using bit number.
     *
     * This method sets the bits at the specified position (`bit_num`) to 1 in the target memory location
     * pointed to by `src_ptr`.
     *
     * @param src_ptr Pointer to the memory location where bits are set.
     * @param bit_num The bit number (position) to set. Bit numbering starts from 0 at the least significant bit (LSB).
     */
      void set_bits(T* src_ptr , const T bit_num); 
          /**
     * @brief Clears specific bits in a given memory location using bit number.
     *
     * This method clears the bits at the specified position (`bit_num`) to 0 in the target memory location
     * pointed to by `src_ptr`.
     *
     * @param src_ptr Pointer to the memory location where bits are cleared.
     * @param bit_num The bit number (position) to clear. Bit numbering starts from 0 at the least significant bit (LSB).
     */

      void clear_bits(T* src_ptr , const T bit_num);
          /**
     * @brief Sets specific bits in a given memory location using a bit mask.
     *
     * This method sets the bits represented by `bit_mask` to 1 in the target memory location pointed to by
     * `src_ptr`. The least significant bit (LSB) of `bit_mask` corresponds to the least significant bit (LSB)
     * of the data type `T`.
     *
     * @param src_ptr Pointer to the memory location where bits are set using a mask.
     * @param bit_mask The bit mask used to determine which bits to set. A 1 in the mask represents a bit to be set, while a 0 leaves the bit unchanged.
     */
      void set_bits_mask(T* src_ptr , const T bit_mask);
          /**
     * @brief Clears specific bits in a given memory location using a bit mask.
     *
     * This method clears the bits represented by `bit_mask` to 0 in the target memory location pointed to by
     * `src_ptr`. The least significant bit (LSB) of `bit_mask` corresponds to the least significant bit (LSB)
     * of the data type `T`.
     *
     * @param src_ptr Pointer to the memory location where bits are cleared using a mask.
     * @param bit_mask The bit mask used to determine which bits to clear. A 1 in the mask represents a bit to be cleared, while a 0 leaves the bit unchanged.
     */
      void clear_bits_mask(T* src_ptr , const T bit_mask);
          /**
     * @brief Toggles specific bits in a given memory location using bit number.
     *
     * This method toggles (inverts) the bits at the specified position (`bit_num`) in the target memory location
     * pointed to by `src_ptr`.
     *
     * @param src_ptr Pointer to the memory location where bits are toggled.
     * @param bit_num The bit number (position) to toggle. Bit numbering starts from 0 at the least significant bit (LSB).
     */
      void toggle_bits(T* src_ptr , const T bit_num);
    /**
     * @brief Performs addition with overflow protection for unsigned integers.
     *
     * This method adds two values (`A` and `B`) and stores the result in `result`, while checking for overflow.
     * If an overflow occurs, it returns `std::numeric_limits<T>::max()`.
     *
     * @param result Pointer to store the addition result.
     * @param A The first operand for addition.
     * @param B The second operand for addition.
     *
     * @return `result` if no overflow occurred, or `std::numeric_limits<T>::max()` if an overflow happened.
     */
     T  add_uint_overflow_protection(T* result , T A , T B );
         /**
     * @brief Performs subtraction with overflow protection for unsigned integers.
     *
     * This method subtracts two values (`A` and `B`) and stores the result in `result`, while checking for underflow.
     * If an underflow occurs (i.e., attempting to subtract a larger number from a smaller one), it returns 0.
     *
     * @param result Pointer to store the subtraction result.
     * @param A The minuend for subtraction.
     * @param B The subtrahend for subtraction.
     *
     * @return `result` if no underflow occurred, or 0 if an underflow happened.
     */
     T subs_uint_overflow_protection(T* result , T A , T B );
     
    /**
     * @brief Performs multiplication with overflow protection for unsigned integers.
     *
     * This method multiplies two values (`A` and `B`) and stores the result in `result`, while checking for overflow.
     * If an overflow occurs, it returns 0.
     *
     * @param result Pointer to store the multiplication result.
     * @param A The first operand for multiplication.
     * @param B The second operand for multiplication.
     *
     * @return `result` if no overflow occurred, or 0 if an overflow happened.
     */
      T mul_uint_overflow_protection(T* result , T A , T B );

      T increment_counter(T* src_ptr , const T value_to_be_incremented, const T threshold ); 

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

/**
 * @brief Flowchart illustrating the steps performed by the `set_bits_mask` method.
 *
 * @dot
 * digraph G {
   rankdir=TB;
   node [shape=box];
   "Start" [shape=plaintext];
   "End" [shape=plaintext];

   "Start" -> "Check if bit mask is non-zero";
   "Check if bit mask is non-zero" -> "Bitwise AND operation";
   "Bitwise AND operation" -> "Store result in memory location";
   "Bitwise AND operation" -> "End";
   "Check if bit mask is non-zero" -> "Return without modifying bits";
 }
 * @enduml
 */
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


template <typename T>
T API_LIB<T>:: increment_counter( T* src_ptr , const T value_to_be_incremented, const T threshold )
{ 
   
    if((src_ptr != NULL))
   {
        /* Satish To do : Write a swtich case base don the size. sizeof(T)*/
         *src_ptr += value_to_be_incremented; 
          if(*src_ptr >= threshold)
          {
            *src_ptr = threshold;
          }
   }
   else 
   {
      CATCH_EXCEPTION(); 
   }

   /*To do : temporary , As of now return E_OK */

   return(0);
}


#endif

