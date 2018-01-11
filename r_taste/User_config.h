#include <HomeassistantMqtt.h>

#define SERIAL_BAUD 115200

/*-------------------VERSION----------------------*/
#define ESP_VERSION "1"
#define ESP_Name "R_Taste"
#define ESP_Funktion "switch"

/*-------------DEFINE YOUR NETWORK PARAMETERS BELOW----------------*/
//MQTT Parameters definition
#define mqtt_Client_Name ESP_Name
#define mqtt_Topic mqtt_Home ESP_Funktion mqtt_Back mqtt_Client_Name mqtt_Back
#define version_Topic mqtt_Topic "version"
#define will_Topic mqtt_Topic "LWT"
#define trace_Topic mqtt_Topic "Trace"
#define count_Topic mqtt_Topic "Count"
#define will_QoS 0
#define will_Retain true
#define will_Message "Offline"
#define Gateway_AnnouncementMsg "Online"
#define mqtt_Home "/home/"
#define mqtt_Back "/"



  

/*--------------MQTT general topics-----------------*/
// global MQTT subject listened by the gateway to execute commands (send RF, IR or others)
#define subjectXtoMqtt mqtt_Topic "taste" 




/*-------------------ACTIVATE TRACES----------------------*/
#define TRACE 0  // 0= trace off 1 = trace on

