#ifndef UI_H_
#define UI_H_

#define START_ANIMATION 0
#define CLOCK_INTERFACE 1
#define EDIT_CLOCK_INTERFACE 2
#define EDIT_INVALID_ANIMATION 3
#define EDIT_SUCCESS_ANIMATION 4

void ui_init(void);

void change_ui(int ui);

void show_ui(void);

void ui_key(int key);

#endif /*UI_H_*/
