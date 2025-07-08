
#include "queue_custom.h"
Queue_Data_Struct V_Queue_DataStruct[TOTAL_NUMBER_QUEUES]; 

Queue_stat Queue :: Queue_init(void *ptr_user_buffer , Queue_Id type , int size_of_queue_buffer , int size_of_individual_element)
{
     Queue_stat stat;
    if((ptr_user_buffer != NULL) && (size_of_queue_buffer > 0) && (size_of_individual_element > 0))
    {
           V_Queue_DataStruct[type].ptr_user_Data = ptr_user_buffer;
           V_Queue_DataStruct[type].size_of_individual_element = size_of_individual_element; 
           V_Queue_DataStruct[type].size_of_queue_buffer = size_of_queue_buffer; 
           V_Queue_DataStruct[type].size_of_individual_element = size_of_individual_element; 
           V_Queue_DataStruct[type].tail = -1; /*To catch empty queue */
           V_Queue_DataStruct[type].head = -1; /*To catch empty queue */     
           stat = QUEUE_OK; 

    }
    else 
    {
        stat = QUEUE_ERROR; 
       
    }
     return (stat); 
}
    

Queue_stat Queue:: check_for_full_queue(Queue_Id type , const Queue_Data_Struct *ptr_queue)
{
     if(((ptr_queue->tail == -1) && (ptr_queue->head == (ptr_queue->size_of_queue_buffer))) \
        || ((ptr_queue->head + 1) == ptr_queue->tail) || (((ptr_queue->tail + 1) == ptr_queue->head) && (ptr_queue->tail != -1)))  
     {
        return (QUEUE_FULL); 
     }
     else 
     {
        return (QUEUE_OK); 
     }
}


Queue_stat Queue::check_for_empty_queue(Queue_Id type, const Queue_Data_Struct *ptr_queue)
{
     if(((ptr_queue->head == -1) && (ptr_queue->tail == -1)) ||
         ((ptr_queue->head == ptr_queue->tail)) && ((ptr_queue->head > 0) && (ptr_queue->tail > 0)))
     {
        return(QUEUE_EMPTY); 
     }
     else 
     {
        return(QUEUE_OK);
     }
}

Queue_stat Queue ::push_element_queue(Queue_Id type , const void *ptr_usr_data)
{
    uint32_t temp_head = 0;  
    uint32_t temp_tail = 0; 
    void* dest_ptr = NULL;
    Queue_stat stat;
    if((ptr_usr_data != NULL) && (type < TOTAL_NUMBER_QUEUES))
    {
        if(QUEUE_EMPTY == check_for_empty_queue(type , &V_Queue_DataStruct[type]))
        {
            V_Queue_DataStruct[type].head = 0; 
            /*Add the first element to  the queue*/
            dest_ptr =  static_cast<void*>(V_Queue_DataStruct[type].ptr_user_Data + (V_Queue_DataStruct[type].head * V_Queue_DataStruct[type].size_of_individual_element));
            lib_memcopy(dest_ptr,ptr_usr_data,V_Queue_DataStruct[type].size_of_individual_element);
            /*increment head to be read y for the next element to be inserted*/
            V_Queue_DataStruct[type].head++; 
            stat = QUEUE_OK; 
        }
        else if(check_for_full_queue(type , &V_Queue_DataStruct[type]) == QUEUE_OK)
        {
            V_Queue_DataStruct[type].head = V_Queue_DataStruct[type].head % V_Queue_DataStruct[type].size_of_queue_buffer; 
            dest_ptr =  static_cast<void*>(V_Queue_DataStruct[type].ptr_user_Data + (V_Queue_DataStruct[type].head * V_Queue_DataStruct[type].size_of_individual_element));
            lib_memcopy(dest_ptr,ptr_usr_data,V_Queue_DataStruct[type].size_of_individual_element); 
            if(check_for_full_queue(type , &V_Queue_DataStruct[type]) == QUEUE_OK)
            {
                    V_Queue_DataStruct[type].head++; 
            }
            else
            {
                   /*do nothing it is a full queue. */
            }
        
             stat = QUEUE_OK;
            
        }
        else if(check_for_full_queue(type , &V_Queue_DataStruct[type]) == QUEUE_FULL)
        {
             stat = QUEUE_FULL; 
        }
        else 
        {
            stat = QUEUE_ERROR; 
        }
    }
    else 
    {
        stat = QUEUE_ERROR; 
    }
        return(stat); 
        //else if(QUEUE_FULL == check_for_full_queue(type , &V_Queue_DataStruct[type]))
        
}

Queue_stat Queue ::pop_element_queue(Queue_Id type ,  void *ptr_usr_data)
{
     void* dest_ptr = NULL;
     Queue_stat stat; 
    if((type < TOTAL_NUMBER_QUEUES))
    {
        if(check_for_empty_queue(type , &V_Queue_DataStruct[type]) == QUEUE_EMPTY)
        {
            /*reset head and tail of circular queue*/
            V_Queue_DataStruct[type].tail = -1; 
            V_Queue_DataStruct[type].head = -1; 
            stat = QUEUE_EMPTY; 
        }
        else
        {
            if((V_Queue_DataStruct[type].tail == -1) && (V_Queue_DataStruct[type].head == 0))
            {
                dest_ptr =  static_cast<void*>(V_Queue_DataStruct[type].ptr_user_Data); /*start with tail equal to 0 */
                if(ptr_usr_data != NULL)
                {
                    lib_memcopy(ptr_usr_data,dest_ptr,V_Queue_DataStruct[type].size_of_individual_element); 
                }
                 stat = QUEUE_OK;
            }
            else 
          {
            V_Queue_DataStruct[type].tail = V_Queue_DataStruct[type].tail % V_Queue_DataStruct[type].size_of_queue_buffer;
            dest_ptr =  static_cast<void*>(V_Queue_DataStruct[type].ptr_user_Data + (V_Queue_DataStruct[type].tail * V_Queue_DataStruct[type].size_of_individual_element));
            if(ptr_usr_data != NULL)
            {
                lib_memcopy(ptr_usr_data,dest_ptr,V_Queue_DataStruct[type].size_of_individual_element); 
            }
            V_Queue_DataStruct[type].tail++; 
            stat = QUEUE_OK;
           } 
        }
    }
    else 
    {
       stat = QUEUE_ERROR; 
    }
    return(stat); 
}

Queue_stat Queue ::peek_element_queue(Queue_Id type , void *ptr_usr_data)
{   
    void *dest_ptr =NULL; 
    Queue_stat stat; 
    if((ptr_usr_data != NULL) && (type < TOTAL_NUMBER_QUEUES))
    {
        if(check_for_empty_queue(type , &V_Queue_DataStruct[type]) == QUEUE_EMPTY)
        {
            stat = QUEUE_EMPTY; 
        }
        else
        {
        
            if((V_Queue_DataStruct[type].tail == -1) && (V_Queue_DataStruct[type].head >= 0))
            {
                dest_ptr =  static_cast<void*>(V_Queue_DataStruct[type].ptr_user_Data); /*start with tail equal to 0 */
                if(ptr_usr_data != NULL)
                {
                    lib_memcopy(ptr_usr_data,dest_ptr,V_Queue_DataStruct[type].size_of_individual_element); 
                }
                 stat = QUEUE_OK;
            }
            else 
            {
             dest_ptr =  static_cast<void*>(V_Queue_DataStruct[type].ptr_user_Data + (V_Queue_DataStruct[type].tail * V_Queue_DataStruct[type].size_of_individual_element));
             lib_memcopy(ptr_usr_data,dest_ptr,V_Queue_DataStruct[type].size_of_individual_element); 
              stat = QUEUE_OK;
            }
             
        
       }

    }
    else 
    {
        stat = QUEUE_ERROR; 
    }

    return(stat);
}


    /*Control should never reach */
