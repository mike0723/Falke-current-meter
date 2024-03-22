#include <LibPrintf.h>

#include "adc.h"
#include "oled.h"
#include "5x100a.h"

int ivalues[NUM_VALUES];
float fvalues[NUM_VALUES];

/* correction values:
 * note: oder is: voltage, current 1, 3, 2, 4, 5, 6, 7
 */
float fcorr[NUM_VALUES] = { 0.15, 0.16, 0.18, -0.13, -2.12, 0.07, 0.0, 0.0 };
float ffact[NUM_VALUES] = { 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

ADS1115 ads[2];

static void setup_hw (void)
{
    int val;

    ads[0] = ADS1115 (0x48);
    ads[1] = ADS1115 (0x49);

    for (int i = 0; i < 2; i++)
    {
	ads[i].begin();
	ads[i].setGain(1);  // 4.096 volt

	for (int j = 0; j < 4; j++)
	{
	    val = ads[i].readADC (j);
	    Serial.println (ads[i].toVoltage (val), 3);
	}
    }
}

void setup_adc (void)
{
    ivalues[0] = 100;
    for (int i = 1; i < NUM_VALUES; i++)
    {
	ivalues[i] = 13333;
	fvalues[i] = 0.0;
    }

    setup_hw ();
}

void adc_read (void)
{
    for (int i = 0; i < 2; i++)
	for (int j = 0; j < 4; j++)
	    ivalues[4*i + j] = ads[i].readADC (j);
    
    // 4.096V full range, 0.125mV/bit
    fvalues[0] = ivalues[0] * 0.000125 * 24.7 / 4.7;     // voltage
    fvalues[0] *= ffact[0];
    fvalues[0] += fcorr[0];
    
    for (int i = 1; i < 8; i++)			// 7x current
    {
	fvalues[i] = ((float)ivalues[i] - 13333.0) * (100.0 / 10666.7);
	fvalues[i] *= ffact[i];
	fvalues[i] += fcorr[i];
    }
    
    oled_write (ivalues, fvalues);
    
    for (int i = 0; i < 8; i++)
    {
	Serial.print (ivalues[i]);
	Serial.print (" ");
    }
    Serial.println ();
}

void adc_getvaluestr (char *s, const char *query)
{
    snprintf (s, VALUESTR_LEN-1, "%u %2.2f %3.2f %3.2f %3.2f %3.2f %3.2f %3.2f %3.2f %s\n",
	     cycle_count,
	     fvalues[0], fvalues[1], fvalues[3], fvalues[2],
	     fvalues[4], fvalues[5], fvalues[6], fvalues[7],
	     query);
}
