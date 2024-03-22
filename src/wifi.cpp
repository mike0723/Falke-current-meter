#include "wifi.h"
#include "blink.h"

const char* ssid[] = { "WH-E8372", "MhD-9750", "" };
const char* password[] = { "W33rhuisjE", "qu4ck437uf", "" };

void setup_wifi (void)
{
    int i = 0;
    
    WiFi.mode(WIFI_STA);

    while (ssid[i][0] != 0)
    {
	blink (i + 1);
	WiFi.begin (ssid[i], password[i]);

	Serial.print ("connecting to ");
	Serial.println (ssid[i]);
	
	if (WiFi.waitForConnectResult () == WL_CONNECTED)
	{
	    Serial.print("IP address: ");
	    Serial.println(WiFi.localIP());
	    break;
	}

	i++;
    }

    if (ssid[i][0] == 0)
    {
	Serial.println("Connection Failed! Rebooting...");
	delay(1000);
	ESP.restart();
    }
}
