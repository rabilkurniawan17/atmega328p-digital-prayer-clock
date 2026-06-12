/*
 * button.c
 *
 * Created: 5/22/2026 6:17:21 AM
 *  Author: Admin
 */ 
#include "button.h"


#define BUTTON_DATA(buttonHandle, buttonPin) \
    uint8_t button_read##buttonHandle (void) \
    { \
  return (!(BUTTON_PIN & (1 << BUTTON_##buttonPin))) ? 1 : 0; \
    }

BUTTON_LIST
#undef BUTTON_DATA
