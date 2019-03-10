
#include "emp_type.h"
#include "traffic_light.h"
#include "libRGB.h"
#include "swtimers.h"
#include "btn.h"



static trafic_state = TS_NORMAL;
void run_traffic_light(int event)
{

  switch (trafic_state) {
    case TS_NORMAL:
      normal_mode();
      if (event == BE_SINGLE_PRESS)
      {
        trafic_state = TS_NORVIGIAN;
      }
      if(event == BE_DOBBELT_PRESS)
      {
        trafic_state = TS_EMERGENCY;
      }
    break;

    case TS_NORVIGIAN:
      norvigian_mode();
      if (event == BE_LONG_PRESS)
      {
        trafic_state = TS_NORMAL;
      }
      if(event == BE_DOBBELT_PRESS)
      {
        trafic_state = TS_EMERGENCY;
      }
    break;

    case TS_EMERGENCY:
      emergency_mode();
      if (event == BE_LONG_PRESS)
      {
        trafic_state = TS_NORMAL;
      }
      if (event == BE_SINGLE_PRESS)
      {
        trafic_state = TS_NORVIGIAN;
      }
    break;
  }


}


static INT16U nor_timer = TIM_1_SEC;
static INT8U nor_state = 1;
void norvigian_mode(void)
{
    switch (nor_state) {
      case 1:
        if (!--nor_timer)
        {
          set_LED_Color(TRAFFIC_YELLOW);
          nor_timer = TIM_1_SEC;
          nor_state = 0;
        }
      break;

        case 0:
          if (!--nor_timer)
          {
            set_LED_Color(TRAFFIC_OFF);
            nor_timer = TIM_1_SEC;
            nor_state = 1;
          }
        break;
    }

}



void emergency_mode(void)
{
set_LED_Color(TRAFFIC_RED);
}


static normal_state = NS_GETREADY;
static INT8U normal_mode_timer = TIM_1_SEC;
void normal_mode(void)
{


  switch (normal_state) {
    case NS_GETREADY:
    if (! --normal_mode_timer)
    {
      set_LED_Color(TRAFFIC_RED_YELLOW);
      normal_state = NS_GO;
      normal_mode_timer = TIM_1_SEC;
    }

    break;

    case NS_GO:
    if (! --normal_mode_timer)
    {
      set_LED_Color(TRAFFIC_GREEN);
      normal_state = NS_CLEAR;
      normal_mode_timer = TIM_1_SEC;
    }

    break;

    case NS_CLEAR:
    if (! --normal_mode_timer)
    {
      set_LED_Color(TRAFFIC_YELLOW);
      normal_state = NS_STOP;
      normal_mode_timer = TIM_1_SEC;
    }

    break;

    case NS_STOP:
    if (! --normal_mode_timer)
    {
      set_LED_Color(TRAFFIC_RED);
      normal_state = NS_GETREADY;
      normal_mode_timer = TIM_1_SEC;
    }

    break;
  }
}
