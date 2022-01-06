#include "ring_buff.h"
#include <stdlib.h>
#include <stdio.h>
    // move head
    static void inc_buff_head(ring_buff_t* ring_buffer);

    // move tail
    static void inc_buff_tail(ring_buff_t* ring_buffer);

    ring_buff_t* ring_buff_init(size_t size_needed)
    {
        // allocate memory for new ring_buffer struct
        ring_buff_t* ring_buff = malloc(sizeof(ring_buff_t) + (size_needed * sizeof(BUF_TYPE)));
        
        if (ring_buff != NULL)
        {
            // initing default values
            ring_buff->size = size_needed;
            ring_buff->head = 0;
            ring_buff->tail = 0;
            ring_buff->num_of_values = 0;
            // allocate memory for the buffer exact
            ring_buff->storage = malloc(size_needed * sizeof(BUF_TYPE));     
        }
        
        return ring_buff;
    }

    eRingBuffErrCode ring_buff_delete (ring_buff_t* ring_buffer)
    {
        // if buffer was not allocated - do nothing
        if (ring_buffer == NULL)
        {
            return RB_ERR_NULL_INSTANCE;
        }
        
        // free allocated memory
        free(ring_buffer);
        return RB_OK;
    }

    void ring_buff_push (BUF_TYPE value, ring_buff_t* ring_buffer)
    {
        // save value
        ring_buffer->storage[ring_buffer->tail] = value;
        
        // checking if we need to loopback the array and move the head
        if (ring_buffer->tail == ring_buffer->head && ring_buffer->num_of_values == ring_buffer->size)
        {
            inc_buff_head(ring_buffer);
        }
        
        // increasing tail index
        inc_buff_tail(ring_buffer);
        
        // increase num of stored values
        ring_buffer->num_of_values = (ring_buffer->num_of_values == ring_buffer->size)
                                ? ring_buffer->num_of_values
                                :(ring_buffer->num_of_values + 1);
    }

    eRingBuffErrCode ring_buff_get (BUF_TYPE* ret_val, ring_buff_t* ring_buffer, eRingBuffGetType get_type)
    {
        // if no stored values - return error code
        if (ring_buffer->num_of_values == 0)
        {
            return RB_ERR_EMPTY;
        }
        
        // if no value needed to be return
        if (ret_val == NULL)
        {
            // avaliable only with RB_GET_POP option
            if (get_type == RB_GET_SHOW)
            {
                return RB_ERR_NULL_ASSIGN;
            }
            inc_buff_head(ring_buffer);                 
            ring_buffer->num_of_values--;   
            return RB_OK;
        }
        
        *ret_val = ring_buffer->storage[ring_buffer->head];
        
        // if RB_GET_POP option - move head
        if (get_type == RB_GET_POP)
        {
            inc_buff_head(ring_buffer);                      
            ring_buffer->num_of_values--;                        
        }
        
        return RB_OK;    
    }

    eRingBuffErrCode ring_buff_map(ring_buff_t* ring_buffer, void (*map_func)(BUF_TYPE* element))
    {
        if (ring_buffer->num_of_values == 0)
        {
            return RB_ERR_EMPTY;
        }
        uint32_t idx = ring_buffer->head;
        for (uint8_t counter = 0; counter < ring_buffer->num_of_values; counter ++)
        {
            map_func(&ring_buffer->storage[idx++]);
            if (idx == ring_buffer->size)
            {
                idx = 0;
            }
        }
        return RB_OK;
    }

    eRingBuffErrCode ring_buff_get_by_id(BUF_TYPE* ret_val, ring_buff_t* ring_buffer, uint32_t id)
    {
        if (ring_buffer == NULL)
        {
            return RB_ERR_NULL_INSTANCE;
        }
        
        if (id >= ring_buffer->num_of_values)
        {
            return RB_ERR_INVALID_ELEMENT_ID;
        }
        
        if (ring_buffer->head < ring_buffer->tail)
        {
            *ret_val = ring_buffer->storage[ring_buffer->head + id];
        }
        uint32_t elements_till_end = ring_buffer->size - ring_buffer->head;
        if ((int32_t)elements_till_end - (int32_t)id > 0)
        {
            *ret_val = ring_buffer->storage[ring_buffer->head + id];
        }
        else
        {
            *ret_val = ring_buffer->storage[id - elements_till_end];
        }
        return RB_OK;
    }

    eRingBuffErrCode ring_buff_reduce(BUF_TYPE (*ret_val), ring_buff_t* ring_buffer, BUF_TYPE (*reduce_func)(BUF_TYPE prev, BUF_TYPE next))
    {
        if (ring_buffer == NULL)
        {
            return RB_ERR_NULL_INSTANCE;
        }
        
        if (ring_buffer->num_of_values == 0)
        {
            return RB_ERR_EMPTY;
        }
        BUF_TYPE accumulator = *ret_val;
        BUF_TYPE tmp;
        
        for (uint32_t idx = 0; idx < ring_buffer->num_of_values; idx++)
        {
            ring_buff_get_by_id(&tmp,ring_buffer, idx);
            accumulator = reduce_func(accumulator, tmp);
        }
        
        *ret_val = accumulator;
        
        return RB_OK;
    }

    /* *********** Static functions implementations **************/

    void inc_buff_head(ring_buff_t* ring_buffer)
    {
        ring_buffer->head = (ring_buffer->head == (ring_buffer->size - 1)) 
                            ? 0 
                            : (ring_buffer->head + 1);
    }

    static void inc_buff_tail(ring_buff_t* ring_buffer)
    {
        ring_buffer->tail = (ring_buffer->tail == (ring_buffer->size - 1)) 
                            ? 0 
                            : (ring_buffer->tail + 1);
    }
