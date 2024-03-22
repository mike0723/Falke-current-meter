#ifndef __OLED_H__
#define __OLED_H__

#include <SSD1306Wire.h>

void setup_oled (void);
void oled_write (int *ival, float *val);

void oled_ota_begin (void);
void oled_ota_progress (unsigned val);
void oled_ota_end (void);

#endif /* __OLED__ */
