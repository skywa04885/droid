#pragma once

#include <Arduino.h>

#define LACAR_DROID_FIRMWARE__I2C1__SDA PB9
#define LACAR_DROID_FIRMWARE__I2C1__SCL PB8

#define LACAR_DROID_FIRMWARE__SPI1__SCK PA5
#define LACAR_DROID_FIRMWARE__SPI1__MISO PA6
#define LACAR_DROID_FIRMWARE__SPI1__MOSI PA7

#define LACAR_DROID_FIRMWARE__RF24__CE PC8
#define LACAR_DROID_FIRMWARE__RF24__CS PC9
#define LACAR_DROID_FIRMWARE__RF24__ADDR 0
#define LACAR_DROID_FIRMWARE__RF24__PA_LAVEL RF24_PA_MAX
#define LACAR_DROID_FIRMWARE__RF24__DATA_RATE RF24_250KBPS 
#define LACAR_DROID_FIRMWARE__RF24__CHANNEL 0