
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>
#include <Pusher.h>
#include "config.h"

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
Pusher pusher;


#define USE_SERIAL Serial



void setup() {

    USE_SERIAL.begin(115200);

  //Serial.setDebugOutput(true);
  USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

//  for(uint8_t t = 4; t > 0; t--) {
//    USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
//    USE_SERIAL.flush();
//    delay(1000);
//  }

  WiFiMulti.addAP(WIFI_SID, WIFI_PASWORD);

  //WiFi.disconnect();
  while(WiFiMulti.run() != WL_CONNECTED) {
    USE_SERIAL.print(".");
    delay(200);
  }

  pusher.connect(String(PUSHER_KEY), String("eu"), PUSHER_HOST, PUSHER_PATH);

}

void loop() {

  pusher.loop();

}
