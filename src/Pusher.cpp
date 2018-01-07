
#include "Pusher.h"

Pusher::Pusher() { 
  //_client.onEvent(Pusher::webSocketEvent);
}

bool Pusher::connect(String app_key, String cluster) {
	
}

bool Pusher::connect(String app_key, String cluster, const char *host, const char *path) {
	WebSocketsClient _client;
	
	_client.begin(host, 80, path);

	// websocket event handler
	_client.onEvent(Pusher::webSocketEvent);

	// try ever 5000 again if connection has failed
	_client.setReconnectInterval(5000);
}


 void Pusher::webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

	switch(type) {
		case WStype_DISCONNECTED:
			Serial.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED: {
			Serial.printf("[WSc] Connected to url: %s\n", payload);

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

     // webSocket.sendTXT("{\"event\":\"pusher:subscribe\",\"data\": {\"channel\": \"my-channel\"}}");

     
		}
			break;
		case WStype_TEXT:
			Serial.printf("[WSc] got text: %s\n", payload);

      //onEvent(payload);



			break;
		case WStype_BIN:
			Serial.printf("[WSc] get binary length: %u\n", length);
			//hexdump(payload, length);

			// send data to server
			// webSocket.sendBIN(payload, length);
			break;
	}

}

void Pusher::loop() {
	_client.loop();
}

