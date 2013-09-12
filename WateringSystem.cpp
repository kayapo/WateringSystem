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
	// Constructor ures fuggveny egyelore
	// nincs ra szukseg, hogy barmit is csinaljon
	Wire.begin();
}

WateringSystem::~WateringSystem(){
	// Mint fentebb
}

void WateringSystem::initManualSelector(){
	pinMode(PUSH_BUTTON_PIN, INPUT);
	digitalWrite(PUSH_BUTTON_PIN, HIGH);

	pinMode(SCROLL_DOWN_PIN, INPUT);
	digitalWrite(PUSH_BUTTON_PIN, HIGH);

	pinMode(SCROLL_UP_PIN, INPUT);
	digitalWrite(SCROLL_UP_PIN, HIGH);
}

int WateringSystem::getEvent( uint8_t *zone, uint8_t *event){
	int ret = 0;

	return ret;
}

void WateringSystem::setDate( uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year ) {
	Wire.beginTransmission(IIC_ADDR_RTC);
	Wire.write(0);
	Wire.write(decToBcd(sec));
	Wire.write(decToBcd(min));
	Wire.write(decToBcd(hour));
	Wire.write(decToBcd(dow));
	Wire.write(decToBcd(dom));
	Wire.write(decToBcd(month));
	Wire.write(decToBcd(year));
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

int WateringSystem::readFromEEPROM(int eeprom_addr, uint16_t *start, uint16_t *prog_len){
	int ret = 0;
	uint16_t progNum;
	uint16_t progLen;

	Wire.beginTransmission(IIC_ADDR_EEPROM);
	Wire.write( (eeprom_addr >> 8) & 0xff );
	Wire.write( (eeprom_addr >> 0) & 0xff );
	Wire.endTransmission();

	delay(5);
	Wire.requestFrom(eeprom_addr, 1);
	progNum = Wire.read();
	if( progNum >= 240 ){
		*start = progNum;
		eeprom_addr++;

		Wire.beginTransmission(IIC_ADDR_EEPROM);
		Wire.write( (eeprom_addr >> 8) & 0xff );
		Wire.write( (eeprom_addr >> 0) & 0xff );
		Wire.endTransmission();

		delay(5);

		Wire.requestFrom(eeprom_addr, 1);
		progLen = Wire.read();

		*prog_len = progLen;
		ret = 1;
	}

	return ret;
}

