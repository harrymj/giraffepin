#include <BlueNRG.h>
#include <SparkFunLSM6DS3.h>
#include "Wire.h"
#include "SPI.h"

/* giraffe_RGB
   @Harry Johnson, 2018
   Starter code for Giraffe Pin PCB
   https://workspace.circuitmaker.com/Projects/Details/Harry-Johnson/Giraffe-Pin
   This code makes use of Sparkfun's LSM6DS3 library, which must be installed separately.
*/

const int kPinLedGreen = 13; // LED on Front Leg.

const int kPinRGBRed = 6;
const int kPinRGBGreen = 9;
const int kPinRGBBlue = 10;

const int kPinGyroInt = 1; // 6DOF I2C Interrupt.

const int kPinBleCs = A5; // Active Low.
const int kPinBleIrq = 7; // Active High.
const int kPinBleReset = 11; // Active Low.

const int kPinVbatSense = A2; // Analog.

// This works reliably on 1/1 board that I've tested it on, but may be 0x6A on other boards.
LSM6DS3 imu(I2C_MODE, 0x6B);

void setup() {
  // LED Initialization.
  pinMode(kPinLedGreen, OUTPUT);
  pinMode(kPinRGBRed, OUTPUT);
  pinMode(kPinRGBGreen, OUTPUT);
  pinMode(kPinRGBBlue, OUTPUT);

  digitalWrite(kPinLedGreen, LOW); // Keep all LEDs off to begin with.
  digitalWrite(kPinRGBRed, LOW);
  digitalWrite(kPinRGBGreen, LOW);
  digitalWrite(kPinRGBBlue, LOW);

  // BlueNRG Initialization. Here, just keep BlueNRG in reset.
  pinMode(kPinBleCs, OUTPUT); // Active Low.
  pinMode(kPinBleReset, OUTPUT); // Active Low
  pinMode(kPinBleIrq, INPUT); //Active High.

  // Gyro Initialization.
  pinMode(kPinGyroInt, INPUT);
  imu.begin();

  // VBAT sense initialization.
  pinMode(kPinVbatSense, INPUT); // ADC pin must be configured as input.
}


void loop() {
  // Turn on Red, Green, and Blue LEDs based on which direction is facing down.
  // Crude logic, but it works for a basic demo.
  digitalWrite(kPinRGBRed, (abs(imu.readFloatAccelX()) > 0.8));
  digitalWrite(kPinRGBGreen, (abs(imu.readFloatAccelY()) > 0.8));
  digitalWrite(kPinRGBBlue, (abs(imu.readFloatAccelZ()) > 0.8));
  delay(10);
}
