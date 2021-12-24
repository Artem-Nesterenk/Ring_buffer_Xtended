#include "stdio.h"
#include "main.h"
#include "ring_buff.h"
#include <stdlib.h>
int main (void)
{
    ring_buff_t* adc = ring_buff_init(4);
    ring_buff_push(1, adc);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_push(2, adc);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_get(NULL, adc, RB_GET_POP);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_push(3, adc);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_push(6, adc);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_push(7, adc);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_push(8, adc);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_push(11, adc);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_get(NULL, adc, RB_GET_POP);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    ring_buff_get(NULL, adc, RB_GET_POP);
    ring_buff_for_each(adc);
    printf("-------------------\n");
    return 0;
}