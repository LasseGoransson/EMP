

#include "libRGB.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"


void set_LED_Color(int color)
{
  GPIO_PORTF_DATA_R &= ~(0x0E);
  GPIO_PORTF_DATA_R |=(color);
}

void set_LED_off(void)
{
  GPIO_PORTF_DATA_R &= ~(0x0E);
}
