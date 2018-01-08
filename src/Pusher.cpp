
#include "Pusher.h"

Pusher::Pusher() { 
}

String Pusher::subscribeJsonString(char * channel) {
	String json = "{\"event\":\"pusher:subscribe\",\"data\": {\"channel\": \"_C_\"}}";

	json.replace(String("_C_"), String(channel));
	
	/*
	char buf[127];
	strcpy(buf, json.c_str());
	//json.toCharArray(buf, json.length()+1);
	return buf;
	*/
	return json;
}
