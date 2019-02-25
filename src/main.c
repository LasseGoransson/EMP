/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 1, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick.h"
#include "counter_handeling.h"
#include "timer0.c"

/*****************************    Defines    *******************************/
/*****************************   Constants   *******************************/
/*****************************   Variables   *******************************/
/*****************************   Functions   *******************************/



int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  disable_global_int();
  init_systick();
  enable_global_int();


  int auto_mode = 1;
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

  // Setup debounce timer





  // Loop forever.
  while(1)
  {
    if (auto_mode == 1)
    {
      counter_auto_mode();
    }
  }
  return( 0 );
}
