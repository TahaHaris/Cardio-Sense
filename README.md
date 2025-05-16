Cardio-Sense: Heart Rate and SpO2 Monitor
Overview
Cardio-Sense is an Arduino-based project that uses the MAX30102 sensor to measure heart rate (in beats per minute, bpm) and blood oxygen saturation (SpO2, in percentage). The measurements are displayed on a 1.8" ST7735 TFT color display and printed to the Serial Monitor for debugging. This project is ideal for hobbyists and developers interested in health monitoring applications.
Features

Real-time heart rate and SpO2 measurement
Visual output on a 1.8" ST7735 TFT display
Serial output for debugging
Configurable sensor parameters for optimal performance
Error handling for sensor initialization failures

Hardware Requirements

Microcontroller: Arduino-compatible board (e.g., Arduino Uno, ESP8266, or ESP32)
Sensor: MAX30102 or MAX30105 pulse oximeter and heart rate sensor
Display: 1.8" ST7735 TFT color display (128x160 resolution)
Wiring:
MAX30102: Connect via I2C (SDA, SCL, VCC, GND)
ST7735 TFT:
CS: Pin 15 (D8)
DC: Pin 3 (RX)
RST: Pin 0 (D3) or connect to 3.3V
SCK, MOSI: SPI pins (board-specific)




Power: 3.3V or 5V depending on the board

Software Requirements

Arduino IDE: Version 1.8.0 or later
Libraries:
Wire.h (included with Arduino IDE)
SPI.h (included with Arduino IDE)
Adafruit_GFX (install via Library Manager)
Adafruit_ST7735 (install via Library Manager)
MAX30105 (SparkFun MAX3010x Sensor Library, install via Library Manager)
spo2_algorithm.h (included with SparkFun MAX3010x library)



Installation

Set up the Arduino IDE:

Download and install the Arduino IDE from arduino.cc.
Install the required libraries using the Library Manager:
Go to Sketch > Include Library > Manage Libraries.
Search for and install Adafruit GFX Library, Adafruit ST7735 and ST7789 Library, and SparkFun MAX3010x Sensor Library.




Connect the hardware:

Wire the MAX30102 sensor to the I2C pins of your Arduino board.
Connect the ST7735 TFT display to the specified pins (CS: 15, DC: 3, RST: 0).
Ensure proper voltage levels (3.3V for MAX30102, check TFT requirements).


Upload the code:

Open the Cardio-Sense.ino file in the Arduino IDE.
Select your board and port from Tools > Board and Tools > Port.
Click Upload to compile and upload the code to your board.



Usage

Power on the device:

Connect the Arduino board to a power source (USB or external power).
The TFT display will show an "Initializing Sensor..." message.


Sensor calibration:

Place your finger on the MAX30102 sensor for accurate readings.
After initialization, the display will show "MAX30102 Ready!".


Monitor readings:

The TFT display updates every 0.5 seconds with:
Heart Rate (in bpm)
SpO2 (in %)


Open the Serial Monitor (Tools > Serial Monitor, 115200 baud) to view the same readings for debugging.


Troubleshooting:

If the display shows "Sensor FAIL", check the MAX30102 wiring and ensure it is properly connected.
Ensure the finger is correctly placed on the sensor for valid readings (invalid readings display as 0).



Code Details

File: Cardio-Sense.ino
Sensor Configuration:
LED Brightness: 60 (adjustable, 0-255)
Sample Average: 4
Mode: Red + IR
Sampling Rate: 100 Hz
Pulse Width: 411 µs
ADC Range: 4096


Buffers: Stores 100 samples of IR and Red LED data for processing.
Algorithm: Uses maxim_heart_rate_and_oxygen_saturation from spo2_algorithm.h to calculate heart rate and SpO2.

Limitations

The MAX30102 sensor requires proper finger placement for accurate results.
Readings may be affected by ambient light, motion, or poor sensor contact.
This project is for educational purposes and not a certified medical device.

Contributing
Contributions are welcome! To contribute:

Fork the repository.
Create a new branch for your feature or bug fix.
Submit a pull request with a clear description of changes.

License
This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments

SparkFun for the MAX3010x library and algorithm
Adafruit for the ST7735 and GFX libraries

