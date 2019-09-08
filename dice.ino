/** 
    author : Jukoo <funscript@outlook.fr> 
    link   : https://github.com/Jukoo/DiceGame
    firmware for dice game v_1.0 

     SCHEMAS     
     -------- 
      2     4 
         3 
      5     6 
 
*/

#include <stdint.h>
#include "dice.hpp" 

//! Animation type 
ANIMATION_TYPE anim_type = DICE_PATERN_ANIMATION ; 
//ANIMATION_TYPE anim_type = RANDOM_LED_ANIMATION ; 

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
    pinMode(PIN_10_BTN, INPUT_PULLUP);  
    randomSeed(analogRead(0))  ;  // initialize random sequence  
    rnd_num = 0; 
    LOG("AVR device ready ! <push the button to start ... >") ; 
}   
void loop () { 
    
    bool pull_up_btn = digitalRead(PIN_10_BTN) ; 
    if(!pull_up_btn) {
        loader() ;  //  the loader  
        leds_animation(dicep, anim_type) ;
        rnd_num =random(RND_RATE) ;  
        dice_throw(rnd_num , dicep) ;
        showResult(rnd_num); 
    }
    
}
