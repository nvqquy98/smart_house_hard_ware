
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// // SSID and Password to your ESP Access Point
// // const char* ssid = "AutoDoor P1";
// // const char* ssid = "AutoDoor P2";
// const char *ssid = "Room103 5Ghz";
// const char *password = "khongcopass";
// IPAddress local_IP(192, 168, 1, 184);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress primaryDNS(8, 8, 8, 8);   // optional
// IPAddress secondaryDNS(8, 8, 4, 4); // optional

// bool doorStatus = LOW;
// int LED1pin = 16;
// int LED2pin = 3;
// int btn = 0;
// char state;
// ESP8266WebServer server(8080); // Server on port 80

// //==============================================================
// //     This rutine is exicuted when you open its IP in browser
// //==============================================================
// void handleRoot()
// {
//   server.send(200, "text/plain", "hello from esp8266!");
// }
// void handle_status();
// void handle_auto();
// void handle_close();
// void handle_open();
// void handle_connect();
// void handle_NotFound();
// String SendHTML(uint8_t led1stat, uint8_t led2stat);

// //===============================================================
// //                  SETUP
// //===============================================================
// void setup(void)
// {
//   pinMode(LED1pin, OUTPUT);
//   pinMode(LED2pin, OUTPUT);
//   pinMode(5, INPUT_PULLUP);
//   pinMode(4, INPUT_PULLUP);
//   pinMode(btn, INPUT_PULLUP);
//   pinMode(2, OUTPUT);
//   Serial.begin(9600);
//   digitalWrite(2, LOW);
//   Serial.println("");
//   // WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);

//   WiFi.begin("Room103 2.4Ghz", "khongcopass"); // Only Access point
//   Serial.print("Access Point \"");
//   int i = 0;
//   while (WiFi.status() != WL_CONNECTED)
//   { // Wait for the Wi-Fi to connect
//     delay(1000);
//     Serial.print(++i);
//     Serial.print(' ');
//   }

//   Serial.println('\n');
//   Serial.println("Connection established!");
//   Serial.print("IP address:\t");
//   Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

//   //  IPAddress myIP = WiFi.softAPIP(); //Get IP address
//   Serial.print("HotSpt IP:");
//   Serial.println(WiFi.softAPIP());
//   ///////////////////////////////////////////////////////////////////////////
//   //   WiFi.begin(ssid, password);
//   //  while (WiFi.status() != WL_CONNECTED) {
//   //    delay(500);
//   //    Serial.print(".");
//   //  }
//   //  // Print local IP address and start web server
//   //  Serial.println("");
//   //  Serial.println("WiFi connected.");
//   //  Serial.println("IP address: ");
//   //  Serial.println(WiFi.localIP());
//   //  /
//   //////////////////////////////////////////////////////////////////////////
//   server.on("/status", handle_status); // Which routine to handle at root location
//   server.on("/auto", handle_auto);
//   server.on("/close", handle_close);
//   server.on("/open", handle_open);
//   server.on("/", handle_connect);
//   server.onNotFound(handle_NotFound);
//   delay(2000);
//   server.begin(); // Start server
//   Serial.println("HTTP server started");
//   digitalWrite(2, HIGH);
// }
// void handle_NotFound()
// {
//   server.send(404, "text/plain", "lacroi :)");
// }
// void handle_status()
// {
//   if (doorStatus)
//     server.send(200, "text/json", "{\"status\": \"open\"}");
//   else
//     server.send(200, "text/json", "{\"status\": \"close\"}");
// }
// void handle_close()
// {
//   doorStatus = LOW;
//   Serial.println("R");
//   server.send(200, "text/json", "{\"status\": \"CloseOk\"}");
// }
// void handle_open()
// {
//   doorStatus = HIGH;
//   Serial.println("L");
//   server.send(200, "text/json", "{\"status\": \"OpenOk\"}");
// }
// void handle_connect()
// {
//   doorStatus = HIGH;
//   Serial.println("M");
//   server.send(200, "text/html", SendHTML(doorStatus, doorStatus));
// }
// void handle_auto()
// {
//   for (int j = 0; j < 6; j++)
//   {
//     digitalWrite(LED1pin, !digitalRead(LED1pin));
//     delay(100);
//   }
//   Serial.println("O");
//   server.send(200, "text/json", "{\"status\": \"AutoOk\"}");
// }

// String SendHTML(uint8_t led1stat, uint8_t led2stat)
// {
//   String ptr = "<!DOCTYPE html> <html>\n";
//   ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
//   ptr += "<title>AutoDoor</title>\n";
//   ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
//   ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
//   ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
//   ptr += ".button-on {background-color: #1abc9c;}\n";
//   ptr += ".button-on:active {background-color: #16a085;}\n";
//   ptr += ".button-off {background-color: #34495e;}\n";
//   ptr += ".button-off:active {background-color: #2c3e50;}\n";
//   ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
//   ptr += "</style>\n";
//   ptr += "</head>\n";
//   ptr += "<body>\n";
//   ptr += "<h1>MOnkeyDLOve</h1>\n";
//   ptr += "<h3>Auto Door control</h3>\n";

//   if (led1stat)
//   {
//     ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
//   }
//   else
//   {
//     ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
//   }

//   if (led2stat)
//   {
//     ptr += "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";
//   }
//   else
//   {
//     ptr += "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";
//   }

//   ptr += "</body>\n";
//   ptr += "</html>\n";

//   return ptr;
// }
// //===============================================================
// //                     LOOP
// //===============================================================
// unsigned long time_ = 0;
// void loop(void)
// {
//   server.handleClient(); // Handle client requests
//   if (doorStatus)
//   {
//     digitalWrite(LED1pin, LOW);
//     digitalWrite(LED2pin, HIGH);
//   }
//   else
//   {
//     digitalWrite(LED1pin, HIGH);
//     digitalWrite(LED2pin, LOW);
//   }

//   if (Serial.available() > 0)
//   {
//     state = Serial.read();
//     if (state == 'B')
//     {
//       doorStatus = 0;
//     }
//     else if (state == 'A')
//     {
//       doorStatus = 1;
//     }
//     else if (state == 'I')
//     {
//       doorStatus = 2;
//     }
//   }
//   else
//     state = 'x';
//   if (digitalRead(5) == 0)
//   {
//     delay(30);
//     while (digitalRead(5) == 0)
//       delay(5);
//     Serial.print('R');
//   }
//   if (digitalRead(4) == 0)
//   {
//     delay(30);
//     while (digitalRead(4) == 0)
//       delay(5);
//     Serial.print('L');
//   }
// }

/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 *
 * Copyright (c) 2022 mobizt
 *
 */

// This example shows how to get a document from a document collection. This operation required Email/password, custom or OAUth2.0 authentication.

// #include <ESP8266WiFi.h>

// #include <Firebase_ESP_Client.h>

// // Provide the token generation process info.
// #include <addons/TokenHelper.h>

// /* 1. Define the WiFi credentials */
// #define WIFI_SSID "Room103 2.4Ghz"
// #define WIFI_PASSWORD "khongcopass"

// /* 2. Define the API Key */
// #define API_KEY "AIzaSyA5rI5E-vWlwna6jN_C9Xju2xM7xLe27tQ"

// /* 3. Define the project ID */
// #define FIREBASE_PROJECT_ID "smart-house-vq"

// /* 4. Define the user Email and password that alreadey registerd or added in your project */
// #define USER_EMAIL "temp02@gmail.com"
// #define USER_PASSWORD "Aa@123456"

// // Define Firebase Data object
// FirebaseData fbdo;

// FirebaseAuth auth;
// FirebaseConfig config;

// unsigned long dataMillis = 0;
// int count = 0;

// // The Firestore payload upload callback function
// void fcsUploadCallback(CFS_UploadStatusInfo info)
// {
//   if (info.status == fb_esp_cfs_upload_status_init)
//   {
//     Serial.printf("\nUploading data (%d)...\n", info.size);
//   }
//   else if (info.status == fb_esp_cfs_upload_status_upload)
//   {
//     Serial.printf("Uploaded %d%s\n", (int)info.progress, "%");
//   }
//   else if (info.status == fb_esp_cfs_upload_status_complete)
//   {
//     Serial.println("Upload completed ");
//   }
//   else if (info.status == fb_esp_cfs_upload_status_process_response)
//   {
//     Serial.print("Processing the response... ");
//   }
//   else if (info.status == fb_esp_cfs_upload_status_error)
//   {
//     Serial.printf("Upload failed, %s\n", info.errorMsg.c_str());
//   }
// }

// void setup()
// {

//   Serial.begin(9600);

//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   Serial.print("Connecting to Wi-Fi");
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(300);
//   }
//   Serial.println();
//   Serial.print("Connected with IP: ");
//   Serial.println(WiFi.localIP());
//   Serial.println();

//   Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

//   /* Assign the api key (required) */
//   config.api_key = API_KEY;

//   /* Assign the user sign in credentials */
//   auth.user.email = USER_EMAIL;
//   auth.user.password = USER_PASSWORD;

//   /* Assign the callback function for the long running token generation task */
//   config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

// #if defined(ESP8266)
//   // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
//   fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
// #endif

//   // Limit the size of response payload to be collected in FirebaseData
//   fbdo.setResponseSize(2048);

//   Firebase.begin(&config, &auth);

//   Firebase.reconnectWiFi(true);

//   // For sending payload callback
//   // config.cfs.upload_callback = fcsUploadCallback;
// }

// void loop()
// {

//   // Firebase.ready() should be called repeatedly to handle authentication tasks.

//   if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
//   {
//     dataMillis = millis();

//     // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create.ino
//     FirebaseJson content;

//     // We will create the nested document in the parent path "a0/b0/c0
//     // a0 is the collection id, b0 is the document id in collection a0 and c0 is the collection id in the document b0.
//     // and d? is the document id in the document collection id c0 which we will create.
//     String documentPath = "a0/b0/c0/d" + String(count);

//     // If the document path contains space e.g. "a b c/d e f"
//     // It should encode the space as %20 then the path will be "a%20b%20c/d%20e%20f"

//     // double
//     content.set("fields/myDouble/doubleValue", 123.45678);

//     // boolean
//     content.set("fields/myBool/booleanValue", true);

//     // integer
//     content.set("fields/myInteger/integerValue", "911");

//     // null
//     content.set("fields/myNull/nullValue"); // no value set

//     String doc_path = "projects/";
//     doc_path += FIREBASE_PROJECT_ID;
//     doc_path += "/databases/(default)/documents/coll_id/doc_id"; // coll_id and doc_id are your collection id and document id

//     // reference
//     content.set("fields/myRef/referenceValue", doc_path.c_str());

//     // timestamp
//     content.set("fields/myTimestamp/timestampValue", "2014-10-02T15:01:23Z"); // RFC3339 UTC "Zulu" format

//     // bytes
//     content.set("fields/myBytes/bytesValue", "aGVsbG8="); // base64 encoded

//     // array
//     content.set("fields/myArray/arrayValue/values/[0]/stringValue", "test");
//     content.set("fields/myArray/arrayValue/values/[1]/integerValue", "20");
//     content.set("fields/myArray/arrayValue/values/[2]/booleanValue", true);

//     // map
//     content.set("fields/myMap/mapValue/fields/name/stringValue", "wrench");
//     content.set("fields/myMap/mapValue/fields/mass/stringValue", "1.3kg");
//     content.set("fields/myMap/mapValue/fields/count/integerValue", "3");

//     // lat long
//     content.set("fields/myLatLng/geoPointValue/latitude", 1.486284);
//     content.set("fields/myLatLng/geoPointValue/longitude", 23.678198);

//     count++;

//     Serial.print("Create a document... ");

//     if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
//       Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
//     else
//       Serial.println(fbdo.errorReason());
//   }
// }

#include <ESP8266WiFi.h>
#include <status_device.h>
#include <ESP8266WebServer.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>

/* config Wifi */
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
#define USER_EMAIL "temp02@gmail.com"
#define USER_PASSWORD "Aa@123456"
#define LED1pin D4
#define LED2pin D3
const String USER_UID = "lndKlnZh66SEIaKO6JVmJibQJ7A2";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;
bool turnOnLed = LOW;
bool turnOnSOS = LOW;
int btn = 0;
char state;
StatusDevice statusDevice;

//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
void fcsUploadCallback(CFS_UploadStatusInfo info);
void addApi();
void getAllStatus();
void updateStatus();
void handleNotFound();
String SendHTML(uint8_t led1stat, uint8_t led2stat);

//===============================================================
//                  SETUP
//===============================================================
void setup(void)
{
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
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
}

//===============================================================
//                     LOOP
//===============================================================
unsigned long time_ = 0;

void loop(void)
{
  server.handleClient(); // Handle client requests
  digitalWrite(LED1pin, turnOnLed);
  digitalWrite(LED2pin, turnOnSOS);
}

void addApi()
{
  server.on("/status", HTTP_GET, getAllStatus); // Which routine to handle at root location
  server.on("/status", HTTP_PATCH, updateStatus);
}

void handleNotFound()
{
  server.send(404, "text/plain", "{\"error\" :\"NotFound\"})");
}

void getAllStatus()
{
  statusDevice.userId = USER_UID;
  statusDevice.turnOnLed = turnOnLed;
  statusDevice.turnOnSOS = turnOnSOS;
  updateFirebase(statusDevice, fbdo, FIREBASE_PROJECT_ID);
  if (true)
  {
    server.send(200, "text/json", statusDevice.mapToJson());
  }
  else
  {
    server.send(400, "text/json", "{\"error\":\"" + fbdo.errorReason() + "\"}");
  }
}

void updateStatus()
{
  Serial.print("Update waiting");
  Serial.println(server.arg("plain"));
  if (server.hasArg("plain"))
  {
    StatusDevice statusDevice = StatusDevice::mapFromJson(server.arg("plain"));
    statusDevice.userId = USER_UID;
    updateFirebase(statusDevice, fbdo, FIREBASE_PROJECT_ID);
    if (true)
    {
      turnOnLed = statusDevice.turnOnLed ? HIGH : LOW;
      turnOnSOS = statusDevice.turnOnSOS ? HIGH : LOW;
      Serial.print(turnOnLed ? "true" : "false");
      server.send(200, "text/json", "{\"data\":\"success\"}");
    }
    else
    {
      server.send(400, "text/json", "{\"error\":\"" + fbdo.errorReason() + "\"}");
    }
  }
}
