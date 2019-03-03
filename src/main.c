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
#include "libRGB.h"

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

  int current_color = 0; // Current color to display
  extern INT16S ticks;
  int when_pressed = 0;
  int last_change = 0;
  int counter_dir = 1;
  int auto_mode = 0;
  int entry_longpress = 0;
  int last_auto_change = 0;
  int auto_mode_timestamp = 0;

  // Loop forever.
  while(1)
  {
    if (auto_mode == 1)
    {
        if ((ticks - last_auto_change)> 20)
        {
          last_auto_change = ticks;
          if (counter_dir)
          {
            current_color++;

          }
          else
          {
            current_color--;
          }
          if (current_color > 7)
          {
            current_color = 0;
          }
          if (current_color < 0)
          {
            current_color = 7;
          }
        }

        if(!( GPIO_PORTF_DATA_R & 0x10) && (ticks - auto_mode_timestamp) > 200)
        {
          auto_mode = 0;
        }


      switch (current_color)
            {
              case 0:
                set_LED_off();
              break;
              case 1:
                set_LED_Color(LED_COLOR_GREEN);
              break;
              case 2:
                set_LED_Color(LED_COLOR_BLUE);
              break;
              case 3:
                set_LED_Color(LED_COLOR_CYAN);
              break;
              case 4:
              set_LED_Color(LED_COLOR_RED);
              break;
              case 5:
                set_LED_Color(LED_COLOR_YELLOW);
              break;
              case 6:
                set_LED_Color(LED_COLOR_MANGENTA);
              break;
              case 7:
                set_LED_Color(LED_COLOR_WHITE);
              break;
            }
    }
    else
    {

    switch (current_color)
          {
            case 0:
              set_LED_off();
            break;
            case 1:
              set_LED_Color(LED_COLOR_GREEN);
            break;
            case 2:
              set_LED_Color(LED_COLOR_BLUE);
            break;
            case 3:
              set_LED_Color(LED_COLOR_CYAN);
            break;
            case 4:
            set_LED_Color(LED_COLOR_RED);
            break;
            case 5:
              set_LED_Color(LED_COLOR_YELLOW);
            break;
            case 6:
              set_LED_Color(LED_COLOR_MANGENTA);
            break;
            case 7:
              set_LED_Color(LED_COLOR_WHITE);
            break;
          }


        // Button check
        if( GPIO_PORTF_DATA_R & 0x10)
        {
            // Not pressed
                    if ((ticks - when_pressed) > 2)
                    {
                      // Valid click check for doubled click
                      if ((ticks - last_change) < 40)
                      {
                        // invert counter
                        if (counter_dir)
                        {
                          counter_dir = 0;
                        }
                        else
                        {
                          counter_dir = 1;
                        }
                      }
                        if (counter_dir)
                        {
                          current_color++;

                        }
                        else
                        {
                          current_color--;
                        }
                        last_change = ticks;
                        entry_longpress = 0;
                    }

                    when_pressed = ticks;
                    }

        else
        {
          // Pressed
          int startpress = ticks;

          while (!(GPIO_PORTF_DATA_R & 0x10))
          {
          //  set_LED_Color(LED_COLOR_RED);
            if((ticks-startpress) > 400)
            {
              auto_mode=1;
              auto_mode_timestamp = ticks;
              break;
            }
            else
            {
              set_LED_off();
            }

            //set_LED_Color(LED_COLOR_GREEN);
          };







        }

        if (current_color > 7)
        {
          current_color = 0;
        }
        if (current_color < 0)
        {
          current_color = 7;
        }


  }



  }

  return( 0 );
}
