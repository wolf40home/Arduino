#include "secrets.h"
/*-------------------VERSION----------------------*/
#define ESP01_VERSION "0.2"

/*-------------DEFINE YOUR NETWORK PARAMETERS BELOW----------------*/
//MQTT Parameters definition
#define Client_Name "R_Taste"
#define mqtt_Topic "/home/switch/"
#define version_Topic mqtt_Topic Client_Name "/version"
#define will_Topic mqtt_Topic Client_Name "/LWT"
#define will_QoS 0
#define will_Retain true
#define will_Message "Offline"
#define Gateway_AnnouncementMsg "Online"


#define E2 2
#define SERIAL_BAUD 115200
  

/*--------------MQTT general topics-----------------*/
// global MQTT subject listened by the gateway to execute commands (send RF, IR or others)
#define subjectXtoMqtt mqtt_Topic Client_Name "/taste" 

/*-------------DEFINE YOUR OTA PARAMETERS BELOW----------------*/
#define ota_hostname Client_Name

/*-------------------ACTIVATE TRACES----------------------*/
#define TRACE 0  // 0= trace off 1 = trace on
