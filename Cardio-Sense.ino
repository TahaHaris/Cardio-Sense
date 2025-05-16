#include <Wire.h>                      // For I2C communication
#include "MAX30105.h"                 // SparkFun library for MAX3010x sensors
#include "spo2_algorithm.h"           // Algorithm for calculating SpO2 and heart rate
#include <Adafruit_GFX.h>             // Core graphics library for displays
#include <Adafruit_ST7735.h>          // Library for ST7735 TFT display
#include <SPI.h>                      // For SPI communication

// ----- TFT Display Setup -----
#define TFT_CS     15  // Chip Select pin for TFT (D8)
#define TFT_DC      3  // Data/Command pin for TFT (RX)
#define TFT_RST     0  // Reset pin for TFT (D3); use -1 if connected to 3.3V
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); // Initialize TFT object

// ----- MAX30102 Sensor Setup -----
MAX30105 particleSensor;              // Create sensor object

uint32_t irBuffer[100];              // Buffer to store 100 IR samples
uint32_t redBuffer[100];             // Buffer to store 100 Red LED samples

int32_t bufferLength = 100;          // Number of samples to read
int32_t spo2;                        // Calculated SpO2 value
int8_t validSPO2;                    // Flag for valid SpO2 reading (1 = valid)
int32_t heartRate;                   // Calculated heart rate value
int8_t validHeartRate;              // Flag for valid heart rate (1 = valid)

void setup() {
  Serial.begin(115200);             // Start serial communication at 115200 baud
  Wire.begin();                     // Initialize I2C bus

  // --- Initialize TFT Display ---
  tft.initR(INITR_BLACKTAB);        // Initialize with Black Tab configuration
  tft.setRotation(1);               // Rotate display to landscape
  tft.fillScreen(ST77XX_WHITE);     // Fill screen with white
  tft.setTextColor(ST77XX_WHITE);   // Set text color (initially white)
  tft.setTextSize(2);               // Set text size to 2

  // Display startup message
  tft.setCursor(10, 10);
  tft.println("Initializing");

  tft.setCursor(10, 35);
  tft.println("Sensor...");

  // --- Initialize MAX30102 Sensor ---
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) { // Try to initialize sensor
    Serial.println("MAX30102 not found. Check wiring."); // Print error to serial
    tft.setCursor(10, 70);
    tft.setTextColor(ST77XX_RED);  // Set text color to red
    tft.println("Sensor FAIL");    // Show failure message on display
    while (1);                     // Halt program if sensor not found
  }

  // Configure sensor parameters
  particleSensor.setup(
    60,     // LED brightness
    4,      // Average samples
    2,      // Mode: Red + IR
    100,    // Sampling rate in Hz
    411,    // Pulse width in microseconds
    4096    // ADC range
  );

  delay(500);                       // Wait for sensor to stabilize

  // Display ready message
  tft.fillScreen(ST77XX_WHITE);     // Clear display
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_BLACK);   // Set text color to black
  tft.println("MAX30102");

  tft.setCursor(10, 30);
  tft.println("Ready!");
  delay(1000);                      // Short delay before starting loop
}

void loop() {
  // Fill buffers with 100 samples
  for (int i = 0; i < bufferLength; i++) {
    while (!particleSensor.available()) { // Wait for new sample to be ready
      particleSensor.check();             // Check for new data
    }
    redBuffer[i] = particleSensor.getRed(); // Get Red LED value
    irBuffer[i] = particleSensor.getIR();   // Get IR LED value
    particleSensor.nextSample();            // Advance internal sample buffer
  }

  // Calculate heart rate and SpO2 using algorithm
  maxim_heart_rate_and_oxygen_saturation(
    irBuffer, bufferLength, redBuffer,
    &spo2, &validSPO2, &heartRate, &validHeartRate
  );

  // Print results to Serial Monitor
  Serial.print("Heart Rate: ");
  Serial.print(validHeartRate ? heartRate : 0);  // Print heart rate if valid
  Serial.print(" bpm / SpO2: ");
  Serial.print(validSPO2 ? spo2 : 0);            // Print SpO2 if valid
  Serial.println(" %");

  // Display results on TFT screen
  tft.fillScreen(ST77XX_WHITE);     // Clear screen for new values

  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.print("Heart Rate:");

  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(10, 35);
  tft.print(validHeartRate ? heartRate : 0); // Show valid or zero
  tft.println(" bpm");

  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(10, 70);
  tft.print("SpO2:");

  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(10, 95);
  tft.print(validSPO2 ? spo2 : 0);           // Show valid or zero
  tft.println(" %");

  delay(500);                                // Update display every 0.5 seconds
}
