

#ifndef PUSHER_H_
#define PUSHER_H_

class Pusher {

    public:
        Pusher(void);
        bool connect(String app_key);
        bool connect(String app_key, String cluster);
        void subscribe(String channel);
        
    private:
        WSclient_t _client;
        void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
        
};

#endif /* PUSHER_H_ */
