
/*
 * WebSocketClient.ino
 *
 */

#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>
#include <Pusher.h>

#include "config.h"

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
Pusher pusher;


#define JSON_BUFFER_SIZE 1024

void onPusherConnectionEstablished(const char* data) {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& jsonObj = jsonBuffer.parseObject(data);

  if (jsonObj.success()) {
    const char* activity_timeout = jsonObj["activity_timeout"];
    webSocket.setReconnectInterval(atoi(activity_timeout) * 1000);

    // Subscribe to the initial channel.
    String json = pusher.subscribeJsonString("my-channel");
    webSocket.sendTXT(json);
  }
}

void onMyEvent(const char* data) {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& jsonObj = jsonBuffer.parseObject(data);

  if (jsonObj.success()) {
    const char* name = jsonObj["name"];
    Serial.print("name: "); Serial.println(name);
  }
}

void handlePusherEvent(uint8_t * payload) {

  // Create the temporary buffer for parsing the json.
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  // Parse the json string.
  JsonObject& jsonObj = jsonBuffer.parseObject(payload);
  if (!jsonObj.success()) {
    return; 
  }
  
  // Get the pusher event name.
  const char* event = jsonObj["event"];
  const char* data = jsonObj["data"];
  Serial.print("Event: "); Serial.println(event);

  // Event subscribers (poor man's event dispatcher).
  if (strcmp(event, "pusher:connection_established") == 0) {
    onPusherConnectionEstablished(data);
  }
  else if (strcmp(event, "my-event") == 0) {
    onMyEvent(data);
  }
    
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload); 
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] got text: %s\n", payload);
      handlePusherEvent(payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  Serial.setDebugOutput(true);

  Serial.println();

  WiFiMulti.addAP(WIFI_SID, WIFI_PASWORD);
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }

  // server address, port and URL
  webSocket.begin(PUSHER_HOST, 80, PUSHER_PATH);

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

}

void loop() {
  webSocket.loop();
}

