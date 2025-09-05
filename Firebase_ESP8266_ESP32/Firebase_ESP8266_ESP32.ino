#include <Arduino.h>
// #include <WiFi.h>
// #include <FirebaseESP32.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <addons/RTDBHelper.h>
#include <Servo.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Five Star Apartment Floor 4" //Five Star Apartment Floor 4
#define WIFI_PASSWORD "fst1658/29" //fst1658/29

/* 2. If work with RTDB, define the RTDB URL and database secret */
#define DATABASE_URL "smartdoorlock-aec8c-default-rtdb.asia-southeast1.firebasedatabase.app"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "VNqftOizmFgBn0bQNA10ntV45nb9wNgOo2sIDeZO"

/* 3. Define the Firebase Data object */
FirebaseData fbdo;

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

#define LED 2
// #define buzz 16
const int servoPin = 13;
int Door1;
Servo servo;

// int PWM_FREQUENCY = 5000;
// int PWM_CHANNEL_2 = 2;
void setup() {
  Serial.begin(115200);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  multi.addAP(WIFI_SSID, WIFI_PASSWORD);
  multi.run();
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    if (millis() - ms > 10000)
      break;
#endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the certificate file (optional) */
  // config.cert.file = "/cert.cer";
  // config.cert.file_storage = StorageType::FLASH;

  /* Assign the database URL and database secret(required) */
  config.database_url = DATABASE_URL;
  config.signer.tokens.legacy_token = DATABASE_SECRET;
  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);
  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  config.wifi.clearAP();
  config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif
  Firebase.begin(&config, &auth);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 1);  // active low
  
  servo.attach(servoPin, 500, 2400);

  delay(500);
}

void loop() {
  if (Firebase.getInt(fbdo, "/Hotel/Room1/Door1")) {
    if (fbdo.dataType() == "int") {
      // Serial.print("Door1 : "); Serial.println(((fbdo.intData() == 0)? "Unlock" : "Lock"));
      Door1 = fbdo.intData();
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  Serial.print(Door1);
  if (Door1==0) {
    digitalWrite(LED, !Door1);  // Unlock
    servo.write(180);
    Serial.println(" Unlocked");
    // delay(5000);
    // Firebase.setInt(fbdo, "/Hotel/Room1/Door1", 1);
  } else{
    digitalWrite(LED, !Door1);  // Lock
    servo.write(0);
    Serial.println(" Locked");
  }
  delay(1500);
}
