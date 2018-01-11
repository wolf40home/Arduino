#ifndef __HomeassistantMqtt__
#define __HomeassistantMqtt__

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <stdint.h>
#include "secrets.h"


struct MqttSettings
{
  public:
	
  //Main Interface and mode settings
    const char* Client_Version;
    const char* Client_Name;
	const char* Client_Type;
//	char* version_Topic;
//	char* will_Topic;
//	char* trace_Topic;
//	char* count_Topic;
	
//	char* mqtt_Topic;


};

class MQTTBASE
 {
	private:
	
	public:
    MqttSettings settings;
	WiFiClient eClient;
	String macToStr(const uint8_t*);
	/////////////////////////////////////////////////////////////////
	/// Constructor used to create the class.
	/// All parameters have default values.
	MQTTBASE( void );
	uint8_t begin( void );

 };
 
#endif