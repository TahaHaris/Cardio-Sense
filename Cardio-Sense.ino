#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi Credentials
#define WIFI_SSID "ur-wifi-name"
#define WIFI_PASSWORD "ur-wifi-password"

// Firebase Credentials
#define FIREBASE_HOST "ur-firebase-database-link"
#define FIREBASE_AUTH "ur-firebase-database"

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

// TFT Display Pins
#define TFT_CS     15  // D8
#define TFT_DC      3  // RX
#define TFT_RST     0  // D3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// MAX30102 Sensor
MAX30105 particleSensor;

uint32_t irBuffer[100];
uint32_t redBuffer[100];
const int bufferLength = 100;

int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // --- TFT Initialization ---
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_WHITE);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Initializing...");
  delay(1000);

  // --- Sensor Initialization ---
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    tft.setCursor(10, 50);
    tft.setTextColor(ST77XX_RED);
    tft.println("Sensor FAIL");
    Serial.println("MAX30102 not found.");
    while (1);
  }

  particleSensor.setup(60, 4, 2, 100, 411, 4096);

  tft.fillScreen(ST77XX_WHITE);
  tft.setCursor(10, 10);
  tft.println("MAX30102");
  tft.setCursor(10, 35);
  tft.println("Ready");

  delay(1000);

  // --- Wi-Fi Setup ---
  Serial.println("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP:");
  Serial.println(WiFi.localIP());

  // --- Firebase Setup ---
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  if (Firebase.ready()) {
    Serial.println("Firebase connected!");
  } else {
    Serial.println("Firebase connection failed.");
  }
}

void loop() {
  for (int i = 0; i < bufferLength; i++) {
    while (!particleSensor.available()) {
      particleSensor.check();
    }
    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample();
  }

  maxim_heart_rate_and_oxygen_saturation(
    irBuffer, bufferLength, redBuffer,
    &spo2, &validSPO2, &heartRate, &validHeartRate
  );

  int hr = validHeartRate ? heartRate : 0;
  int ox = validSPO2 ? spo2 : 0;

  Serial.print("Heart Rate: "); Serial.print(hr); Serial.print(" bpm, ");
  Serial.print("SpO2: "); Serial.print(ox); Serial.println(" %");

  // --- Display on TFT ---
  tft.fillScreen(ST77XX_WHITE);
  tft.setCursor(10, 10); tft.print("Heart Rate:");
  tft.setCursor(10, 35); tft.print(hr); tft.println(" bpm");
  tft.setCursor(10, 70); tft.print("SpO2:");
  tft.setCursor(10, 95); tft.print(ox); tft.println(" %");

  // --- Send to Firebase ---
  if (Firebase.ready()) {
    Firebase.setInt(firebaseData, "/vitals/heartRate", hr);
    Firebase.setInt(firebaseData, "/vitals/spo2", ox);
    Serial.println("Data sent to Firebase!");
  } else {
    Serial.println("Firebase not ready!");
  }

  delay(2000);  // Wait 2 seconds before next reading
}
