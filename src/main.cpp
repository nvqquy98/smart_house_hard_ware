#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Firebase_ESP_Client.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <addons/TokenHelper.h>
/* model */

#include <model/device_status.h>
#include <model/device_data.h>
#include <device_manager.h>

/* config Wifi */
// const char *ssid = "nvqquy98";
// const char *password = "qwertyuio";

// IPAddress local_IP(172, 20, 10, 12);
// IPAddress gateway(172, 20, 10, 1);
// IPAddress subnet(255, 255, 255, 240);
// IPAddress primaryDNS(8, 8, 8, 8);   // optional
// IPAddress secondaryDNS(8, 8, 4, 4); // optiona

const char *ssid = "Room103 2.4Ghz";
const char *password = "khongcopass";
IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional
ESP8266WebServer server(8080);      // Server on port 80

/* define Firebase */
#define API_KEY "AIzaSyA5rI5E-vWlwna6jN_C9Xju2xM7xLe27tQ"
#define FIREBASE_PROJECT_ID "smart-house-vq"

// #define USER_EMAIL "temp02@gmail.com"
// #define USER_PASSWORD "Aa@123456"
#define USER_EMAIL "temp03@gmail.com"
#define USER_PASSWORD "123456"
#define LED1pin D4
#define LED2pin D3
const String USER_UID = "imy0ARx0llgLakOdINlZzHw8Drs1";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
DeviceManager deviceManager;

unsigned long dataMillis = 0;
int count = 0;
bool turnOnLed = LOW;
bool turnOnSOS = LOW;
int btn = 0;
char state;
int input[5] = {D1, D2, D3, D4, D5};
int output[5] = {D6, D7, D8, D9, D10};

//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
// Route Api
void addApi();
void initDevices();
void createNewStatus();
void handleNotFound();
void createDevice();
String SendHTML(uint8_t led1stat, uint8_t led2stat);

//===============================================================
//                  SETUP
//===============================================================
void setup()
{
  for (int i = 0; i < 5; i++)
  {
    pinMode(output[i], OUTPUT);
    pinMode(input[i], INPUT_PULLUP);
  }
  digitalWrite(LED1pin, LOW);
  digitalWrite(LED2pin, LOW);
  Serial.begin(9600);
  Serial.println("");
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.begin(ssid, password); // Only Access point
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println('\n');
  Serial.print("Connected IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
  /* setup HTTP Request */
  addApi();
  server.onNotFound(handleNotFound);
  delay(2000);
  server.begin(); // Start server
  Serial.println("HTTP server started");

  /* setup firebase */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
  fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);
  timeClient.begin();
  timeClient.setTimeOffset(7);
}

//===============================================================
//                     LOOP
//===============================================================

void setupPin();

void loop(void)
{
  server.handleClient(); // Handle client requests
  setupPin();
}

void addApi()
{
  server.on("/devices_info", HTTP_POST, initDevices); // Which routine to handle at root location
  server.on("/status", HTTP_POST, createNewStatus);
  server.on("/devices", HTTP_POST, createDevice);
}

void handleNotFound()
{
  server.send(404, "text/plain", "{\"error\" :\"NotFound\"})");
}

void initDevices()
{
  if (server.hasArg("plain"))
  {
    deviceManager.initDevices(server.arg("plain"));
    server.send(200, "text/json", "{\"data\" : \"success\"}");
    return;
  }
  server.send(400, "text/json", "{\"error\" : \"NOT_FOUND\"}");
}

void setupPin()
{
  for (int i = 0; i < 5; i++)
  {
    if (digitalRead(input[i]) == false)
    {
      // turn LED on:
      while (digitalRead(input[i]) == false)
      {
        delay(50);
      }
      digitalWrite(output[i], !digitalRead(output[i]));
      DeviceData deviceData = deviceManager.getDevice(output[i]);
      DeviceStatusData deviceStatusData = DeviceStatusData(deviceData.id, digitalRead(output[i]), output[i], deviceData.deviceType);
      if (deviceStatusData.createDeviceStatusDataFirebase(USER_UID, fbdo, FIREBASE_PROJECT_ID))
      {
        Serial.print("create success!");
      }
      else
      {
        Serial.print(fbdo.errorReason());
      }
    }
  }
}

void createNewStatus()
{
  timeClient.update();
  if (server.hasArg("plain"))
  {
    DeviceData deviceData = DeviceData::mapFromJson(server.arg("plain"));
    DeviceStatusData deviceStatus = DeviceStatusData(deviceData.id, deviceData.isTurnOn, deviceData.pinOutput, deviceData.deviceType);
    deviceStatus.createAt = timeClient.getEpochTime();
    digitalWrite(deviceStatus.pinOutput, deviceStatus.isTurnOn);
    if (deviceStatus.createDeviceStatusDataFirebase(USER_UID, fbdo, FIREBASE_PROJECT_ID))
    {
      digitalWrite(deviceStatus.pinOutput, deviceStatus.isTurnOn);
      server.send(200, "text/json", "{\"data\":" + deviceStatus.mapToJson() + "}");
    }
    else
    {
      digitalWrite(deviceStatus.pinOutput, !deviceStatus.isTurnOn);
      server.send(400, "text/json", "{\"error\":\"" + fbdo.errorReason() + "\"}");
    }
  }
}

void createDevice()
{
  timeClient.update();
  if (server.hasArg("plain"))
  {
    DeviceData deviceData = DeviceData::mapFromJson(server.arg("plain"));
    if (deviceData.createDeviceFirebase(USER_UID, fbdo, FIREBASE_PROJECT_ID))
    {
      server.send(200, "text/json", "{\"data\":" + deviceData.mapToJson() + "}");
    }
    else
    {
      server.send(400, "text/json", "{\"error\":\"" + fbdo.errorReason() + "\"}");
    };
  }
}