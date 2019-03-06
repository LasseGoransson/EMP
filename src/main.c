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

/*****************************    Defines    *******************************/
/*****************************   Constants   *******************************/
/*****************************   Variables   *******************************/
extern INT16S ticks;
int btn_timeout = 0;
int combinationState = 0;
/*****************************   Functions   *******************************/

int check_btn_event(void)
{
  // SW 1
  if(!( GPIO_PORTF_DATA_R & 0x10) && (ticks - btn_timeout > 100))
  {
    btn_timeout = ticks;
    //set_LED_Color(LED_COLOR_RED);
    return 1;
  }
  // SW 2
  if(!( GPIO_PORTF_DATA_R & 0x01) && (ticks - btn_timeout > 100))
  {
    btn_timeout = ticks;
  //  set_LED_Color(LED_COLOR_RED);
    return 2;
  }
  return 0;
}

int check_combination(int btn_event, int combinationState)
{
  switch (combinationState)
  {
    case 0:
      if (btn_event == 1)
      {
        combinationState++;

      }
      else if (btn_event == 2)
      {
        combinationState = 0;
      }

      break;
    case 1:
      if (btn_event == 2)
      {
        combinationState++;

      }
      else if (btn_event == 1)
      {
        combinationState = 0;
      }
      break;
    case 2:
      if (btn_event == 2)
      {
        combinationState++;

      }
      else if (btn_event == 1)
      {
        combinationState = 0;
      }
      break;
    case 3:
      if (btn_event == 1)
      {
        combinationState++;

      }
      else if (btn_event == 2)
      {
        combinationState = 0;
      }
      break;
    case 4:
      if (btn_event == 2)
      {
        combinationState++;

      }
      else if (btn_event == 1)
      {
        combinationState = 0;
      }
      break;
    case 5:
      if (btn_event >0)
      {
        combinationState = 0;
      }
      break;
  }
  return combinationState;
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
  enable_global_int();



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



  combinationState = 0;

  // Loop forever.
  while(1)
  {

    set_LED_off();
    int btn_event = check_btn_event(); // Get current btn state
    combinationState = check_combination(btn_event,combinationState);

    switch (combinationState) {
      case 0:
      //set_LED_off();
      set_LED_Color(LED_COLOR_RED);
      break;

      case 5:
        set_LED_Color(LED_COLOR_GREEN);
      break;
    }




  }

  return( 0 );
}
