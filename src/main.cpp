#include "blink.h"
#include "wifi.h"
#include "ota.h"
#include "adc.h"
#include "http.h"
#include "oled.h"
#include "5x100a.h"

unsigned cycle_count = 0;

void setup()
{
    setup_led ();
    
    Serial.begin(115200);
    Serial.println("Booting");

    Wire.begin ();
    setup_adc ();
    setup_oled ();

    setup_wifi ();
    setup_ota ();
    
    MDNS.begin ("esp8266");

    setup_http ();

    Serial.println("Ready");

    blink (10);
}

void loop ()
{
    cycle_count++;
    
    ArduinoOTA.handle();

    adc_read ();

#if 1
    blink (1);
#else
    delay (10);
#endif
    
    delay (880);
}
