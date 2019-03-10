#include "emp_type.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "btn.h"
#include "swtimers.h"
#include "libRGB.h"

int button_pressed(void)
{
  // SW 1

return( !(GPIO_PORTF_DATA_R & 0x10) );  // SW1 at PF4

}

static INT8U bs_state = BS_IDLE;

INT8U get_btn_event(void)
{

  static INT16U btn_timer;
  INT8U btn_event = BE_NO_EVENT;

  switch(bs_state)
  {
    case BS_IDLE:
  //set_LED_Color(LED_COLOR_GREEN);
      // Path to First_press
      if (button_pressed())
      {
        bs_state = BS_FIRST_PRESS;
        btn_timer = TIM_2_SEC;
      }
      break;
    case BS_FIRST_PRESS:
    //set_LED_Color(LED_COLOR_RED);
      // Path to Long_press
      if (!(--btn_timer))
      {
          btn_event = BE_LONG_PRESS;
          bs_state = BS_LONG_PRESS;
      }
      // Path to BS_FIRST_RELEASE
      if (!button_pressed())
      {
        bs_state = BS_FIRST_RELEASE;
        btn_timer = TIM_100_MSEC;
      }
      break;
    case BS_FIRST_RELEASE:
    //set_LED_Color(LED_COLOR_CYAN);
      // Path to BS_IDLE
      if (!(--btn_timer))
      {
        bs_state = BS_IDLE;
        btn_event = BE_SINGLE_PRESS;
      }
      // Path to BS_SECOND_PRESS
      if (button_pressed())
      {
        bs_state = BS_SECOND_PRESS;
        btn_timer = TIM_2_SEC;
      }
      break;
    case BS_SECOND_PRESS:
      //Path to BS_LONG_PRESS
      if (!(--btn_timer))
      {
        bs_state = BS_LONG_PRESS;
        btn_event = BE_LONG_PRESS;
      }
      // Path to BS_IDLE
      if (!button_pressed())
      {
        bs_state = BS_IDLE;
        btn_event = BE_DOBBELT_PRESS;
      }
    break;
  case BS_LONG_PRESS:
      if(!button_pressed())
      {
        bs_state = BS_IDLE;
      }

  break;
  default:
    break;


  }

  return btn_event;

}
