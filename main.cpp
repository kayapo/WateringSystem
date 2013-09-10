//-------------------------------------
// Programozhato ontozorendszer
//
//-------------------------------------

#include <Arduino.h>
#include "lib/Wire.h"
#include "lib/LiquidCrystal_I2C.h"
#include "WateringSystem.h"

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
 * @abstract   MAIN_CYCLE_DELAY
 * @discussion Delay time, wait before next cycle in main loop
 */
#define MAIN_CYCLE_DELAY 250

/*!
 * @defined
 * @abstract   EDIT_WAIT_CYCLE
 * @discussion At least as many cycles need to keep pressing the edit button to enter the setup
 */
#define EDIT_WAIT_CYCLE 12

int edit_cycles = 0;

LiquidCrystal_I2C lcd(IIC_ADDR_LCD, 2, 1, 0, 4, 5, 6, 7);

WateringSystem wSys();


void setup(){
	// Objektum letrehozatal
	lcd.begin(16,2);
	Wire.begin();

	// setDate(0, 30, 20, 6, 8, 9, 43);

	lcd.setBacklightPin(3,POSITIVE);
	delay(100);
	lcd.setBacklight(HIGH);
	delay(100);
	lcd.home();
	delay(100);

	lcd.print("Watering System");
	lcd.setCursor(0,1);
	lcd.print("Start");
	delay(1000);
}

void loop(){
	// Letrehozok nehany valtozot
	// a datum es ido kijelzeshez
	byte sec, min, hour, dow, dom, mon, year;
	wSys.getDate( &sec, &min, &hour, &dow, &dom, &mon, &year);

	// A masodiksor elejere teszem a kurzort
	lcd.setCursor(0,1);

	// Kiirom az orat
	if( hour < 10 )
		lcd.print("0");
	lcd.print(hour,DEC);

	// Kettospont
	lcd.print(":");

	// Kiirom a percet
	if( min < 10 )
		lcd.print("0");
	lcd.print(min,DEC);

	// Kettospont
	lcd.print(":");

	// Kiirom a masodpercet
	if( sec < 10 )
		lcd.print("0");
	lcd.print(sec,DEC);

	// Nemi ur
	lcd.print("  ");

	if( mon < 10 )
		lcd.print("0");
	lcd.print(mon,DEC);

	// Perjel
	lcd.print("/");

	if( dom < 10 )
		lcd.print("0");
	lcd.print(dom,DEC);

	// Takarekoskodunk az eroforrasokkal
	// masodpercenkent 4szer engedem futni a
	// a rendszert
	delay(MAIN_CYCLE_DELAY);
}

int main(){
	init();
	setup();

	while(true){
		loop();
	}
}
