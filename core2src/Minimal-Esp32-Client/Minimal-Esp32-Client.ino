/*
	Minimal Esp32 Websockets Client

	This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello Server")
        4. Sends the websocket server a "ping"
        5. Prints all incoming messages while the connection is open

    NOTE:
    The sketch dosen't check or indicate about errors while connecting to 
    WiFi or to the websockets server. For full example you might want 
    to try the example named "Esp32-Client".

	Hardware:
        For this sketch you only need an ESP8266 board.

	Created 15/02/2019
	By Gil Maimon
	https://github.com/gilmaimon/ArduinoWebsockets

*/

#include <ArduinoWebsockets.h>
#include <WiFi.h>

const char* ssid = "TP-LINK_BC5B"; //Enter SSID
const char* password = "kcsyyds."; //Enter Password
const char* websockets_server_host = "192.168.1.106"; //Enter server adress
const uint16_t websockets_server_port = 8080; // Enter server port

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
    Serial.print("\nConnecting to WiFi:");
    Serial.print(ssid);
    // Connect to wifi
    WiFi.begin(ssid, password);
    
    // Wait some time to connect to wifi
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.print("\nConnected to Wifi\n");
    
    // run callback when messages are received
    client.onMessage(onMessageCallback);
    
    // run callback when events are occuring
    client.onEvent(onEventsCallback);
//    while(1){
//       client.connect(websockets_server_host, websockets_server_port, "/");
//
//    // Send a message
//    client.send("Hello Server");
//    
//      delay(1000);
//          Serial.print("trying\n");
//      }
    // Connect to server
    client.connect(websockets_server_host, websockets_server_port, "/");

    // Send a message
    client.send("Hello Server");

    // Send a ping
    client.ping();
}

void loop() {
    client.poll();
}
