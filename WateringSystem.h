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

// A legfobb ciklus //////////////////////////////////////////////////////////
//
class WateringSystem
{
public:
	/*!
	 * @defined
	 * @abstract
	 * @discussion
	 *
	 * @param
	 */

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
	int getEvent(uint8_t *zone, uint8_t *event);

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
	int readFromEEPROM(int eeprom_addr, uint16_t *start_addr, uint16_t *prog_len);
}; // class WateringSystem

#endif
