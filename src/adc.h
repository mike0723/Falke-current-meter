#ifndef __ADC_H__
#define __ADC_H__

#include "Wire.h"
#include "ADS1X15.h"

#define NUM_VALUES 8
#define VALUESTR_LEN 160

/* 1x battery voltage, 5x battery current, 2x spare */
extern int ivalues[NUM_VALUES];
extern float fvalues[NUM_VALUES];

void setup_adc (void);
void adc_read (void);
void adc_getvaluestr (char *s, const char *query);

#endif /* __ADC_H__ */
