

#include "User_config.h"

#include <PubSubClient.h>

uint8_t GPIO_Taste = 2;
//adding this to bypass the problem of the arduino builder issue 50
void callback(char*topic, byte* payload,unsigned int length);

MQTTBASE baseclient;

// client parameters
PubSubClient client(mqtt_server, mqtt_port, callback, baseclient.eClient);

//MQTT last attemps reconnection date
unsigned long lastReconnectAttempt = 0;
static int contador=0;
boolean tmpE2=false; 

 
boolean reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    trc(F("MQTT connection...")); //F function enable to decrease sram usage
    #ifdef mqtt_user
      if (client.connect(mqtt_Client_Name, mqtt_user, mqtt_password, will_Topic, will_QoS, will_Retain, will_Message)) { // if an mqtt user is defined we connect to the broker with authentication
    #else
      if (client.connect(mqtt_Client_Name, will_Topic, will_QoS, will_Retain, will_Message)) {
    #endif
      trc(F("Connected to broker"));
      // Once connected, publish an announcement...
      client.publish(will_Topic,Gateway_AnnouncementMsg,will_Retain);
      // publish version
      client.publish(version_Topic,ESP_VERSION,will_Retain);
      //Subscribing to topic
      if (client.publish(trace_Topic, "Start")) {
       trc("publish " subjectXtoMqtt "ok");
      } else {
       trc("publish " subjectXtoMqtt "fail");
      }
    } else {
      trc(F("mqtt connect fail"));
      trc(F("failed, rc="));
      trc(String(client.state()));
      trc(F("try again in 5s"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
   
  }
    contador++;
    String payload2="";
    payload2 = contador;
    client.publish(count_Topic,(char*)payload2.c_str());

  return client.connected();
}


void callback(char* topic, byte* payload, unsigned int len) {

  
}

void setup() {
  //
   baseclient.settings.Client_Version =ESP_VERSION;
   baseclient.settings.Client_Name =ESP_Name;
   baseclient.settings.Client_Type =ESP_Funktion;


  Serial.begin(SERIAL_BAUD);
  //
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(GPIO_Taste, INPUT_PULLUP);
  
    // Port defaults to 8266
    ArduinoOTA.setPort(ota_port);

    // Hostname defaults to esp8266-[ChipID]
    ArduinoOTA.setHostname(ESP_Name);

    // No authentication by default
    ArduinoOTA.setPassword(ota_password);

    ArduinoOTA.onStart([]() {
      trc(F("Start"));
    });
    ArduinoOTA.onEnd([]() {
      trc(F("\nEnd"));
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) trc(F("Auth Failed"));
      else if (error == OTA_BEGIN_ERROR) trc(F("Begin Failed"));
      else if (error == OTA_CONNECT_ERROR) trc(F("Connect Failed"));
      else if (error == OTA_RECEIVE_ERROR) trc(F("Receive Failed"));
      else if (error == OTA_END_ERROR) trc(F("End Failed"));
    });
    ArduinoOTA.begin();
    if (digitalRead(GPIO_Taste) == LOW){
      client.publish(subjectXtoMqtt, "ON");
    } else {
      client.publish(subjectXtoMqtt, "OFF");
    }

}

void loop()
{ ArduinoOTA.handle();
  unsigned long now = millis();
  String str;
  char b[2]; 
  str=String(digitalRead(GPIO_Taste));
  str.toCharArray(b,2);  
  //MQTT client connexion management
  if (!client.connected()) { // not connected

     trc(F("Rot An"));
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else { 

    
    client.loop();
    ArduinoOTA.handle();
    if (digitalRead(GPIO_Taste) == LOW) 
      if (tmpE2 == true) {
         client.publish(subjectXtoMqtt, "ON");
         tmpE2 = false;
      }
    if (digitalRead(GPIO_Taste) == HIGH)
      if (tmpE2 == false) {
        client.publish(subjectXtoMqtt, "OFF");
        tmpE2 = true;
        }

  }
  digitalWrite(LED_BUILTIN, digitalRead(GPIO_Taste));
}
//trace
void trc(String msg){
  if (TRACE) {
    Serial.println(msg);
  } else {
  client.publish(trace_Topic,(char*)msg.c_str());
  }
 } 




