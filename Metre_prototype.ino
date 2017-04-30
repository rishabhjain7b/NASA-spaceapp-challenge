
#include "ThingSpeak.h"


//#define USE_WIFI101_SHIELD
//#define USE_ETHERNET_SHIELD

#if defined(ARDUINO_AVR_YUN)
    #include "YunClient.h"
    YunClient client;
#else
  #if defined(USE_WIFI101_SHIELD) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_ARCH_ESP8266)
    // Use WiFi
    #ifdef ARDUINO_ARCH_ESP8266
      #include <ESP8266WiFi.h>
    #else
      #include <SPI.h>
      #include <WiFi101.h>
    #endif
    char ssid[] = "nasa";    //  your network SSID (name) 
    char pass[] = "whatnasa";   // your network password
    int status = WL_IDLE_STATUS;
    WiFiClient  client;
  #elif defined(USE_ETHERNET_SHIELD)
    // Use wired ethernet shield
    #include <SPI.h>
    #include <Ethernet.h>
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    EthernetClient client;
  #endif
#endif

#ifdef ARDUINO_ARCH_AVR
  // On Arduino:  0 - 1023 maps to 0 - 5 volts
  #define VOLTAGE_MAX 5.0
  #define VOLTAGE_MAXCOUNTS 1023.0
#elif ARDUINO_SAMD_MKR1000
  // On MKR1000:  0 - 1023 maps to 0 - 3.3 volts
  #define VOLTAGE_MAX 3.3
  #define VOLTAGE_MAXCOUNTS 1023.0
#elif ARDUINO_SAM_DUE
  // On Due:  0 - 1023 maps to 0 - 3.3 volts
  #define VOLTAGE_MAX 3.3
  #define VOLTAGE_MAXCOUNTS 1023.0  
#elif ARDUINO_ARCH_ESP8266
  // On ESP8266:  0 - 1023 maps to 0 - 1 volts
  #define VOLTAGE_MAX 1.0
  #define VOLTAGE_MAXCOUNTS 1023.0
#endif

/*
  *****************************************************************************************
  **** Visit https://www.thingspeak.com to sign up for a free account and create
  **** a channel.  The video tutorial http://community.thingspeak.com/tutorials/thingspeak-channels/ 
  **** has more information. You need to change this to your channel, and your write API key
  **** IF YOU SHARE YOUR CODE WITH OTHERS, MAKE SURE YOU REMOVE YOUR WRITE API KEY!!
  *****************************************************************************************/
unsigned long myChannelNumber = 210679;
const char * myWriteAPIKey = "KW8P0FHZEUC4N6VD";
const int ledPin =  16;      // the number of the LED pin

// Variables will change :
int ledState = LOW;             // ledState used to set the LED

void setup() {
  
  #ifdef ARDUINO_AVR_YUN
    Bridge.begin();
  #else   
    #if defined(ARDUINO_ARCH_ESP8266) || defined(USE_WIFI101_SHIELD) || defined(ARDUINO_SAMD_MKR1000)
      WiFi.begin(ssid, pass);
    #else
      Ethernet.begin(mac);
    #endif
  #endif
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  ThingSpeak.begin(client);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading 
  // On Uno,Mega,YunArduino:  0 - 1023 maps to 0 - 5 volts
  // On ESP8266:  0 - 1023 maps to 0 - 1 volts
  // On MKR1000,Due: 0 - 4095 maps to 0 - 3.3 volts
  float voltage = sensorValue ;

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  delay(200); // ThingSpeak will only accept updates every 15 seconds.
  
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW && voltage<=20 ) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
}
