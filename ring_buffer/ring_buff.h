#ifndef RING_BUFF_H
#define RING_BUFF_H

#include <stdint.h>
#include <stddef.h>
#include "ring_buff_conf.h"

/**
*   @brief Struct of the ring buffer
*/
typedef struct ring_buff_struct
{
    size_t size;                ///< number of elements, that can be stored in ring buffer
    uint32_t head;              ///< index of the head of the ring buffer
    uint32_t tail;              ///< index of the tail of the ring buffer
    uint32_t num_of_values;     ///< current amount of stored data
    BUF_TYPE* storage;          ///< the buffer itself
} ring_buff_t;

/**
*   @brief enumeration for error types
*/
typedef enum
{
    RB_OK,                       ///< No error, evetyrhing is fine
    RB_ERR_EMPTY,                ///< Seems like you`ve passed the empty buffer to a func
    RB_ERR_NULL_ASSIGN,          ///< Seems that you`ve provided NULL as a returned parameter for @ring_buff_get
    RB_ERR_NULL_INSTANCE,        ///< Your buffer wasn`t initialized
    RB_ERR_INVALID_ELEMENT_ID,   ///< You want to get element, that doesn`t exist. Are you sure, you want it?
} eRingBuffErrCode;

/**
*   @brief enumeration, that specify with type of @ref ring_buff_get function you want to invoke
*/
typedef enum
{
    RB_GET_SHOW,                ///< Get value at head`s position WITHOUT deleting it
    RB_GET_POP,                 ///< Get value at head`s position and delete it from buffer
} eRingBuffGetType;

/**
 * @brief initialyzing new ring buffer
 * @param size_needed number of elements that can be stored simultaneously in buffer 
 * @return pointer to a new ring_buffer
 */
ring_buff_t* ring_buff_init(size_t size_needed);

/**
 * @brief freeing memory, used for ring buffer
 * @param ring_buffer pointer to the buffer must be deleted
 * @return Error code @ref eRingBuffErrCode
 */
eRingBuffErrCode ring_buff_delete (ring_buff_t* ring_buffer);

/**
 * @brief pushing value to the buffer
 * @param value value to be pushed
 * @param ring_buffer pointer to the buffer, where value must be pushed
 * @return none
 */
void ring_buff_push (BUF_TYPE value, ring_buff_t* ring_buffer);

/**
 * @brief return value form the head of the buffer either deleiting ot or not, depends on @ref eRingBuffGetType
 * @param ret_val pointer to the variable, where returned value will be stored. Can be NULL only with @ref RB_GET_POP
 * @param ring_buffer pointer to the buffer
 * @param get_type specify if value must be left in the buffer @ref eRingBuffGetType
 * @return Error code @ref eRingBuffErrCode
 */
eRingBuffErrCode ring_buff_get (BUF_TYPE* ret_val, ring_buff_t* ring_buffer, eRingBuffGetType get_type);

/**
 * @brief return element by its id (like in normal array) IDs are counted from the head to the tail
 * @param ret_val pointer to the variable, where returned value will be stored
 * @param ring_buffer pointer to the buffer
 * @param id id of the element
 * @return Error code @ref eRingBuffErrCode
 */
eRingBuffErrCode ring_buff_get_by_id(BUF_TYPE* ret_val, ring_buff_t* ring_buffer, uint32_t id);

/**
 * @brief apply some function to all elements of the ring buffer
 * @param ring_buffer pointer to the buffer
 * @param map_func user-defined function which will be applied the the elements
 * @return Error code @ref eRingBuffErrCode
 */
eRingBuffErrCode ring_buff_map(ring_buff_t* ring_buffer, void (*map_func)(BUF_TYPE* element));

/**
 * @brief executes a user-supplied “reducer” callback function on each element of the array
 * Passing in the return value from the calculation on the preceding element. 
 * The final result of running the reducer across all elements of the array is a single value.
 * In result we`ll get sum of all the elements
 * @param ret_val pointer to the variable, where result will be stored. Also start value of recude function
 * @param ring_buffer pointer to the buffer
 * @param reduce_func user-defined reduce function
 * @return Error code @ref eRingBuffErrCode
 */
eRingBuffErrCode ring_buff_reduce(BUF_TYPE (*ret_val), ring_buff_t* ring_buffer, BUF_TYPE (*reduce_func)(BUF_TYPE prev, BUF_TYPE next));
#endif