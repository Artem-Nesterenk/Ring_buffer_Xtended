#include "stdio.h"
#include "main.h"
#include "../ring_buffer/ring_buff.h"
#include <stdlib.h>

int main (void)
{
    ring_buff_t* adc = ring_buff_init(4);
    ring_buff_push(1, adc);
    ring_buff_push(2, adc);
    ring_buff_push(3, adc);
    ring_buff_push(4, adc);
    return 0;
}