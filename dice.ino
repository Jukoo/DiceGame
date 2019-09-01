/** 
    FUNCTIONS  AND RANDOM NUMBER 
    TODO 
    []  add button to lauch dice operation  
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


// leds collection 
uint8_t dicep[DICE_SIZE] = {
    0x0002,   
    0x0003,
    0x0004,
    0x0005, 
    0x0006
} ; 

uint8_t rnd_num ; 
uint8_t const ipb{B_IPUP} ;  // ipb -> input button 


void setup () { 
    Serial.begin(9600) ; 
    dice_init(dicep) ; 
    pinMode(ipb , INPUT_PULLUP);  
    RAND_INIT() ;  //randomSeed(analogRead(0))  ;  // initialize random sequence  
    rnd_num = 0x000 ;  
    LOG("AVR device ready ! <push the button to start ... >") ; 
}   
void loop () { 
    
    bool ipb_stat = digitalRead(ipb) ; 
    if(!ipb_stat) {
        loader() ; 
        leds_init(dicep) ; 
        DTimer(2000);
        rnd_num = random(RND_RATE) ;  
        dice_throw(rnd_num , dicep) ;
        showResult(rnd_num); 
        DTimer(1000) ;   
    }
    
}
