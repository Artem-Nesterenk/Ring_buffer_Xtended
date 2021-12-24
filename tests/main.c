#include "stdio.h"
#include "main.h"
#include "../ring_buffer/ring_buff.h"
#include <stdlib.h>
void local_inc(uint8_t* c)
{
        *c = *c+1;
}
void local_print(uint8_t* c)
{
        printf("%d ", *c);
}
void local_multi(uint8_t* c)
{
        *c = *c * *c;
}
int main (void)
{
    ring_buff_t* adc = ring_buff_init(4);
    ring_buff_push(1, adc);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_push(2, adc);
    ring_buff_map(adc, local_print);
        printf("\n");
    ring_buff_push(3, adc);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_push(4, adc);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_push(5, adc);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_get(NULL,adc, RB_GET_POP);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_get(NULL,adc, RB_GET_POP);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_push(9, adc);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_push(10, adc);
    ring_buff_map(adc, local_print);
    printf("\n");
    ring_buff_get(NULL,adc, RB_GET_POP);
    ring_buff_map(adc, local_print);
    printf("\n");
    uint8_t a ;
    eRingBuffErrCode err;
    printf("\n head - > %d\n", adc->head);
    printf("\n tail - > %d\n", adc->tail);
    printf("\n");
    err = ring_buff_get_by_id(&a, adc, 0);
    printf("\n val - > %d\n", a);
    printf("\n err - > %d\n", err);
    printf("\n");
    err = ring_buff_get_by_id(&a, adc, 1);
    printf("\n val - > %d\n", a);
    printf("\n err - > %d\n", err);
    printf("\n");
    err = ring_buff_get_by_id(&a, adc, 2);
    printf("\n val - > %d\n", a);
    printf("\n err - > %d\n", err);
    printf("\n");
    err = ring_buff_get_by_id(&a, adc, 3);
    printf("\n val - > %d\n", a);
    printf("\n err - > %d\n", err);
    return 0;
}