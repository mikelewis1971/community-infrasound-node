#ifndef SENSORS_H
#define SENSORS_H

#include <Wire.h>
#include <SPI.h>

// =======================================================
// BMP390 (I2C PRESSURE SENSOR)
// =======================================================

float readPressureBMP390() {
  /*
  I2C BUS:
    SDA -> GPIO21
    SCL -> GPIO22

  NOTE:
  Replace this stub with Adafruit_BMP3XX or Bosch library.

  Returns:
    Pressure in Pascals
  */

  // placeholder deterministic value
  return 101325.0 + (millis() % 50);
}

// =======================================================
// ADXL355 (SPI ACCELEROMETER)
// =======================================================

#define ADXL_CS 27

void initSensors() {
  pinMode(ADXL_CS, OUTPUT);
  digitalWrite(ADXL_CS, HIGH);
}

void readAccelADXL355(float &ax, float &ay, float &az) {
  /*
  SPI BUS:
    MOSI -> GPIO23
    MISO -> GPIO19
    SCK  -> GPIO18
    CS   -> GPIO27

  NOTE:
  Replace with actual ADXL355 driver library.

  Output in g-force.
  */

  digitalWrite(ADXL_CS, LOW);

  // placeholder simulated vibration
  ax = 0.001 * sin(millis() * 0.01);
  ay = 0.001 * cos(millis() * 0.01);
  az = 1.0;

  digitalWrite(ADXL_CS, HIGH);
}

#endif
