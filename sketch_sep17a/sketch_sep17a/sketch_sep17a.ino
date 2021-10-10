#include <WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "TP-LINK_BC5C";
const char* password = "kcsyyds.";
char path[] = "/echo";
char host[] = "192.168.89.35:8080";

WebSocketClient webSocketClient;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(5000);
  if (client.connect(host, 80)) { //调用WiFiClient对象的connect方法与主机建立TCP连接
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }
  webSocketClient.path = path;  //为WebSocketClient的路径分配全局变量
 
  webSocketClient.host = host;  // 为WebSocketClient的主机数据分配全局变量
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }
}
void loop() {
  String data;
  if (client.connected()) {
    webSocketClient.sendData("Info to be echoed back"); // 发送数据到服务器
    webSocketClient.getData(data);  // 从服务器接收数据
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
  } else {
    Serial.println("Client disconnected.");
  }
  delay(3000);
}
现象
