#include "../ring_buffer/ring_buff.h"
#include <gtest/gtest.h>

const uint8_t buff_size = 4;
const uint8_t values_for_test[buff_size] = {1, 2, 3, 4};
    
static void map_function_increment(uint8_t* element);
static uint8_t reduce_function_sum(uint8_t prev, uint8_t next);

TEST(ring_buffer_tests, initing_test)
{
    ring_buff_t* rb = ring_buff_init(buff_size);
    
    EXPECT_EQ(rb->size , buff_size);
    EXPECT_EQ(rb->num_of_values, 0);
    
    ring_buff_delete(rb);
}

TEST(ring_buffer_tests, push_pop_test)
{
    ring_buff_t* rb = ring_buff_init(buff_size);
    
    //pushing values to the buffer
    for(uint8_t idx = 0; idx < buff_size; idx++)
    {
        ring_buff_push(values_for_test[idx], rb);
    }
    
    // checking if values are correct
    uint8_t readed_out_value = 0;
    for(uint8_t idx = 0; idx < buff_size; idx++)
    {
        ring_buff_get_by_id(&readed_out_value, rb, idx);
        EXPECT_EQ(values_for_test[idx], readed_out_value);
    }
    
    // Now run a sequence of tests, where firstly getiing value without deleting it and then with deleting
    uint8_t tmp_readed_out_value;
    for(uint8_t idx = 0; idx < buff_size; idx++)
    {
        // reading value without deleting
        ring_buff_get(&tmp_readed_out_value, rb, RB_GET_SHOW);
        EXPECT_EQ(values_for_test[idx], tmp_readed_out_value);
        // reading value with deleting
        ring_buff_get(&readed_out_value, rb, RB_GET_POP);
        EXPECT_EQ(tmp_readed_out_value, readed_out_value);
    }
    
    //verifing if ring_buffer is empty now
    EXPECT_EQ(rb->num_of_values, 0);
    
    ring_buff_delete(rb);
}

TEST(ring_buffer_tests, map_function_test)
{
    ring_buff_t* rb = ring_buff_init(buff_size);
    
    //pushing values to the buffer
    for(uint8_t idx = 0; idx < buff_size; idx++)
    {
        ring_buff_push(values_for_test[idx], rb);
    }
    
    ring_buff_map(rb, map_function_increment);
    
    uint8_t readed_out_value = 0;
    //verifing if all values are incremented
    for(uint8_t idx = 0; idx < buff_size; idx++)
    {
        ring_buff_get_by_id(&readed_out_value, rb, idx);
        EXPECT_EQ(values_for_test[idx] + 1, readed_out_value);
    }
    
    ring_buff_delete(rb);
}

TEST(ring_buffer_tests, reduce_function_test)
{   
    uint8_t target_sum = 0;
    uint8_t result = 0;
    
    ring_buff_t* rb = ring_buff_init(buff_size);
    
    //pushing values to the buffer
    for(uint8_t idx = 0; idx < buff_size; idx++)
    {
        ring_buff_push(values_for_test[idx], rb);
        // accumulating sum  for future test
        target_sum += values_for_test[idx];
    }
    
    ring_buff_reduce(&result, rb, reduce_function_sum);
    
    EXPECT_EQ(result, target_sum);
    
    ring_buff_delete(rb);
}

void map_function_increment(uint8_t* element)
{
    *element = *element + 1;
}
uint8_t reduce_function_sum(uint8_t prev, uint8_t next)
{
    return prev + next;
}