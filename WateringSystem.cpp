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

void WateringSystem::resetZones(){
	int c;
	for(c = 0; c < 16; c++){
			zoneStatus[c] = 0x00;
	}
}

void WateringSystem::initManualSelector(){
	pinMode(PUSH_BUTTON_PIN, INPUT);
	digitalWrite(PUSH_BUTTON_PIN, HIGH);

	pinMode(SCROLL_DOWN_PIN, INPUT);
	digitalWrite(PUSH_BUTTON_PIN, HIGH);

	pinMode(SCROLL_UP_PIN, INPUT);
	digitalWrite(SCROLL_UP_PIN, HIGH);
}

void WateringSystem::readProgram(int year, int month, int dom, int dow, int hour, int min, int sec){
	// Egy program hossza: 9byte * 2fazis * 14lepes = 252byte
	int PROGNUM = EEPROM_LENGTH / PROGRAM_LENGTH;
	int prg_addr, pa, in_zone, in_year, in_month, in_dom, in_dow, in_hour, in_min, in_sec, in_state;

	for( prg_addr = 0; prg_addr < EEPROM_LENGTH; prg_addr += PROGRAM_LENGTH){
		triggerEEPROM(prg_addr);
		Wire.requestFrom(IIC_ADDR_EEPROM, PROGRAM_LENGTH);

		for( pa = 0; pa < 252; pa += 9){
			if( Wire.available() )
				in_zone = Wire.read();

			if( Wire.available() )
				in_year = Wire.read();

			if( Wire.available() )
				in_month = Wire.read();

			if( Wire.available() )
				in_dom = Wire.read();

			if( Wire.available() )
				in_dow = Wire.read();

			if( Wire.available() )
				in_hour = Wire.read();

			if( Wire.available() )
				in_min = Wire.read();

			if( Wire.available() )
				in_sec = Wire.read();

			if( Wire.available() )
				in_state = Wire.read();

			if( year == 0 or in_year == year ){
				if( month == 0 or in_month == month ){
					if( dom == 0 or in_dom == dom ){
						if( dow == 0 or in_dow == dow ){
							if( hour == 0 or in_hour == hour ){
								if( in_min == min and in_sec == sec ){
									if( in_zone > 7 ){
										// zoneStatus[0]
										setZone( &zoneStatus[0], in_zone, in_state );
									} else {
										// zoneStatus[1]
										setZone( &zoneStatus[1], (in_zone - 8), in_state );
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void WateringSystem::setZone( uint8_t *zoneRef, uint8_t zoneNum, uint8_t state){
	int zone_mask = (int) pow(2, zoneNum);
	if( state ){
		zoneRef |= zone_mask;
	} else {
		zoneRef &= zone_mask;
	}
}

int WateringSystem::getZoneState(int zone, uint8_t *zoneState){
	int ret = 0;
	if( zone == 1 ){
		ret = 1;
		*zoneState = zoneStatus[0];
	}

	if( zone == 2 ){
		ret = 1;
		*zoneState = zoneStatus[1];
	}

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

void WateringSystem::triggerEEPROM( int eepromAddress ){
	Wire.beginTransmission(IIC_ADDR_EEPROM);
	Wire.write( (int) (eepromAddress >> 8) );
	Wire.write( (int) (eepromAddress >> 0xff) );
	Wire.endTransmission();
}
