#ifndef _LIBRGB_H
  #define _LIBRGB_H

  #define LED_COLOR_GREEN 0x08
  #define LED_COLOR_BLUE  0x04
  #define LED_COLOR_CYAN  0x0c
  #define LED_COLOR_RED   0x02
  #define LED_COLOR_YELLOW 0x0A
  #define LED_COLOR_MANGENTA 0x06
  #define LED_COLOR_WHITE  0x0E

  #define TRAFFIC_GREEN 0x0C
  #define TRAFFIC_YELLOW 0x0A
  #define TRAFFIC_RED 0x06
  #define TRAFFIC_RED_YELLOW 0x02
  #define TRAFFIC_OFF 0x0E



void led_setup(void);
void set_LED_Color(int color);
void set_LED_off(void);



  /****************************** End Of Module *******************************/
  #endif
