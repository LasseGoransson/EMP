
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "counter_handeling.h"

void counter_auto_mode(void)
{
  int ticks = getCountTicks();

  int choice = ticks % 8;

  if (choice == 0)
  {
    GPIO_PORTF_DATA_R &= ~(0x0E);;
  }

  if (choice == 1)
  {
    GPIO_PORTF_DATA_R|=(0x08);
  }


  if (choice == 2)
  {
    GPIO_PORTF_DATA_R |=(0x04); // 1100
  }


  if (choice == 3)
  {
    GPIO_PORTF_DATA_R |=(0x0c); // 1100
  }


  if (choice == 4)
  {
    GPIO_PORTF_DATA_R |=(0x02); // 1100
  }


  if (choice == 5)
  {
    GPIO_PORTF_DATA_R |=(0x09); // 1100
  }


  if (choice == 6)
  {
    GPIO_PORTF_DATA_R |=(0x06); // 1100
  }


  if (choice == 7)
  {
    GPIO_PORTF_DATA_R |= (0x0E); // 1100
  }

  GPIO_PORTF_DATA_R &= ~(0x0E);



}
