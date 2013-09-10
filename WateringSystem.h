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
#endif

#include <inttypes.h>

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

	// Destructor
	~WateringSystem();
};

