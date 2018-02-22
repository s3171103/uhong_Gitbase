#include <ESP8266WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <ESP8266WebServer.h>  // 提供網站伺服器功能的程式庫
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const char ssid[] = "hemuhemu";
const char pass[] = "0952474239s";

String content= "";

ESP8266WebServer server(80);   // 宣告網站伺服器物件與埠號

// 定義處理首頁請求的自訂函式
void rootRouter() {
  server.send(200, "text/html", content.substring(1));   //網頁的html 在此(紅色字體可做修改)
  
}

void setup() {
  Serial.begin(115200);  
  WiFi.begin(ssid, pass);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  /*
   *  若要指定IP位址，請自行在此加入WiFi.config()敘述。
   WiFi.config(IPAddress(192,168,1,50),    // IP位址
               IPAddress(192,168,1,1),     // 閘道（gateway）位址
               IPAddress(255,255,255,0));  // 網路遮罩（netmask）
   */

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   // 等待WiFi連線
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());  // 顯示ESP8266裝置的IP位址

  server.on("/index.html", rootRouter);  // 處理首頁連結請求的事件
  server.on("/", rootRouter);
  
  server.onNotFound([](){   // 處理「找不到指定路徑」的事件
    server.send(404, "text/plain", "File NOT found!");
  });
  
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
    server.handleClient();  // 處理用戶連線
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  
  byte letter;
  content = " ";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
}
