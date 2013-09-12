//-------------------------------------
// Programozhato ontozorendszer
//
//-------------------------------------

#include <Arduino.h>
#include "lib/Wire.h"
#include "lib/LiquidCrystal_I2C.h"
#include "WateringSystem.h"
#include "lang/hu_lang.h"

int edit_cycles = 0;

// Futasi objektumok
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(IIC_ADDR_LCD, 2, 1, 0, 4, 5, 6, 7);
WateringSystem wSys = WateringSystem();

void startSystem(){
	lcd.setBacklightPin(3,POSITIVE);
	delay(100);
	lcd.setBacklight(HIGH);
	delay(100);
	lcd.home();
	delay(100);

	lcd.print("Watering System");
	lcd.setCursor(0,1);
	lcd.print(MSG_START);
}

void displayClock(){
	// Letrehozok nehany valtozot
	// a datum es ido kijelzeshez
	byte sec, min, hour, dow, dom, mon, year;
	wSys.getDate( &sec, &min, &hour, &dow, &dom, &mon, &year );

	lcd.home();
	lcd.print("Watering System");

	// A masodiksor elejere teszem a kurzort
	lcd.setCursor(0,1);

	// Kiirom az orat
	if( hour < 10 )
		lcd.print("0");
	lcd.print(hour,DEC);

	// Kettospont
	lcd.print(CLOCK_SEPARATOR);

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
	lcd.print(DATE_SEPARATOR);

	if( dom < 10 )
		lcd.print("0");
	lcd.print(dom,DEC);
}

void settingsMenu(){
	boolean do_menu = true;
	int scroll = LOW;
	int scroll_last = LOW;
	int msg_state = 1;

	// Letorlom a kijelzot
	lcd.clear();
	lcd.home();

	// Belepes a beallitas menube
	lcd.print(MSG_SETTINGS_MENU);

	// Megvarjuk a nyomogomb elengedeset
	while( ! digitalRead(PUSH_BUTTON_PIN)){ }

	// Kiirom a valasztas alap beallitasat
	lcd.setCursor(0,1);
	lcd.print(MSG_NO);

	scroll = digitalRead(SCROLL_UP_PIN);
	if( (scroll_last == LOW) && (scroll == HIGH) ){
		if( digitalRead(SCROLL_DOWN_PIN) == LOW ){

		}
	}

	while(do_menu){
		scroll = digitalRead(SCROLL_UP_PIN);
		if( (scroll_last == LOW) && (scroll == HIGH) ){
			if( digitalRead(SCROLL_DOWN_PIN) == LOW ){
				msg_state--;
			} else {
				msg_state++;
			}
		}

		if( msg_state%2 == 0 ){
			lcd.setCursor(0,1);
			lcd.print(MSG_NO);
			lcd.print("   ");
		} else {
			lcd.setCursor(0,1);
			lcd.print(MSG_YES);
			lcd.print("   ");
		}

		if( ! digitalRead(PUSH_BUTTON_PIN) )
			do_menu = false;

		if( msg_state < -500 or msg_state > 500 )
			msg_state = 0;

		delay(25);

		scroll_last = scroll;
	}
}

void setup(){
	// Objektum letrehozatal
	lcd.begin(16,2);

	wSys.initManualSelector();
	// wSys.setDate(0, 45, 11, 4, 12, 9, 43);
	startSystem();
	delay(1000);
}

void loop(){
	//uint8_t zone, event;

	displayClock();

	if( digitalRead( PUSH_BUTTON_PIN ) ){
		edit_cycles = 0;
	} else {
		edit_cycles++;
	}

	if( edit_cycles == EDIT_WAIT_CYCLE ){
		settingsMenu();
	}
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
