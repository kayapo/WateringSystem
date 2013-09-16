// ---------------------------------------------------------------------------
// Created by Molnar Istvan on 09/09/2013
// Copyright: All rights reserved
//
// @file: WateringSystem.cpp
// This file implements all functionalities of the WateringSystem
//
// @author: Molnar Istvan  <kayapo@molnaristvan.eu>
// ---------------------------------------------------------------------------
#ifndef WateringSystem_h
#define WateringSystem_h

#include <inttypes.h>

// CONSTANT  definitions
// ---------------------------------------------------------------------------

/*!
 * @defined
 * @abstract   IIC_ADDR_LCD
 * @discussion Az LCD kijelzo cime az IIC csatornan
 */
#define IIC_ADDR_LCD 0x3f

/*!
 * @defined
 * @abstract   IIC_ADDR_RTC
 * @discussion Az RTC modul cime az IIC csatornan
 */
#define IIC_ADDR_RTC 0x68

/*!
 * @defined
 * @abstract   IIC_ADDR_EEPROM
 * @discussion Az EEPROM cime az IIC csatornan
 */
#define IIC_ADDR_EEPROM 0x50

/*!
 * @defined
 * @abstract   IIC_ADDR_RELAY
 * @discussion A rele vezerlo (MCP23017) cime az IIC csatornan
 */
#define IIC_ADDR_RELAY 0x20

/*!
 * @defined
 * @abstract   PUSH_BUTTON_PIN
 * @discussion Ehhez a labhoz csatlakozik a forgasjelado nyomogombja
 */
#define PUSH_BUTTON_PIN 2

/*!
 * @defined
 * @abstract   SCROLL_UP_PIN
 * @discussion Ehhez a labhoz csatlakozik a forgasjelado egyik laba
 */
#define SCROLL_UP_PIN 3

/*!
 * @defined
 * @abstract   SCROLL_DOWN_PIN
 * @discussion Ehhez a labhoz csatlakozik a forgas jelado masik laba
 */
#define SCROLL_DOWN_PIN 4

/*!
 * @defined
 * @abstract   MAIN_CYCLE_DELAY
 * @discussion A loop fuggvenyben ennyi idot kell varni a cilus vegen
 */
#define MAIN_CYCLE_DELAY 250

/*!
 * @defined
 * @abstract   EDIT_WAIT_CYCLE
 * @discussion A loop fuggvenyben ennyi ciklust kell varni miellot belepek a beallitasokba
 */
#define EDIT_WAIT_CYCLE 12

/*!
 * @defined
 * @abstract   EEPROM_LENGTH
 * @discussion Az EEPROM hossza byteban
 */
#define EEPROM_LENGTH 32768

/*!
 * @defined
 * @abstract   PROGRAM_LENGTH
 * @discussion Egy program hossza byteban
 */
#define PROGRAM_LENGTH 252

// A legfobb ciklus //////////////////////////////////////////////////////////
//
class WateringSystem
{
public:

	// Constructor without parameters
	WateringSystem();

	// Destructor
	~WateringSystem();

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */
	void resetZones();

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */
	int getZoneState(int zone, uint8_t *zoneState);

	/*!
	 * @defined
	 * @abstract
	 * @discussion Felolvassa az osszes programot az EEPROM -bol es beallitja a relek allapotbitjeit
	 * @discussion Egy program hossza: 9byte * 2fazis * 14lepes = 252byte
	 * @discussion { [ zone (0xF0 - 0xFF) ][ year (0x00 = *) ][ month (0x00 = *) ]
	 *             [ dom (0x00 = *) ][ dow (0x00 = *, 0x01 - 0x07) ][ hour (0x00 - 0x17) ][ min (0x00 - 0x3b) ][ sec (0x00 - 0x3b) ]
	 *             [ eventType (0x00 = ki, >0x00 = be)]}{...}{...}...
	 *
	 * @param
	 */
	void readProgram(int year, int month, int dom, int dom, int hour, int min, int sec);

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */
	void initManualSelector();

	/*!
	 * @method
	 * @abstract
	 * @discussion
	 *
	 * @param sec[in] secundums to set
	 * @param min[in] minutes to set
	 * @param hour[in] hours to set
	 * @param dow[in] day of week to set
	 * @param dom[in] day of month to set
	 * @param year[in] year to set
	 */
	void setDate( uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year );

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param *sec[in] pointer of secundums to get
	 * @param *min[in] pointer of minutes to get
	 * @param *hour[in] pointer of hours to get
	 * @param *dow[in] pointer of day of week to get
	 * @param *dom[in] pointer of day of month to get
	 * @param *year[in] pointer of year to get
	 */
	void getDate( uint8_t *sec, uint8_t *min, uint8_t *hour, uint8_t *dow, uint8_t *dom, uint8_t *month, uint8_t *year );

private:
	/*!
	 * @defined
	 * @abstract   SCROLL_UP_PIN
	 * @discussion Ehhez a labhoz csatlakozik a forgasjelado egyik laba
	 */
	uint8_t zoneStatus[2];

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */
	uint8_t bcdToDec( uint8_t bcd );

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */
	uint8_t decToBcd( uint8_t dec );

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */
	void triggerEEPROM( int eepromAddress );

	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */
	void setZone(uint8_t *zoneRef, uint8_t zoneNum, uint8_t state);
}; // class WateringSystem

#endif
