#include "Arduino.h" 
#include "dice.hpp" 
#include <stdint.h> 


void dice_init(uint8_t dpins [])  {
    for(uint8_t i{0} ; i < DICE_SIZE;  i++) {
        pinMode(dpins[i] , OUTPUT);     
    } 
    DTimer(1000) ; 
    for ( uint8_t i{0}  ;  i < RND_RATE ;  i++ ) {
        digitalWrite(dpins[i] , 0x000) ;  // !  LOW  
    }
}

//! used for quick test 
void dice_blink (uint8_t dpins []) {
   for(uint8_t i{0} ; i < RND_RATE-1 ;  i++) {
        digitalWrite(dpins[i] , 0x00); 
        DTimer(ANIM_SPEED) ; 
        digitalWrite(dpins[i] , 0x01); 
    }
}

// --- deci Patern visualisation 



static void turn_off_between() {    
    uint8_t all_leds[FIVE]  = {2,3,4,5,6} ; 
    for (  uint8_t i {0} ; i< FIVE  ; i++) 
        digitalWrite(all_leds[i] , 0x0001) ;   
} 

static void dice_illuminate( uint8_t current_dice_partern [] ,uint8_t size)  {  
    for (uint8_t  i {0}  ; i < size ; i++) {
        digitalWrite(current_dice_partern[i], 0x000) ; 
    }
}

namespace dice_patern {

   void one (uint8_t& _one  , uint32_t timeDelay)  {
        digitalWrite(_one , 0x000) ;
        DTimer(timeDelay);
    } ; 
   void two(uint8_t two [] , uint32_t  timeDelay) {
       dice_illuminate(two , TWO) ; 
       DTimer(timeDelay);
    } ;  
    void three(uint8_t three []  ,uint32_t timeDelay) {
       dice_illuminate(three , THREE) ; 
       DTimer(timeDelay);
   } ;     
    void four(uint8_t four[] , uint32_t  timeDelay) {
       dice_illuminate(four, FOUR) ; 
       DTimer(timeDelay);
   } ; 

    void five (uint8_t all_5_leds [] ,uint32_t timeDelay) {
       dice_illuminate(all_5_leds , FIVE) ; 
       DTimer(timeDelay);
    } ; 
    void zero (uint8_t all_5_leds [] ) {
       dice_illuminate(all_5_leds , FIVE) ;  
        DTimer(ANIM_SPEED) ;  
    }
}  

/*! 
 * dice_throw : 
 * 
 */
void dice_throw ( uint8_t& rand_num  , uint8_t dicep []) {  
    switch (rand_num ) {
        case 0x001 : 
            dice_patern::one(_one) ;
            break ; 
        case TWO : 
            dice_patern::two(two) ; 
            break ; 
        case THREE : 
            dice_patern::three(three) ;
            break ; 
        case  FOUR : 
            dice_patern::four(four);
            break; 
        case FIVE: 
            dice_patern::five(dicep) ;
            break ; 
        default :  dice_patern::zero(dicep) ;      
    } 
} 


void leds_init ( uint8_t dpins [] ) {  
    for(uint32_t i{0} ; i < 2000 ; i+=200) {
        uint8_t rnd_patern  = random(6) ; 
        //LOG(rnd_patern);
        for (uint8_t pin {0}  ; pin < FIVE  ; pin++) {
          animation_patern(rnd_patern , dpins);  
        }
          DTimer(i) ; 
    }
} 
// need a quick animation 
static void animation_patern(uint8_t& rnd_num , uint8_t dpins []) {
        switch (rnd_num) {
        case 0x001 : 
            dice_patern::one(_one  , ANIM_SPEED) ;
            turn_off_between() ;
            break ; 
        case TWO : 
            dice_patern::two(two ,ANIM_SPEED) ; 
            turn_off_between() ;
            break ; 
        case THREE : 
            dice_patern::three(three , ANIM_SPEED) ;
            turn_off_between() ;
            break ; 
        case  FOUR : 
            dice_patern::four(four , ANIM_SPEED); 
            turn_off_between() ;
            break; 
        case FIVE: 
            dice_patern::five(dpins , ANIM_SPEED) ;
            turn_off_between() ;
            break ; 
        default :  dice_patern::zero(dpins) ;      
    } 
}


void vdbg(bool& stat ) {
    LOG_("INPUT PULL UP status 0x00") ; 
    LOG(stat ?1:0) ; 
} 


//! little load bar animation on console  
void loader () { 
    LOG_("launching |") ; 
    int counter {0} ; 
    int alea  = random(11) ;  
    while (counter <= alea ) {
       // LOG_("░") ; 
        LOG_("#"); 
        DTimer(100) ; 
        counter++ ; 
    } 
    LOG("|") ;
} 

//! show the  correct number 
void showResult (uint8_t& rand_num) {
        char buffer[0x0f] ;     
        sprintf(buffer , "the result is :  %d" ,rand_num) ; 
        LOG(buffer) ; 
}
/* 
void io_pins_config (_IO_digital * io_instance) {
    io_instance->_one = 0x003 ; 
    io_instance->two  = {4,5} ; 
    

}
*/ 
