// ---------------------------------------------------------------------------
// Created by Molnar Istvan on 09/09/2013
// Copyright: All rights reserved
//
// @file: WateringSystem.cpp
// This file implements all functionalities of the WateringSystem
//
// @author: Molnar Istvan  <kayapo@molnaristvan.eu>
// ---------------------------------------------------------------------------
#include <Arduino.h>
#include "lib/Wire.h"
#include "lib/LiquidCrystal_I2C.h"
#include "WateringSystem.h"

// CONSTANT  definitions
// ---------------------------------------------------------------------------

/*!
 * @defined
 * @abstract   IIC_ADDR_LCD
 * @discussion Address of LCD display on IIC channel
 */
#define IIC_ADDR_LCD 0x3f

/*!
 * @defined
 * @abstract   IIC_ADDR_RTC
 * @discussion Address of RTC module on IIC channel
 */
#define IIC_ADDR_RTC 0x68

/*!
 * @defined
 * @abstract   IIC_ADDR_EEPROM
 * @discussion Address of EEPROM datastore on IIC channel
 */
#define IIC_ADDR_EEPROM 0x50

/*!
 * @defined
 * @abstract   IIC_ADDR_RELAY
 * @discussion Address of relay block (MCP23017) on IIC channel
 */
#define IIC_ADDR_RELAY 0x20

/*!
 * @defined
 * @abstract   PUSH_BUTTON_PIN
 * @discussion For this pin connected the rotary encoders push button
 */
#define PUSH_BUTTON_PIN 11

/*!
 * @defined
 * @abstract   SCROLL_UP_PIN
 * @discussion For this pin connected the rotary encoders rotate first direction
 */
#define SCROLL_UP_PIN 12

/*!
 * @defined
 * @abstract   SCROLL_DOWN_PIN
 * @discussion For this pin connected the rotary encoders rotate other direction
 */
#define SCROLL_DOWN_PIN 13

// PUBLIC METHODS
// ---------------------------------------------------------------------------
void WateringSystem::WateringSystem(){

}


void WateringSystem::setDate( uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year ) {
	Wire.beginTransmission(IIC_ADDR_RTC);
	Wire.write(0);
	Wire.write(bcdToDec(sec));
	Wire.write(bcdToDec(min));
	Wire.write(bcdToDec(hour));
	Wire.write(bcdToDec(dow));
	Wire.write(bcdToDec(dom));
	Wire.write(bcdToDec(month));
	Wire.write(bcdToDec(year));
	Wire.write(0x10);
	Wire.endTransmission();
}

void WateringSystem::getDate( uint8_t *sec, uint8_t *min, uint8_t *hour, uint8_t *dow, uint8_t *dom, uint8_t *month, uint8_t *year ) {
	Wire.beginTransmission(IIC_ADDR_RTC);
	Wire.write(0);
	Wire.endTransmission();

	Wire.requestFrom(IIC_ADDR_RTC, 7);

	*sec   = bcdToDec(Wire.read() & 0x7f);
	*min   = bcdToDec(Wire.read());
	*hour  = bcdToDec(Wire.read() & 0x3f);
	*dow   = bcdToDec(Wire.read());
	*dom   = bcdToDec(Wire.read());
	*month = bcdToDec(Wire.read());
	*year  = bcdToDec(Wire.read());
}

// PRIVATE METHODS
// ---------------------------------------------------------------------------
byte WateringSystem::bcdToDec(byte val){
	return ( (val/16*10) + (val%16) );
}

byte WateringSystem::decToBcd(byte val){
	return ( (val/10*16) + (val%10) );
}
