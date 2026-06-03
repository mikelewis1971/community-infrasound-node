/*
=========================================================
 Community Vibration + Pressure Monitoring Node
 Hardware: ESP32 DevKit V1
 Sensors:
   - BMP390 (I2C pressure)
   - ADXL355 (SPI accelerometer)
   - microSD (SPI logging)

 Wiring:
 --------------------------------------------------------

 I2C (BMP390):
   SDA -> GPIO21
   SCL -> GPIO22
   VCC -> 3.3V
   GND -> GND

 SPI BUS (shared):
   MOSI -> GPIO23
   MISO -> GPIO19
   SCK  -> GPIO18

 Devices:
   SD_CS     -> GPIO5
   ADXL355_CS-> GPIO27

 =========================================================
*/

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "sensors.h"

// ---------------- PINS ----------------
#define SD_CS 5
#define ADXL_CS 27

File logFile;

unsigned long lastSample = 0;
const int SAMPLE_MS = 5; // 200 Hz

void setup() {
  Serial.begin(115200);

  // I2C INIT (BMP390)
  Wire.begin(21, 22);

  // SPI INIT
  SPI.begin(18, 19, 23);

  // SD INIT
  if (!SD.begin(SD_CS)) {
    Serial.println("SD FAIL");
    while (1);
  }

  logFile = SD.open("/data.csv", FILE_WRITE);

  if (!logFile) {
    Serial.println("FILE FAIL");
    while (1);
  }

  logFile.println("time_ms,pressure_pa,ax,ay,az");
  logFile.flush();

  initSensors();

  Serial.println("NODE READY");
}

void loop() {
  unsigned long now = millis();

  if (now - lastSample >= SAMPLE_MS) {
    lastSample = now;

    float pressure = readPressureBMP390();

    float ax, ay, az;
    readAccelADXL355(ax, ay, az);

    logFile.print(now);
    logFile.print(",");
    logFile.print(pressure, 4);
    logFile.print(",");
    logFile.print(ax, 6);
    logFile.print(",");
    logFile.print(ay, 6);
    logFile.print(",");
    logFile.println(az, 6);

    logFile.flush();
  }
}
