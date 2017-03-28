#include "delay.h"

void delay_us(uint n)
{
  for(;n>0;n--);
}


void delay_ms(uint n)
{
  uint i;
  for(; n > 0 ;n--)
    for(i = 0; i < 655;i++);
}
