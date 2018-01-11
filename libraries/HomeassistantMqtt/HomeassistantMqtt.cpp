#include "HomeassistantMqtt.h"


MQTTBASE::MQTTBASE(void ) {
		
		settings.Client_Name = "ESP";
		//settings.Client_Type = "Sensor";
		//settings.mqtt_Topic = "/Home/";
}
	
uint8_t MQTTBASE::begin()
{
	WiFi.begin(wifi_ssid, wifi_password);
  //
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.println(".");
	}
	Serial.println("");
	Serial.println(F("WiFi connected"));
	Serial.println(F("IP address: "));
	Serial.println(WiFi.localIP().toString());


	
}

String MQTTBASE::macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}
