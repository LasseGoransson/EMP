#ifndef BTN_H_
#define BTN_H_

#define BS_IDLE 0
#define BS_FIRST_PRESS 1
#define BS_FIRST_RELEASE 2
#define BS_SECOND_PRESS 3
#define BS_LONG_PRESS 4

#define BE_SINGLE_PRESS 1
#define BE_DOBBELT_PRESS 2
#define BE_LONG_PRESS 3
#define BE_NO_EVENT 0

int button_pressed(void);
INT8U get_btn_event(void);

#endif
