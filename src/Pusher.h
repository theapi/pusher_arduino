

#ifndef PUSHER_H_
#define PUSHER_H_

#include <Arduino.h>
#include <WebSockets.h>
#include <WebSocketsClient.h>

class Pusher {

    public:
        Pusher();
       // bool connect(String app_key);
        bool connect(String app_key, String cluster);
        bool connect(String app_key, String cluster, const char *host, const char *path);
        void loop(void);
        void subscribe(String channel);
        
       static void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
        
    private:
        WebSocketsClient _client;
        
        
};

#endif /* PUSHER_H_ */
