// Author: Nasmin Uddin
// The Unforgettable Cube - Complete code (GAME)
/*------------------------------------------------------------------------------*/
//LIBRARIES
#include <Adafruit_MCP3008.h>   // for ADC
#include <Adafruit_NeoPixel.h>  // for RGB LEDs
#include "TM1637.h"             // for 7-segment display

/*------------------------------------------------------------------------------*/
//MACROS
#define PIN        7 // LED-IN pin (PCB) connected to the NeoPixels
#define NUMPIXELS  4 // number of NeoPixels
#define NHALL      4 // number of hall effect sensors
#define CS         5 // ADC CS pin
//pins definitions for TM1637 dispay 1
#define CLK1       9
#define DIO1       10
//pins definitions for TM1637 dispay 2
#define CLK2       11
#define DIO2       12
// hall effect sensors base value
#define HAL_0      556
#define HAL_1      522 
#define HAL_2      545
#define HAL_3      531

//GLOBAL VARIABLES
float delayVal=1000;     // time (in ms) to pause between pixels
float speed_factor= 0.5; // speed factor to determine delayVal
// initialise score and high score
int high_score=0, score=0;
int sequence[50]; // initialise sequence of 50 elements 
int step_S= 0;    // counter to keep track of the elements in the sequence
int state=0, j=0;
int c=10000;      // delay counter to run each pattern sequence
int len_i=2;      // game level (level 1 = 2 tiles)
int stride=25;    // determines the range for base values of each hall effect sensor
int fake_flash=2; // max number of fake flashes per pattern
int toss=1; 

// set TM1637 objects as dis1 and dis2
TM1637 dis1(CLK1,DIO1);
TM1637 dis2(CLK2,DIO2);
// set Adafruit_NeoPixel object as pixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// set Adafruit_MCP3008 object as adc
Adafruit_MCP3008 adc ;
// pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
uint32_t magenta = pixels.Color(50, 0, 50);

/*-----------------------------------------------------------------------------*/
void setup() {
    // put your setup code here, to run once:
    pixels.begin(); // initialise NeoPixel strip object
    Serial.begin(9600);
    adc.begin(SCK, MOSI, MISO, CS); // custom pins to use a software SPI interface
    // initialise TM1637 objects
    dis1.init(); 
    dis1.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
    dis2.init();
    dis2.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

    /* initialize the pseudo-random number generator by reading voltage fluctutions 
    from an unconnected pin (pin 13) */
    randomSeed(analogRead(13));
}

void loop() {
    int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9}; // 0-9 config
    if (c>0) c--; // decrement counter
    switch(state){
        case 0:
            high_score= max(score, high_score); // compare score and high score
            if(len_i==2){
                // if game reset to level 1 show score and high score
                // print the units correctly on the displays
                dis1.display(3,NumTab[int((score))%10]);
                dis1.display(2,NumTab[int(floor(score/10))%10]);
                dis1.display(1,NumTab[int(floor(score/100))%10]);
                dis1.display(0,NumTab[int(floor(score/1000))%10]);
                dis2.display(3,NumTab[int((high_score))%10]);
                dis2.display(2,NumTab[int(floor(high_score/10))%10]);
                dis2.display(1,NumTab[int(floor(high_score/100))%10]);
                dis2.display(0,NumTab[int(floor(high_score/1000))%10]);
            }

            score=0;        // reset score 
            pixels.clear(); // turn all the pixels off
            pixels.show();  // Send the updated pixel colors to the hardware
            delayVal= 900/pow(2,speed_factor*(len_i-2))+100; // change speed based on level
            fake_flash=2;   // reset number of fake flashes
            // call function to generate and show the sequence
            if(len_i<51){
                populate();
            }
            else{
                len_i=50;
                populate();
            }
            pattern();
            j=0;
            state=1; // move to the next state
            step_S = sequence[j]; 
    
        case 1:
            // read and store the change in magnetic field from each hall effect sensor
            int a0=adc.readADC(0);
            int a1=adc.readADC(1);
            int a2=adc.readADC(2);
            int a3=adc.readADC(3); 

            if(a0>HAL_0+stride ||a0<HAL_0-stride){
                //if the value in the sequence = button press turn LED green
                if(step_S == 0){
                    len_i=len_i+(j==len_i-1); // increment level
                    pixels.setPixelColor(0,pixels.Color(0, 70, 0)); //LED 0 = green
                    pixels.show(); // Send the updated pixel colors to the hardware
                    // next value in the array
                    j=j+1;
                    step_S = sequence[j];
                    delay(500);
                    // turn LED off
                    pixels.clear();
                    pixels.show();
                }
                // otherwise restart at level 0
                else{
                    score=len_i-2;
                    len_i=2;
                    pixels.setPixelColor(0,pixels.Color(70, 0, 0)); // LED 0 = red 
                    pixels.show(); // Send the updated pixel colors to the hardware
                    delay(500);
                    state=0; // change states
                }
            }
      
            if(a1>HAL_1+stride ||a1<HAL_1-stride){
                //if the value in the sequence = button press turn LED green
                if(step_S == 1){
                    len_i=len_i+(j==len_i-1); // increment level
                    pixels.setPixelColor(1,pixels.Color(0, 70, 0)); //LED 1 = green
                    pixels.show(); // Send the updated pixel colors to the hardware
                    // next value in the array
                    j=j+1;
                    step_S = sequence[j];
                    delay(500);
                    // turn LED off
                    pixels.clear();
                    pixels.show();
                }
                // otherwise restart at level 0
                else{
                    score=len_i-2;
                    len_i=2;
                    pixels.setPixelColor(1,pixels.Color(70, 0, 0)); // LED 1 = red 
                    pixels.show(); // Send the updated pixel colors to the hardware
                    delay(500);
                    state=0; // change states
                }
            }

            if(a2>HAL_2+stride ||a2<HAL_2-stride){
                if(step_S == 2){
                    len_i=len_i+(j==len_i-1); // increment level
                    pixels.setPixelColor(2,pixels.Color(0, 70, 0)); //LED 2 = green
                    pixels.show(); // Send the updated pixel colors to the hardware
                    // next value in the array
                    j=j+1;
                    step_S = sequence[j];
                    delay(500);
                    // turn LED off
                    pixels.clear();
                    pixels.show();
                }
                // otherwise restart at level 0
                else{
                    score=len_i-2;
                    len_i=2;
                    pixels.setPixelColor(2,pixels.Color(70, 0, 0)); // LED 2 = red 
                    pixels.show(); // Send the updated pixel colors to the hardware
                    delay(500);
                    state=0; // change states
                }
            }
      
            if(a3>HAL_3+stride ||a3<HAL_3-stride){
                if(step_S == 3){ // the correct led
                    len_i=len_i+(j==len_i-1); // increment level
                    pixels.setPixelColor(3,pixels.Color(0, 70, 0)); //LED 3 = green
                    pixels.show(); // Send the updated pixel colors to the hardware
                    // next value in the array
                    j=j+1;
                    step_S = sequence[j];
                    delay(500);
                    // turn LED off
                    pixels.clear();
                    pixels.show();
                }
                // otherwise restart at level 0
                else{
                    score=len_i-2;
                    len_i=2;
                    pixels.setPixelColor(3,pixels.Color(70, 0, 0)); // LED 3 = red 
                    pixels.show(); // Send the updated pixel colors to the hardware
                    delay(500);
                    state=0; // change states
                }
            }
            // if all the tiles have been correctly pressed don't wait for the counter
            if(j==len_i){
                c=0;
            }
            // if times up then change the counter accordingly for the next sequence
            if (c==0){
                pixels.clear();
                pixels.show(); // Send the updated pixel colors to the hardware
                c=10000+3000*(len_i);
                state=0; // change states
            }
    } //END switch
} //END loop

/*--------------------------------------------------------------------------------------*/
// function for creating the pattern and storing it in sequence array
void populate(){
    for (int i=0; i<len_i; i++){
        sequence[i]= random(NUMPIXELS);
    }
    //print the sequence in the serial monitor for debugging
    for (int k=0;k<len_i; k++){
        Serial.println(sequence[k]);
    }
}

// function for displaying the sequence on the cube and generating fake flashes
void pattern(){
    for(int i=0; i<len_i; i++) {
        // show pattern in BLUE    
        pixels.setPixelColor(sequence[i],pixels.Color(0, 0, 70));
        pixels.show();      // Send the updated pixel colors to the hardware.
        // determines the speed of the flash
        delay(delayVal);    // Pause before next pass through loop
        pixels.setPixelColor(sequence[i],pixels.Color(0, 0, 0));
        pixels.show();      // Send the updated pixel colors to the hardware
        delay(delayVal);
        toss=random(3);     // probability of fake flash 1/3

        // if fake flash then turn on a random LED orange
        if(toss==0 && fake_flash>0){
            pixels.setPixelColor(random(4),pixels.Color(70, 30, 0));
            pixels.show(); // Send the updated pixel colors to the hardware
            // determines the speed of the flash
            delay(delayVal); // Pause before next pass through loop
            pixels.clear();
            pixels.show();
            fake_flash=fake_flash-1; // keep track of the number of fake flashes
        }
    } 
    // turon all LEDs magenta
    pixels.fill(magenta,0,NUMPIXELS);
    pixels.show(); // Send the updated pixel colors to the hardware
    delay(200);
    // turn all of the LEDs off
    pixels.clear();
    pixels.show(); // Send the updated pixel colors to the hardware
}
