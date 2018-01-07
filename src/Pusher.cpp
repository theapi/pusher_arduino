
#include "Pusher.h"

Pusher::Pusher() { 
  _client.onEvent(webSocketEvent);
}

bool Pusher::connect(String app_key, String cluster) {
	
}
