/** 
    author : Jukoo <funscript@outlook.fr> 
    link   : https://github.com/Jukoo
    firmware for dice game v_1.0 

     SCHEMAS     
     -------- 
      2     4 
         3 
      5     6 
 
*/

#include <stdint.h>
#include "dice.hpp" 


// leds collections 
uint8_t dicep[DICE_SIZE] = { 
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6
 } ; 

uint8_t rnd_num ; 
void setup () { 
    Serial.begin(9600) ; 
    dice_init(dicep) ; 
    pinMode(I_BTN, INPUT_PULLUP);  
    randomSeed(analogRead(0))  ;  // initialize random sequence  
    rnd_num = 0x000 ;  
    LOG("AVR device ready ! <push the button to start ... >") ; 
}   
void loop () { 
    
    bool ipb_stat = digitalRead(I_BTN) ; 
    if(!ipb_stat) {
        loader() ; 
        leds_init(dicep , false ) ;
        //animation_patern_v2(dicep , DICE_SIZE) ; 
        rnd_num =random(RND_RATE) ;  
        dice_throw(rnd_num , dicep) ;
        showResult(rnd_num); 
    }
    
}
