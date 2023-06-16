// Author: Nasmin Uddin
// The Unforgettable Cube - 7-segment display testing code
/*---------------------------------------------------------------------*/
#include "TM1637.h" //library for the 4 digit 7-segment display
/*---------------------------------------------------------------------*/
#define CLK1 9      //pins definitions for TM1637 dis1
#define DIO1 10
#define CLK2 11     //pins definitions for TM1637 dis2
#define DIO2 12
//intialise two object of type TM1637
TM1637 dis1(CLK1,DIO1);
TM1637 dis2(CLK2,DIO2);
float level = 0; //counter variable
/*---------------------------------------------------------------------*/
void setup() {
    // put your setup code here, to run once:
    dis1.init(); //initialise display 1
    //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
    dis1.set(BRIGHT_TYPICAL);
    dis2.init(); //initialise display 2
    dis2.set(BRIGHT_TYPICAL);
}
/*---------------------------------------------------------------------*/
void loop() {
    // put your main code here, to run repeatedly:
    int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9}; // 0-9 config
    //digit one score (right to left)
    dis1.display(3,NumTab[int((level))%10]);
    // digit two score (right to left)
    dis1.display(2,NumTab[int(floor(level/10))%10]);
    // digit three score (right to left)
    dis1.display(1,NumTab[int(floor(level/100))%10]);
    //digit four score (right to left)
    dis1.display(0,NumTab[int(floor(level/1000))%10]);
    
    //digit one high score (right to left)
    dis2.display(0,NumTab[int((level))%10]);
    //digit two high score (right to left)
    dis2.display(1,NumTab[int(floor(level/10))%10]);
    //digit three high score (right to left)
    dis2.display(2,NumTab[int(floor(level/100))%10]);
    //digit four high score (right to left)
    dis2.display(3,NumTab[int(floor(level/1000))%10]);
    delay(500); // wait for a while
    level=level+1; //increment counter
}
