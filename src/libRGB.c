

#include "libRGB.h"
#include "emp_type.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"


void led_setup(void)
{
  int dummy;

  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Unlock the CR register
  GPIO_PORTF_CR_R   = 0xFF;        // Enable overwrite of PUR to FP0

  // Set the direction as output (PF1).
  GPIO_PORTF_DIR_R = 0x0E;

  // Enable the GPIO pins for digital function (PF0 and PF1).
  GPIO_PORTF_DEN_R = 0x1F;

  // Enable internal pull-up (PF1).
  GPIO_PORTF_PUR_R = 0x11;
}

void set_LED_Color(int color)
{
  GPIO_PORTF_DATA_R &= ~(0x0E);
  GPIO_PORTF_DATA_R |=(color);
}

void set_LED_off(void)
{
  GPIO_PORTF_DATA_R &= ~(0x0E);
}
