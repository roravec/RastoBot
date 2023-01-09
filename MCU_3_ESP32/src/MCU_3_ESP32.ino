#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define LED_STATUS_PIN  13

const char* ssid = "RMFamily";
const char* password = "1957288451";

void Setup_GPIOs()
{
  pinMode(LED_STATUS_PIN, OUTPUT);
}

void setup() {
  
  Serial.begin(115200);
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

  Setup_GPIOs();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(1);
  ArduinoOTA.handle();
  LED_Blink();
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