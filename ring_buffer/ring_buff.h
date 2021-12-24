#ifndef RING_BUFF_H
#define RING_BUFF_H

#include <stdint.h>
#include <stddef.h>
#include "ring_buff_conf.h"

typedef struct
{
    size_t size;
    uint32_t head;
    uint32_t tail;
    uint32_t num_of_values;
    BUF_TYPE* storage;
} ring_buff_t;

typedef enum
{
    RB_OK,
    RB_ERR_EMPTY,
    RB_ERR_NULL_ASSIGN,
} eRingBuffErrCode;

typedef enum
{
    RB_GET_SHOW,
    RB_GET_POP,
} eRingBuffGetType;


ring_buff_t* ring_buff_init(size_t size_needed);

void ring_buff_delete (ring_buff_t* ring_buff);

void ring_buff_push (BUF_TYPE value, ring_buff_t* ring_buffer);

eRingBuffErrCode ring_buff_get (BUF_TYPE* ret_val, ring_buff_t* ring_buffer, eRingBuffGetType get_type);

eRingBuffErrCode ring_buff_for_each(ring_buff_t* ring_buffer);


#endif