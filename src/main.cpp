#include <Arduino.h>
#include "adf4351.h"


#define PIN_SS PA4  ///< SPI slave select pin, default value

ADF4351  vfo(PIN_SS, SPI_MODE0, 1000000UL , MSBFIRST) ;


void setup() {
    pinMode(PC13,OUTPUT);
    Serial.begin(9600) ;
    Serial.print("Hello adf4351 demo!!!") ;

    vfo.pwrlevel = 0 ; ///< sets to -4 dBm output
    vfo.RD2refdouble = 0 ; ///< ref doubler off
    vfo.RD1Rdiv2 = 0 ;   ///< ref divider off
    vfo.ClkDiv = 150 ;
    vfo.BandSelClock = 80 ;
    vfo.RCounter = 1 ;  ///< R counter to 1 (no division)
    vfo.ChanStep = steps[2] ;  ///< set to 10 kHz steps

    /*!
        sets the reference frequency to 25 Mhz
    */
    if ( vfo.setrf(25000000UL) ==  0 )
        Serial.println("ref freq set to 25 Mhz") ;
    else
      Serial.println("ref freq set error") ;
      /*!
         initialize the chip
      */
      vfo.init() ;

    /*!
        enable frequency output
    */
    vfo.enable() ;

    Serial.println("setf() to 97 MHz") ;

    if ( vfo.setf(97000000UL) == 0 ) {
        Serial.print("setf() success freq:") ;
        Serial.println(vfo.cfreq) ;
    } else {
        Serial.println("setf() error") ;
    }
}

void loop() {
    delay(1500);
    digitalWrite(PC13,0);
    delay(200);
    digitalWrite(PC13,1);
}