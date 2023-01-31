#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <HardwareSerial.h>

#define MCU3_MCU1_UART_BAUDRATE 115200
#define MCU3_MCU2_UART_BAUDRATE 115200
#define SERIAL_BAUDRATE         115200

#define BUFFER_SIZE 100

#define MCU3_MCU1_UART_RX_PIN 9
#define MCU3_MCU1_UART_TX_PIN 10

#define MCU3_MCU2_UART_RX_PIN 16
#define MCU3_MCU2_UART_TX_PIN 17

#define LED_STATUS_PIN  13

const char* ssid = "RMFamily";
const char* password = "1957288451";

HardwareSerial UART_MCU3_MCU2(2);
HardwareSerial UART_MCU3_MCU1(1);

void Setup_GPIOs()
{
  pinMode(LED_STATUS_PIN, OUTPUT);
}

void setup() {
  
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
   ArduinoOTA.setHostname("RastoBot");

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

  Serial.print("Starting UARTs... ");
  UART_MCU3_MCU2.begin(MCU3_MCU2_UART_BAUDRATE, SERIAL_8N1, MCU3_MCU2_UART_RX_PIN, MCU3_MCU2_UART_TX_PIN);
  //UART_MCU3_MCU1.begin(MCU3_MCU1_UART_BAUDRATE, SERIAL_8N1, MCU3_MCU1_UART_RX_PIN, MCU3_MCU1_UART_TX_PIN);
  Serial.print("Finished!\n");
  Setup_GPIOs();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(1);
  ArduinoOTA.handle();
  LED_Blink();
  //MCU2_RX_handler();
  //MCU1_RX_handler();
}

uint32_t ledBlinkCounter = 0;
bool ledStatus = false;
void LED_Blink()
{
  if (ledBlinkCounter >= 500) // counter ended
  {
    if (!ledStatus) // if led is turned off then turn it on
    {
      digitalWrite(LED_STATUS_PIN, HIGH);
      ledStatus = true;
    }
    else // led is turned on so turn it off
    {
      digitalWrite(LED_STATUS_PIN, LOW);
      ledStatus = false;
    }
    ledBlinkCounter = 0; // reset counter
  }
  else
  {
    ledBlinkCounter++; // increment counter
  }
}

void MCU1_TX(uint8_t msg, uint16_t len)
{
  UART_MCU3_MCU1.write(&msg, len);
}
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
      Serial.print("MCU2 RX:");
    }
    uint8_t receivedByte = UART_MCU3_MCU2.read();
    Serial.write(&receivedByte, 1);
    bytesCounter++;
  }
  if (bytesCounter > 0)
  {
    Serial.println("MCU1 bytes received: " + bytesCounter);
  }
}
void MCU1_RX_handler()
{
  uint16_t bytesCounter = 0;
  // read UART buffer
  while (UART_MCU3_MCU1.available() > 0)
  {
    if (bytesCounter == 0)
    {
      Serial.print("MCU1 RX:");
    }
    uint8_t receivedByte = UART_MCU3_MCU1.read();
    Serial.write(&receivedByte, 1);
    bytesCounter++;
  }
  if (bytesCounter > 0)
  {
    Serial.println("MCU1 bytes received: " + bytesCounter);
  }
}
