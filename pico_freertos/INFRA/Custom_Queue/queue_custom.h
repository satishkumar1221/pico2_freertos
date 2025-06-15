
#ifndef QUEUE_CUSTOM_H
#define QUEUE_CUSTOM_H

#include <stdio.h>
#include <stdint.h>
#include "memlib.h"

using namespace std;
/*As the queue is not dynamically allocated and is general purpose user should add the queue ID here. This is the onky thing user have to do. user can pass any dataype*/
typedef enum 
{
    test_queue, 
   TOTAL_NUMBER_QUEUES
}Queue_Id; 

typedef enum 
{
    Circular_Queue, 
    Threadsafe_Queue, 
    Total_Queue_Types

}Queue_type; 

typedef struct
{
    void *ptr_user_queue_buffer; 
    void *ptr_user_Data; 
    int size_of_queue_buffer;
    int size_of_individual_element;
    int head;  
    int tail; 

}Queue_Data_Struct; 

typedef enum 
{
    QUEUE_EMPTY, 
    QUEUE_FULL,
    QUEUE_OK,
    QUEUE_ERROR
}Queue_stat; 


/*Adding this as a global variable as the queue is global and staically declared so the status has to be maintained irrespective  */
extern Queue_Data_Struct V_Queue_DataStruct[TOTAL_NUMBER_QUEUES]; 


class Queue : public MemLib
{
    public:  
    
    Queue_stat Queue_init(void *ptr_user_buffer , Queue_Id type , int size_of_queue_buffer , int size_of_individual_element); 
    Queue_stat push_element_queue(Queue_Id type , const void *ptr_usr_data);  
    Queue_stat pop_element_queue(Queue_Id type ,  void *ptr_usr_data); 
    Queue_stat peek_element_queue(Queue_Id type , void *ptr_usr_data); 
    private : 
    Queue_stat check_for_full_queue(Queue_Id type , const Queue_Data_Struct *ptr_queue); 
    Queue_stat check_for_empty_queue(Queue_Id type, const Queue_Data_Struct *ptr_queue);     

}; 



#endif 