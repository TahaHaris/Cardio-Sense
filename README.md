# Cardio-Sense 💓

**Cardio-Sense** is a compact, IoT-ready heart rate and SpO₂ monitoring system using the **MAX30102** pulse oximeter sensor and an **ESP8266** microcontroller. It detects and displays a user’s pulse and blood oxygen levels in real-time, ideal for personal health tracking, wearable projects, or telehealth applications.

## 🚀 Features

- 🔬 Accurate heart rate and SpO₂ measurement via MAX30102
- ⚡ Real-time data processing with ESP8266
- 🔄 Onboard LED indicator for pulse detection
- 🖥️ Serial monitor output for live debugging and BPM/SpO₂ readout
- 🌐 (Optional) Wi-Fi capability for future IoT integration

## 🧰 Hardware Requirements

| Component         | Description                        |
|------------------|------------------------------------|
| ESP8266 (NodeMCU) | Wi-Fi enabled microcontroller      |
| MAX30102          | Pulse oximeter and heart-rate sensor |
| Jumper wires      | For connections                    |
| Breadboard        | For prototyping                    |
| USB Cable         | For power and programming          |

## 🔌 Circuit Connections

| MAX30102 Pin | ESP8266 Pin |
|--------------|-------------|
| VIN          | 3.3V        |
| GND          | GND         |
| SDA          | D2 (GPIO4)  |
| SCL          | D1 (GPIO5)  |
| INT          | D0          |

> ⚠️ **Note:** Power the MAX30102 with 3.3V to avoid damaging the sensor.

## 📦 Library Dependencies

Install the following libraries via the Arduino Library Manager:

- `Adafruit MAX30105`
- `Adafruit Sensor`
- `Wire`
- `ESP8266WiFi` *(Optional, for Wi-Fi features)*

## 🔧 Setup and Usage

1. Clone or download this repository.
2. Open `Cardio-Sense.ino` in the Arduino IDE.
3. Select **ESP8266** as the board and the correct port.
4. Install all required libraries.
5. Upload the code to your board.
6. Open the Serial Monitor at **115200 baud**.
7. Place your finger on the sensor and observe live readings.

## 🧠 How It Works

The MAX30102 emits infrared and red light into the skin and measures the reflected light to determine:

- **Heart Rate (BPM):** Calculated by analyzing peaks in the IR signal.
- **SpO₂:** Estimated from the ratio of red and IR light absorption.

The ESP8266 handles signal processing and prints the data over serial. The onboard LED toggles with each heartbeat detection.

## 🌍 Future Improvements

- ☁️ Send data to a cloud server or dashboard
- 📱 Create a mobile app interface
- 🔋 Battery-powered wearable version
- 📊 Add OLED display support

## 👤 Author

Created by Taha Haris

---

💬 *Questions or improvements? Feel free to open an issue or contribute!*
