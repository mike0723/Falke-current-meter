#include "oled.h"
#include "5x100a.h"
#include "fonts.h"

SSD1306Wire display (0x3c /*, SDA, SCL*/);

void setup_oled (void)
{
    display.init();
    display.setFont (ArialMT_Plain_10);
    display.setTextAlignment (TEXT_ALIGN_CENTER_BOTH);
    display.drawString (display.getWidth () / 2,
			display.getHeight () / 2,
			"Starting ...");
    display.display ();    
}

void oled_write (int *ival, float *val)
{
    char s[40];
    float sum = 0.0;

    for (int i = 1; i < 8; i++)
	sum += val[i];
    
    display.clear ();
    display.setTextAlignment (TEXT_ALIGN_LEFT);

    // line 1: voltage and current sum
    display.setFont(ArialMT_Plain_16);
    sprintf (s, "%2.2fV", val[0]);
    display.drawString (0, 0, s);
    sprintf (s, "%3.2fA", sum);
    display.drawString (64, 0, s);

    // line 2: current 1 and 5
    display.setFont(/*Monospaced_plain_10*/ArialMT_Plain_10);
    sprintf (s, "1:%8.2fA", val[1]);
    display.drawString (0, 18, s);
    sprintf (s, "5:%8.2fA", val[5]);
    display.drawString (64, 18, s);
    
    // line 3: current 2 and 6
    sprintf (s, "2:%8.2fA", val[3]);
    display.drawString (0, 30, s);
    sprintf (s, "6:%8.2fA", val[6]);
    display.drawString (64, 30, s);

    // line 4: current 3 and 7
    sprintf (s, "3:%8.2fA", val[2]);
    display.drawString (0, 42, s);
    sprintf (s, "7:%8.2fA", val[7]);
    display.drawString (64, 42, s);

    // line 5: current 4
    sprintf (s, "4:%8.2fA", val[4]);
    display.drawString (0, 54, s);
    sprintf (s, "| %d |", cycle_count);
    display.drawString (64, 54, s);
    
    display.display ();
}

void oled_ota_begin (void)
{
    display.clear ();
    display.setFont (ArialMT_Plain_10);
    display.setTextAlignment (TEXT_ALIGN_CENTER_BOTH);
    display.drawString (display.getWidth() / 2,
			display.getHeight() / 2 - 10,
			"OTA Update");
    display.display();    
}

void oled_ota_progress (unsigned val)
{
    display.drawProgressBar (4, 32, 120, 8, val);
    display.display ();    
}

void oled_ota_end (void)
{
    display.clear ();
    display.setFont (ArialMT_Plain_10);
    display.setTextAlignment (TEXT_ALIGN_CENTER_BOTH);
    display.drawString (display.getWidth () / 2,
			display.getHeight () / 2,
			"Flashing ...");
    display.display ();    
}
