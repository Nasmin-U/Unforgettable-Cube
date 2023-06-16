// Author: Adafruit
// Edited by: Nasmin Uddin
// The Unforgettable Cube - RGB LEDs testing code
/*---------------------------------------------------------------------*/ 

//library for RGB LEDs
#include <Adafruit_NeoPixel.h>
#define PIN        7 //LED-IN pin (PCB) connected to the NeoPixels
#define NUMPIXELS  4 //number of NeoPixels
//set Adafruit_NeoPixel object as pixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500
/*---------------------------------------------------------------------*/ 

void setup() {

    pixels.begin(); //initialise NeoPixel strip object
}
/*---------------------------------------------------------------------*/ 

void loop() {
    pixels.clear(); //turn all the pixels off

    // turn all LEDs orange one at a time
    for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(30, 10, 0));
        //send the updated pixel colours to the hardware
        pixels.show();
        //time (in milliseconds) to pause between pixels
        delay(DELAYVAL); 
    }

    //turn all LEDs turquoise one at a time
    for(int k=0; k<NUMPIXELS; k++) {
        pixels.setPixelColor(k, pixels.Color(0, 30, 10));
        //send the updated pixel colours to the hardware
        pixels.show();
        delay(DELAYVAL);
    }

    //turn all LEDs purple one at a time
    for(int j=0; j<NUMPIXELS; j++) {
        pixels.setPixelColor(j, pixels.Color(10, 0, 30));
        //send the updated pixel colours to the hardware
        pixels.show();
        //time (in milliseconds) to pause between pixels
        delay(DELAYVAL);
    }
}
