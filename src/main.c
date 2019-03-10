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
#include "libRGB.h"
#include "btn.h"
#include "swtimers.h"

/*****************************    Defines    *******************************/




/*****************************   Constants   *******************************/
/*****************************   Variables   *******************************/
//extern INT16S ticks;
INT8U btn_event = BE_NO_EVENT;

/*****************************   Functions   *******************************/

void init_gpio(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  int dummy;

  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOF;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  // Set the direction as output (PF1, PF2 and PF3).
  GPIO_PORTF_DIR_R = 0x0E;
  // Set the direction as output (PD6).
  GPIO_PORTD_DIR_R = 0x40;

  // Enable the GPIO pins for digital function (PF0, PF1, PF2, PF3, PF4).
  GPIO_PORTF_DEN_R = 0x1F;
  // Enable the GPIO pins for digital function (PD6).
  GPIO_PORTD_DEN_R = 0x40;

  // Enable internal pull-up (PF0 and PF4).
  GPIO_PORTF_PUR_R = 0x11;
}

volatile INT16S ticks = 0;

void systick_handler(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  // Hardware clears systick int reguest
  ticks++;
}

int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  disable_global_int();
  init_systick();
  init_gpio();
  enable_global_int();



INT8U alive_timer = TIM_500_MSEC;
int on=0;
  // Loop forever.
  while(1)
  {

    // wait while ticks are 0;
    while( !ticks );

    // Remove a tick
    ticks--;

    if( ! --alive_timer )
    {
      alive_timer        = TIM_500_MSEC;
      GPIO_PORTD_DATA_R ^= 0x40;
    }

    if (button_pressed())
    {
        //set_LED_Color(LED_COLOR_RED);
    }
    else
    {
      //set_LED_Color(LED_COLOR_GREEN);
    }


   btn_event = get_btn_event();



    // Call tasks;
    switch (btn_event) {
      case BE_SINGLE_PRESS:
      set_LED_Color(LED_COLOR_BLUE);
      break;
      case BE_DOBBELT_PRESS:
      set_LED_Color(LED_COLOR_WHITE);
      break;
      case BE_LONG_PRESS:
      set_LED_Color(LED_COLOR_GREEN);
      break;
      default:
        break;
    }


  }

  return( 0 );
}
