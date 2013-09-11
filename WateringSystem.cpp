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

// PUBLIC METHODS
// ---------------------------------------------------------------------------
WateringSystem::WateringSystem(){

}

WateringSystem::~WateringSystem(){

}

void WateringSystem::initManualSelector(){
	pinMode(PUSH_BUTTON_PIN, INPUT);
	digitalWrite(PUSH_BUTTON_PIN, HIGH);

	pinMode(SCROLL_DOWN_PIN, INPUT);
	digitalWrite(PUSH_BUTTON_PIN, HIGH);

	pinMode(SCROLL_UP_PIN, INPUT);
	digitalWrite(SCROLL_UP_PIN, HIGH);
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
