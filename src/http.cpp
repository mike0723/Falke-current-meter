#include "http.h"
#include "adc.h"

#define PARAM_MESSAGE "corr"

AsyncWebServer server(80);

void notFound (AsyncWebServerRequest *request)
{
    request->send (404, "text/plain", "Not found");
}

void setup_http (void)
{
    server.on ("/", HTTP_GET, [](AsyncWebServerRequest *request) {
	String query_str;
	char valuestr[VALUESTR_LEN];

	if (request->hasParam(PARAM_MESSAGE))
            query_str = request->getParam(PARAM_MESSAGE)->value();
	
	adc_getvaluestr (valuestr, query_str.c_str ());
	
	request->send(200, "text/plain", valuestr);	
    });

    server.onNotFound(notFound);

    server.begin();
}
