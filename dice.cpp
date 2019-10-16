#include "Arduino.h" 
#include "dice.hpp" 
#include <stdint.h> 

//! initialize the output pins 
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

//! turn off the leds 
static void turn_off_between() {    
    uint8_t all_leds[DICE_SIZE]  = {2,3,4,5,6} ; 
    for (  uint8_t i {0} ; i< DICE_SIZE  ; i++) 
        digitalWrite(all_leds[i] , 0x0001) ;   
} 

//! turn on the leds 
static void dice_illuminate( uint8_t current_dice_partern [] ,uint8_t size)  {  
    for (uint8_t  i {0}  ; i < size ; i++) {
        digitalWrite(current_dice_partern[i], 0x000) ; 
    }
}


//! dice patern namespace 
//! collection of my patern 
namespace DP{   //! => DP as Dice Patern 

   void one (uint8_t& _one  , uint32_t timeDelay)  {
        digitalWrite(_one , 0x000) ;
        DTimer(timeDelay);
    } ; 
   void two(uint8_t two [] , uint32_t  timeDelay) {
       dice_illuminate(two , PIN_2) ; 
       DTimer(timeDelay);
    } ;  
    void three(uint8_t three []  ,uint32_t timeDelay) {
       dice_illuminate(three , PIN_3) ; 
       DTimer(timeDelay);
   } ;     
    void four(uint8_t four[] , uint32_t  timeDelay) {
       dice_illuminate(four, PIN_4) ; 
       DTimer(timeDelay);
   } ; 

    void five (uint8_t all_5_leds [] ,uint32_t timeDelay) {
       dice_illuminate(all_5_leds , DICE_SIZE) ; 
       DTimer(timeDelay);
    } ; 
    void zero (uint8_t all_5_leds [] ) {
       //dice_illuminate(all_5_leds , DICE_SIZE) ; 
        turn_off_between() ; 
        DTimer(ANIM_SPEED) ;  
    }
}  

/*! 
 * dice_throw : 
 *  show the correct patern sorted in random  
 */
void dice_throw ( uint8_t& rand_num  , uint8_t dicep []) {  
    switch (rand_num ) {
        case 0x001 : 
            DP::one(one) ;
            break ; 
        case PIN_2 : 
            DP::two(two) ; 
            break ; 
        case PIN_3 : 
            DP::three(three) ;
            break ; 
        case  PIN_4 : 
            DP::four(four);
            break; 
        case DICE_SIZE: 
            DP::five(dicep) ;
            break ; 
        default : DP::zero(dicep) ;      
    } 
} 

//! used for animation  
void leds_animation ( uint8_t dpins [] ,ANIMATION_TYPE &a_type , int &v_duration,  bool use_random_animation) {  
    int MAX_DURATION = v_duration ; 
    uint8_t watch_rnd {0}  ; 
    for(uint32_t i{0} ; i <MAX_DURATION ; i+=75) {
        uint8_t rnd_patern  = random(RND_RATE) ;  
        if (use_random_animation) { 
            while (watch_rnd == rnd_patern || rnd_patern == 0) {
                rnd_patern = random(RND_RATE) ;  
            } 
        } 
        for (uint8_t pin {0}  ; pin < DICE_SIZE  ; pin++) {
            if(a_type == 0) 
                animation_patern(rnd_patern , dpins);
            else 
                animation_patern_v2(rnd_patern, dpins) ; 
        }
          DTimer(i) ;  
          //! the watch_rnd is active when  the use_random_animation is set to true 
          //! otherwise  it sets to zero 
          watch_rnd = use_random_animation ? rnd_patern : 0 ; 
    }
} 
//! play the leds  animation #animation version 1  
static void animation_patern(uint8_t& rnd_num , uint8_t dpins []) {
        switch (rnd_num) {
        case 0x001 : 
            DP::one(one , ANIM_SPEED) ;
            turn_off_between() ;
            break ; 
        case PIN_2 : 
            DP::two(two , ANIM_SPEED) ; 
            turn_off_between() ;
            break ; 
        case PIN_3 : 
            DP::three(three , ANIM_SPEED) ;
            turn_off_between() ;
            break ; 
        case  PIN_4 : 
            DP::four(four , ANIM_SPEED); 
            turn_off_between() ;
            break; 
        case DICE_SIZE: 
            DP::five(dpins , ANIM_SPEED) ;
            turn_off_between() ;
            break ; 
        default :  DP::zero(dpins) ;      
    } 
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
//! animation version 2  [much more cool]
void animation_patern_v2( uint8_t& rand_num , uint8_t io_pins [])  {      
                digitalWrite(io_pins[rand_num] , 0x000) ; 
                DTimer(100) ; 
                digitalWrite(io_pins[rand_num]  , 0x001) ; 
                DTimer(100) ;  
} 



//! show variation on serial Ploter or Serial monitor
void potar_variation_view(int& value) {
    char buffer[0x0017] ; //! 20  
    sprintf (buffer , "readed value -> %d" , value ); 
    LOG(buffer);  
    DTimer(0x64); 
}


int animation_potar_control(int&pot_val, int rate_animation ) {
   return map(
           pot_val ,  
           LOW_POT_RATE , 
           HIGH_POT_RATE , 
           500,
           rate_animation 
           )  ; 
    
}
