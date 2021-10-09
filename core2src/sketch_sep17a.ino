#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <M5Core2.h>

//const char* ssid = "115_GeekTech_5G"; //Enter SSID
const char* ssid = "TP-Link_BC5B"; //Enter SSID
//const char* password = "202011021635_XD"; //Enter Password
const char* password = "kcsyyds."; //Enter Password
const char* websockets_server = "10.181.92.9:8080"; //server adress and port

using namespace websockets;

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

WebsocketsClient client;
void setup() {
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);
    M5.begin();
    // Wait some time to connect to wifi
    M5.Lcd.print("Initialization Done");
    while(WiFi.status() != WL_CONNECTED){
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
      Serial.println(".");
        M5.Lcd.print(".");
        delay(1000);
    }
    
    if(WiFi.status() == WL_CONNECTED) M5.Lcd.print("\nWiFi ok");
    else M5.Lcd.print("\nWiFi Retry");
    }
    // Setup Callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    
    // Connect to server
    client.connect(websockets_server);

    // Send a message
    client.send("Hi Server!");
    // Send a ping
    client.ping();
}

void loop() {
    client.poll();
}
