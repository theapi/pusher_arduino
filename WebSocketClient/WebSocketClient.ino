/*
 * WebSocketClient.ino
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>

#include "config.h"

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

#define USE_SERIAL Serial

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

	switch(type) {
		case WStype_DISCONNECTED:
			USE_SERIAL.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED: {
			USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);

			// Subscribe to a channel
     /*
      * 
{
  "event": "pusher:subscribe",
  "data": {
    "channel": String,
    "auth": String,
    "channel_data": String
  }
}
      */

      webSocket.sendTXT("{\"event\":\"pusher:subscribe\",\"data\": {\"channel\": \"my-channel\"}}");

     
		}
			break;
		case WStype_TEXT:
			USE_SERIAL.printf("[WSc] get text: %s\n", payload);

			// send message to server
			// webSocket.sendTXT("message here");
			break;
		case WStype_BIN:
			USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
			//hexdump(payload, length);

			// send data to server
			// webSocket.sendBIN(payload, length);
			break;
	}

}

void setup() {
	// USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);

	//Serial.setDebugOutput(true);
	USE_SERIAL.setDebugOutput(true);

	USE_SERIAL.println();
	USE_SERIAL.println();
	USE_SERIAL.println();

//	for(uint8_t t = 4; t > 0; t--) {
//		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
//		USE_SERIAL.flush();
//		delay(1000);
//	}

	WiFiMulti.addAP(WIFI_SID, WIFI_PASWORD);

	//WiFi.disconnect();
	while(WiFiMulti.run() != WL_CONNECTED) {
    USE_SERIAL.print(".");
		delay(100);
	}

	// server address, port and URL
	//webSocket.begin("192.168.0.34", 81, "/");
  webSocket.begin(PUSHER_HOST, 80, PUSHER_PATH);

	// event handler
	webSocket.onEvent(webSocketEvent);

	// try ever 5000 again if connection has failed
	webSocket.setReconnectInterval(5000);

}

void loop() {
	webSocket.loop();
}
