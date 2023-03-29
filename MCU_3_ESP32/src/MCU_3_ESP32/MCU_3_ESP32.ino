#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HardwareSerial.h>
#include "libs/RastoBot.h"
#include "libs/ermaCommProtocol.h"
#include "webpages.h"
typedef enum {WIFI_MODE_CLIENT, WIFI_MODE_SERVER} WifiMode;

/* WIFI MODE SETTINGS **************************************/
WifiMode WIFI_MODE = WIFI_MODE_SERVER;
/**********************************************************/
/* WIFI CONNECT TO SETTINGS ********************************/
const char* client_ssid = "RMFamily";
const char* client_password = "1957288451";
/**********************************************************/

/* WEBSERVER SETTINGS *************************************/
/* Put your SSID & Password */
const char* hostname = "RastoBot";  // Enter SSID here
const char* server_ssid = "RastoBot";  // Enter SSID here
const char* server_password = "12345678";  //Enter Password here
/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
WebServer server(80);
//AsyncWebServer server(80);
/*******************************************************/
/*LEDS *************************************************/
#define LED_B_PIN 15
#define LED_G_PIN 2
#define LED_R_PIN 4
#define LED_STATUS_PIN  13
/* UARTS SETTINGS *************************************/
#define MCU3_MCU1_UART_BAUDRATE 115200
#define MCU3_MCU2_UART_BAUDRATE 256000
#define SERIAL_BAUDRATE         256000

#define BUFFER_SIZE 100

#define MCU3_MCU1_UART_RX_PIN 9
#define MCU3_MCU1_UART_TX_PIN 10

#define MCU3_MCU2_UART_RX_PIN 16
#define MCU3_MCU2_UART_TX_PIN 17
HardwareSerial UART_MCU3_MCU2(2);
//HardwareSerial UART_MCU3_MCU1(1);
/*******************************************************/

/* LCD SETTINGS *************************************/
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
/*******************************************************/
/*******************************************************/
void Setup_GPIOs()
{
  pinMode(LED_STATUS_PIN, OUTPUT);
}
uint32_t loopCounter = 0;
void setup() {
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_R_PIN, OUTPUT);
  digitalWrite(LED_G_PIN, HIGH);
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Booting...");
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  if (WIFI_MODE == WIFI_MODE_CLIENT)  // client
  {
    WiFi_StartClient();
    OTA_StartClient();
  }
  else if (WIFI_MODE == WIFI_MODE_SERVER) // server
  {
    Webserver_Start();
  }
  
  Serial.print("Starting UARTs... ");
  UART_MCU3_MCU2.begin(MCU3_MCU2_UART_BAUDRATE, SERIAL_8N1, MCU3_MCU2_UART_RX_PIN, MCU3_MCU2_UART_TX_PIN);
  //UART_MCU3_MCU1.begin(MCU3_MCU1_UART_BAUDRATE, SERIAL_8N1, MCU3_MCU1_UART_RX_PIN, MCU3_MCU1_UART_TX_PIN);
  Serial.print("UARTs started.\n");
  Setup_GPIOs();
  Display_PrintText("RastoBot", "Bakalarska praca", " by Rastislav Oravec", "");
  Serial.print("RastoBot is ready!\n");
}

void loop() {
  loopCounter++;
  //delay(1);
  if (WIFI_MODE == WIFI_MODE_CLIENT)
    ArduinoOTA.handle();
  else if (WIFI_MODE == WIFI_MODE_SERVER)
    Webserver_Loop();
  BoardLED_Blink();
  GLED_Blink();
  MCU2_RX_handler();
  EXT_RX_handler();
  //MCU1_RX_handler();
}

uint32_t boardLedBlinkCounter = 0;
bool boardLedStatus = false;
void BoardLED_Blink()
{
  if (boardLedBlinkCounter >= 1000) // counter ended
  {
    if (!boardLedStatus) // if led is turned off then turn it on
    {
      digitalWrite(LED_STATUS_PIN, HIGH);
      boardLedStatus = true;
    }
    else // led is turned on so turn it off
    {
      digitalWrite(LED_STATUS_PIN, LOW);
      boardLedStatus = false;
    }
    boardLedBlinkCounter = 0; // reset counter
  }
  else
  {
    boardLedBlinkCounter++; // increment counter
  }
}
uint32_t GLedBlinkCounter = 0;
bool GLedStatus = false;
void GLED_Blink()
{
  if (GLedBlinkCounter >= 1000) // counter ended
  {
    if (!GLedStatus) // if led is turned off then turn it on
    {
      digitalWrite(LED_G_PIN, HIGH);
      GLedStatus = true;
    }
    else // led is turned on so turn it off
    {
      digitalWrite(LED_G_PIN, LOW);
      GLedStatus = false;
    }
    GLedBlinkCounter = 0; // reset counter
  }
  else
  {
    GLedBlinkCounter++; // increment counter
  }
}
uint32_t RLedBlinkCounter = 0;
bool RLedStatus = false;
void RLED_Toggle()
{
  //if (RLedBlinkCounter >= 1000) // counter ended
  //{
    if (!RLedStatus) // if led is turned off then turn it on
    {
      digitalWrite(LED_R_PIN, HIGH);
      RLedStatus = true;
    }
    else // led is turned on so turn it off
    {
      digitalWrite(LED_R_PIN, LOW);
      RLedStatus = false;
    }
    RLedBlinkCounter = 0; // reset counter
  //}
  //else
  //{
  //  RLedBlinkCounter++; // increment counter
  //}
}
uint32_t BLedBlinkCounter = 0;
bool BLedStatus = false;
void BLED_Toggle()
{
  //if (BLedBlinkCounter >= 1000) // counter ended
  //{
    if (!BLedStatus) // if led is turned off then turn it on
    {
      digitalWrite(LED_B_PIN, HIGH);
      BLedStatus = true;
    }
    else // led is turned on so turn it off
    {
      digitalWrite(LED_B_PIN, LOW);
      BLedStatus = false;
    }
    BLedBlinkCounter = 0; // reset counter
  //}
  //else
  //{
  //  BLedBlinkCounter++; // increment counter
  //}
}

//void MCU1_TX(uint8_t msg, uint16_t len)
//{
//  UART_MCU3_MCU1.write(&msg, len);
//}
void MCU2_TX(uint8_t msg, uint16_t len)
{
  UART_MCU3_MCU2.write(&msg, len);
}

void MCU2_RX_handler()
{
  uint16_t bytesCounter = 0;
  // read UART buffer
  while (UART_MCU3_MCU2.available() > 0)
  {
    if (bytesCounter == 0)
    {
      //Serial.print("MCU2 RX:");
    }
    uint8_t receivedByte = UART_MCU3_MCU2.read();
    Serial.write(receivedByte);
    //Serial.print(String(receivedByte) + " ");
    bytesCounter++;
  }
  if (bytesCounter > 0)
  {
    BLED_Toggle();
    //Serial.println("");
    //Serial.println("MCU2 bytes received: " + bytesCounter);
  }
}
void EXT_RX_handler()
{
  uint16_t bytesCounter = 0;
  // read UART buffer
  while (Serial.available() > 0)
  {
    if (bytesCounter == 0)
    {
      //Serial.print("EXT RX:");
    }
    uint8_t receivedByte = Serial.read();
    UART_MCU3_MCU2.write(receivedByte);
    //Serial.print(String(receivedByte) + " ");
    bytesCounter++;
  }
  if (bytesCounter > 0)
  {
    RLED_Toggle();
    //Serial.println("");
    //Serial.println("EXT bytes received: " + bytesCounter);
  }
}

void Display_PrintText(char * line1, char * line2, char * line3, char * line4)
{
  Display_Clear();
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
  lcd.setCursor(0,2);
  lcd.print(line3);
  lcd.setCursor(0,3);
  lcd.print(line4);
}

void Display_Clear()
{
  lcd.clear(); 
}


/************************************************************/
void WiFi_StartClient()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(client_ssid, client_password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("WiFi client ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void OTA_StartClient()
{
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
   ArduinoOTA.setHostname(hostname);

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
}

void Webserver_Start()
{
  WiFi.softAP(server_ssid, server_password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(500);
  //MDNS_Start();
  Webserver_Setup();
  server.begin();
  Serial.println("HTTP server started");
}
void Webserver_Loop() {
  server.handleClient();
}

//void handle_OnConnect() {
//  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF");
//  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
//}
//
//void handle_led1on() {
//  LED1status = HIGH;
//  Serial.println("GPIO4 Status: ON");
//  server.send(200, "text/html", SendHTML(true,LED2status)); 
//}
//
//void handle_led1off() {
//  LED1status = LOW;
//  Serial.println("GPIO4 Status: OFF");
//  server.send(200, "text/html", SendHTML(false,LED2status)); 
//}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void MDNS_Start()
{
   /*use mdns for host name resolution*/
  if (!MDNS.begin(hostname)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(100);
    }
  }
  Serial.println("mDNS responder started");
}

void Webserver_Setup()
{
  //server.on("/", handle_OnConnect);
//  server.on("/led1on", handle_led1on);
//  server.on("/led1off", handle_led1off);
//  server.on("/led2on", handle_led2on);
//  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);
  
  /*return index page which is stored in serverIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
}
