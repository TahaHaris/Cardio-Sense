# Cardio-Sense 💓

**Cardio-Sense** is a complete heart health monitoring system that combines hardware (ESP8266 + MAX30102) with a modern web application. It provides real-time heart rate (BPM) and blood oxygen (SpO₂) readings, and leverages AI to offer health insights. Designed for personal wellness, fitness training, or telehealth research, it’s both lightweight and powerful.

---

## 🚀 Getting Started

#### 🧰 Hardware Requirements

| Component         | Description                               |
|------------------|-------------------------------------------|
| ESP8266 (NodeMCU) | Wi-Fi enabled microcontroller             |
| MAX30102          | Pulse oximeter + heart-rate sensor module |
| Jumper Wires      | For making electrical connections         |
| Breadboard        | For prototyping without soldering         |
| USB Cable         | To program and power the ESP8266          |

#### 🔌 Circuit Connections

| MAX30102 Pin | ESP8266 Pin |
|--------------|-------------|
| VIN          | 3.3V        |
| GND          | GND         |
| SDA          | D2 (GPIO4)  |
| SCL          | D1 (GPIO5)  |
| INT          | D0 (GPIO16) |

> ⚠️ **Warning:** Do not power the MAX30102 with 5V. Use 3.3V only.

#### ⚙️ How to Run

```bash
git clone https://github.com/your-username/cardio-sense.git
cd cardio-sense/firmware
```

1. Open `Cardio-Sense.ino` in Arduino IDE
2. Select **ESP8266** as your board and choose the correct port
3. Upload the code
4. Open Serial Monitor at **115200 baud**
5. Place your finger on the MAX30102 to start receiving live data

---

💻 **Step 2: Web App (Real-Time Monitoring & AI)**

The Cardio-Sense Web Application helps users **track**, **visualize**, and **analyze** their heart health using real-time data synced from Firebase.

#### 🛠️ Tech Stack

| Layer     | Tools Used                                                  |
|-----------|-------------------------------------------------------------|
| Frontend  | Next.js, React, TypeScript                                  |
| UI/UX     | Tailwind CSS, ShadCN UI, Lucide Icons, custom SVG branding  |
| AI        | Genkit – for intelligent HR analysis                        |
| Backend   | Firebase Realtime Database                                  |

#### 📁 Setup Instructions

```bash
cd cardio-sense/web
npm install
npm run dev
```

> ⚠️ Connect this app to a Firebase project and configure your `.env.local` with Firebase credentials.

---

## 🧠 Features Overview (Detailed)

### 📟 Firmware Features (ESP8266 + MAX30102)

- **Accurate Heart Rate & SpO₂ Measurement:**
  - Uses IR and red light to detect heartbeat and blood oxygen saturation.
  - Calculates BPM from IR signal peaks.
  - Estimates SpO₂ from red/IR ratio.

- **Real-Time Data Display:**
  - Prints live heart rate and SpO₂ values to the serial monitor.
  - Onboard LED toggles with each detected heartbeat.

- **Wi-Fi & Firebase Support:**
  - Pushes live data to Firebase Realtime Database (`/vitals/heartRate` and `/vitals/spo2`).
  - Enables integration with web dashboards or cloud services.

---

### 🖥️ Web Application Features

#### 1. **Main Layout & Navigation**
- **Sidebar Navigation:** Clean and collapsible sidebar with easy access to pages.
- **Navigation Links:**
  - **Dashboard:** View real-time health data
  - **History:** Analyze past trends
  - **Zones:** Configure and simulate workouts
- **User Actions (Planned):** Buttons for Account, Settings, Logout (placeholders)

---

#### 2. **Dashboard Page**

- **Live Reading Card:**
  - Fetches real-time `heartRate` and `spo2` from Firebase.
  - Shows data in large readable format.
  - Handles loading/error states gracefully.

- **AI Heart Rate Analysis Card:**
  - Inputs: heart rate, SpO₂, age, resting HR, activity level.
  - Uses AI to analyze data and return:
    - Whether your heart rate is normal or abnormal.
    - Explanation and health recommendation.
  - User-friendly feedback with validation and loading indicators.

**Dashboard Demo:** https://github.com/TahaHaris/Cardio-Sense/blob/main/Dashboard%20Page.gif
    

---

#### 3. **History Page**

- **Heart Rate Data Visualizations:**
  - Interactive **line chart** showing:
    - Daily average, min, and max BPM over the past 30 days.
  - **Bar chart** for comparative daily averages.
  - Helps identify long-term trends and anomalies.
  - (Currently uses mock data, but Firebase integration is planned.)

**History Demo:** https://github.com/TahaHaris/Cardio-Sense/blob/main/History%20Page.gif

---

#### 4. **Zones Page**

- **Zone Configuration:**
  - Input age or manual Maximum Heart Rate (MHR).
  - Auto-calculates zones using `220 - age` formula.
  - Zones include:
    - Warm-Up (50–60% MHR)
    - Fat Burn (60–70%)
    - Cardio (70–80%)
    - Peak (80–90%)
    - Max Effort (90–100%)

- **Workout Simulation Tracker:**
  - Simulates workout session data.
  - Shows % time spent in each zone with progress bars.
  - Displays total time and breakdown by zone.

- **Personalized Zone Display:**
  - Lists zone names, BPM ranges, MHR %, and color codes.
  - Helps users optimize training based on goals (e.g., fat burn vs endurance).
 
**Zone Page:** https://github.com/TahaHaris/Cardio-Sense/blob/main/Zone%20Page.gif

---

#### 5. **AI Capabilities**

  - Takes user inputs and gives AI feedback:
    - Is your heart rate normal?
    - Why?
    - What should you do?
  - Uses Zod schemas to validate data types and enforce structure.

---

## 💡 Why This Matters

Heart disease is the leading cause of death globally.  
Cardio-Sense brings affordable, real-time heart monitoring to everyone.  
It helps users detect issues early, optimize fitness, and enable remote care.  
Combining accessible hardware with AI insights, it turns raw data into action.

## 👤 Author

**Taha Haris**

> 💬 Have ideas, bugs, or questions?

