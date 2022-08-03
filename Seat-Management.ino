#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "vivo"
#define WIFI_PASSWORD "123456789"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAnN_2lo3i3EIhDY3_z6VfPIuB_MEX2WxM"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://ksaudi-84809.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

int r1c1 = 13; // choose input pin (for Infrared sensor) 
bool val1 = false; // variable for reading the pin status
int irval1 = 0;

int r2c1 = 12;
bool val2 = false;
int irval2 = 0;

int r3c1 = 14;
bool val3 = false;
int irval3 = 0;

void setup(){
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  
  config.database_url = DATABASE_URL;

  /* Sign up */
  
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  pinMode(r1c1, INPUT); // declare Infrared sensor as input
  pinMode(r2c1, INPUT);
}

void loop(){

  irval1 = digitalRead(r1c1);
  irval2 = digitalRead(r2c1);
  irval3 = digitalRead(r3c1);
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    if (irval1 == HIGH)
      { // check if the input is HIGH
        val1 = true;
        if (Firebase.RTDB.setString(&fbdo, "/Seat/Row 1/chair1", val1)){
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
        Serial.println("1"); 
      }
     else{
      val1 = false;
      if (Firebase.RTDB.setString(&fbdo, "/Seat/Row 1/chair1", val1)){
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
        Serial.println("0"); 
     }

    //IR - 2
    if (irval2 == HIGH)
      { // check if the input is HIGH
        val2 = true;
        if (Firebase.RTDB.setString(&fbdo, "/Seat/Row 2/chair1", val2)){
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
        Serial.println("1"); 
      }
     else{
      val2 = false;
      if (Firebase.RTDB.setString(&fbdo, "/Seat/Row 2/chair1", val2)){
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
        Serial.println("0"); 
     }

     //IR - 3
     if (irval3 == HIGH)
      { // check if the input is HIGH
        val3 = true;
        if (Firebase.RTDB.setString(&fbdo, "/Seat/Row 3/chair1", val3)){
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
        Serial.println("1"); 
      }
     else{
      val3 = false;
      if (Firebase.RTDB.setString(&fbdo, "/Seat/Row 3/chair1", val3)){
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
        Serial.println("0"); 
     }
  }
}
