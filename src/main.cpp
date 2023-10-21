#include <Arduino.h>
#include <Wire.h>

#include "config.hpp"
#include "MyDisplay.hpp"
#include "MyAccelerometer.hpp"
#include "MyCom.hpp"
#include "MyGPS.hpp"

using namespace lacar::droid::firmware;

void setup()
{
  Serial.begin(115200);

  SPI.begin();
  Wire.begin(LACAR_DROID_FIRMWARE__I2C1__SDA,
             LACAR_DROID_FIRMWARE__I2C1__SCL);

  MyDisplay::getInstance().begin();
  MyAccelerometer::getInstance().setup();
  MyCom::getInstance().setup();
  MyGPS::getInstance().setup();

  // g_GPS.begin();
}

void loop()
{
  MyDisplay::getInstance().update();
  MyAccelerometer::getInstance().loop();
  MyCom::getInstance().loop();
  MyGPS::getInstance().loop();
}
