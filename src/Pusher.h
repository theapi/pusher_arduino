

#ifndef PUSHER_H_
#define PUSHER_H_

#include <Arduino.h>

class Pusher {

    public:
        Pusher();
        String subscribeJsonString(char * channel);
        
        
};

#endif /* PUSHER_H_ */
