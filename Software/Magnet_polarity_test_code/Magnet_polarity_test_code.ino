// Author: Nasmin Uddin
// The Unforgettable Cube - Magnet polarity testing code
/*--------------------------------------------------------------------------*/
//libraries for Hall-effect sensors and RGB LEDs
#include <Adafruit_MCP3008.h>
#include <Adafruit_NeoPixel.h>

/*--------------------------------------------------------------------------*/

#define PIN        7 //LED-IN pin (PCB) connected to the NeoPixels
#define NUMPIXELS  4 // How many NeoPixels are attached to the Arduino?
#define NHALL      4 // number of hall effect sensors
#define CS         5 //ADC CS pin
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
// hall effect sensors base value
#define HAL_0      556
#define HAL_1      522 
#define HAL_2      545
#define HAL_3      531

long const ADC_REF = 3.0;  // Set voltage used for VREF
//when setting up the NeoPixel library, we tell it how many pixels,
//and which pin to use to send signals.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//set Adafruit_MCP3008 object as adc
Adafruit_MCP3008 adc ;
/*--------------------------------------------------------------------------*/

void setup() {
    // put your setup code here, to run once:
    pixels.begin(); //initialise NeoPixel strip object
    Serial.begin(9600); //initialise serial monitor
    adc.begin(SCK, MOSI, MISO, CS); //custom pins
}

void loop() {
    // put your main code here, to run repeatedly:
    pixels.clear(); //set all pixel colors to 'off'
    pixels.show();  //send the updated pixel colors to the hardware
    //read all the Hall-effect sensors
    int adc_Reading0 = adc.readADC(0);
    int adc_Reading1 = adc.readADC(1);
    int adc_Reading2 = adc.readADC(2);
    int adc_Reading3 = adc.readADC(3);
    // print the values read from the sensor 0
    Serial.print(" Hall 0 --> ");
    Serial.print(adc_Reading0);
    Serial.print(" = ");
    Serial.print((adc_Reading0 * ADC_REF)/1024.0);
    Serial.print("V, ");
    // print the values read from the sensor 1
    Serial.print(" Hall 1 --> ");
    Serial.print(adc_Reading1);
    Serial.print(" = ");
    Serial.print((adc_Reading1 * ADC_REF)/1024.0);
    Serial.print("V, ");
    // print the values read from the sensor 2
    Serial.print(" Hall 2 --> ");
    Serial.print(adc_Reading2);
    Serial.print(" = ");
    Serial.print((adc_Reading2 * ADC_REF)/1024.0);
    Serial.print("V, ");
    // print the values read from the sensor 0
    Serial.print(" Hall 3 --> ");
    Serial.print(adc_Reading3);
    Serial.print(" = ");
    Serial.print((adc_Reading3 * ADC_REF)/1024.0);
    Serial.print("V, ");
    //new line
    Serial.println("");

    //upper bound of sensor 0
    if (adc_Reading0 > HAL_0+10){ 
        pixels.setPixelColor(0, pixels.Color(100, 0, 0)); //red
        pixels.show(); //send the updated pixel colors to the hardware
    }
    //lower bound of sensor 0
    if (adc_Reading0 < HAL_0-10){ //base value minus stride
        pixels.setPixelColor(0, pixels.Color(0, 100, 0)); //green
        pixels.show(); // Send the updated pixel colors to the hardware
    }

    //upper bound of sensor 1
    if (adc_Reading1 > HAL_1+10){ 
        pixels.setPixelColor(1, pixels.Color(100, 0, 0)); //red
        pixels.show(); // Send the updated pixel colors to the hardware
    }
    //lower bound of sensor 1
    if (adc_Reading1 < HAL_1-10){ 
        pixels.setPixelColor(1, pixels.Color(0, 100, 0)); //green
        pixels.show(); // Send the updated pixel colors to the hardware
    }

    //upper bound of sensor 2
    if (adc_Reading2 > HAL_2+7){ 
        pixels.setPixelColor(2, pixels.Color(100, 0, 0)); //red
        pixels.show(); // Send the updated pixel colors to the hardware
    }
    //lower bound of sensor 2
    if (adc_Reading2 < HAL_2-10){
        pixels.setPixelColor(2, pixels.Color(0, 100, 0)); //green
        pixels.show(); // Send the updated pixel colors to the hardware
    }

    //upper bound of sensor 3
    if (adc_Reading3 > HAL_3+10){ 
        pixels.setPixelColor(3, pixels.Color(100, 0, 0)); //red
        pixels.show(); // Send the updated pixel colors to the hardware
    }
    //lower bound of sensor 3
    if (adc_Reading3 < HAL_3-10){
        pixels.setPixelColor(3, pixels.Color(0, 100, 0)); //green
        pixels.show(); // Send the updated pixel colors to the hardware
    }

    delay(10); //pause before next pass through loop
}
