// Author: Nasmin Uddin
// The Unforgettable Cube - Hall-effect sensors testing code
/*---------------------------------------------------------------------*/ 

#include <Adafruit_MCP3008.h> //library for Hall-effect sensors
#define CS 5              //ADC CS pin
long const ADC_REF = 3.0; //set voltage used for VREF
int num_hall=4;           //number of hall effect sensors
Adafruit_MCP3008 adc ;    //set Adafruit_MCP3008 object as adc
/*---------------------------------------------------------------------*/

void setup() {
    //put your setup code here, to run once:
    Serial.begin(9600); // =initialise serial monitor
    //use custom pins
    adc.begin(SCK, MOSI, MISO, CS);
}
/*---------------------------------------------------------------------*/

void loop(){
    //read all Hall-effect sensors 
    for(size_t i=0; i<num_hall;i++){
        int adc_Reading = adc.readADC(i);
        //print to the serial monitor
        Serial.print(adc_Reading);
        Serial.print(" = ");
        //convert binary to decimal voltage
        Serial.print((adc_Reading * ADC_REF)/1024.0);
        Serial.print("V,   ");
    }
    Serial.println(""); //print a space
    delay(100); //wait for 100ms
}
