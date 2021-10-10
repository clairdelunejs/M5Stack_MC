#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <M5Core2.h>

//const char* ssid = "115_GeekTech_5G"; //Enter SSID
//const char* ssid = "TP-LINK_BC5B"; //Enter SSID
const char* ssid = "Segmention_Fault";
//const char* password = "202011021635_XD"; //Enter Password
//const char* password = "kcsyyds."; //Enter Password
const char* password = "123456789";
const char* websockets_server = "192.168.220.35:8080"; //server adress and port
//
//
//HardwareSerial serial_ext(2);
//
//typedef struct {
//  uint32_t length;
//  uint8_t *buf;
//} jpeg_data_t;
//
//jpeg_data_t jpeg_data;
//static const int RX_BUF_SIZE = 20000;
//static const uint8_t packet_begin[3] = { 0xFF, 0xD8, 0xEA };
//

using namespace websockets;

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    M5.Lcd.print("Got Message:");
    Serial.println(message.data());
    M5.Lcd.print(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
//        M5.Lcd.print("\nConnnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
        M5.Lcd.print("\nConnnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
//        M5.Lcd.print("\nGot a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
//        M5.Lcd.print("\nGot a Pong!");
    }
    else{Serial.println("w");}
}


WebsocketsClient client;
void setup() {
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);
    M5.begin();
    // Wait some time to connect to wifi
//    M5.Lcd.print("Initialization Done");
    while(WiFi.status() != WL_CONNECTED){
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
//      Serial.println(".");
        M5.Lcd.print(".");
        delay(1000);
    }
    
      if(WiFi.status() != WL_CONNECTED) 
      {M5.Lcd.print("\nWiFi Retry");WiFi.begin(ssid, password);}
    }
    // Setup Callbacks
    M5.Lcd.print("\nWiFi Connected!");
    Serial.println("WiFi Connected!");
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    M5.Lcd.print("\nCallbacks Yes");
    Serial.println("Callbacks Yes");
    // Connect to server
    client.connect(websockets_server);
    // Send a message
    client.send("Hi Server!");
    // Send a ping
    client.ping();
}

void loop() {
    client.poll();
//    Serial.println("Callbacks Yes");  
}
