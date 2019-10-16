#ifndef __DICE__
#define __DICE__ 

#include <stdint.h> 

#define BAUD_CHANNEL   19200
#define RND_RATE 0X006   
#define DICE_SIZE (RND_RATE - 0X001)             

//!  io digital pins 
#define PIN_2    0X02                           //! PIN 2  
#define PIN_3    0X03                           //! PIN 3 
#define PIN_4    0X04                           //! PIN 4 
#define PIN_5    0X05                           //! PIN 5 
#define PIN_6    0x06                           //! PIN 6
//! io analog  
#define  ANALOG_POT A2                          
#define  LOW_POT_RATE 0X00
#define  HIGH_POT_RATE 0x3FF 

//! BTN PUSH 
#define PIN_10_BTN    0X0A                      //! PIN 10 Button INPUT_PULLUP 
// RANDOM 
#define RAND_INIT()   randomSeed(analogRead(0)) //! INITIALISE THE RANDOM SEQUENCE   
#define RAND(arg_num)  random(arg_num)          //! GENERATE RANDOM NUMBER  [not used] 

#define NO_RAND_REPEAT true                     //! AVOID TO REPEATE  THE SAME NUMBER
                                                //! SUCCESSIVELY... 
//! TIMER  
#define MAX_T_SLP  0x64                        //! MAX TIME DELAY OR SLEEP  100 
#define ANIM_SPEED 0x0a                        //! ANIMATION  SPEED         10

//! REDIFINE  DELAY METHOD
#define DTimer(timeDelay) delay(timeDelay)      //! TIME DELAY OR SLEEP  
/* 
#define S_ENABLE Serial.available() 
#define DR digitalRead(I_BTN) 
#define RXDR Serial.read() 
*/

//! REDIFINE SERIAL METHOD 
#define LOG(arg) Serial.println(arg)
#define LOG_(arg)Serial.print(arg) 

//! DICE PATERN   
uint8_t one {PIN_3}; 
uint8_t two[2]   = {PIN_4,PIN_5} ; 
uint8_t three[3] = {PIN_3 ,PIN_4,PIN_5} ; 
uint8_t four[4]  = {PIN_2,PIN_4,PIN_5,PIN_6} ;
//!  the five is  equale to DICE_SIZE !\\

//! CORE 
void dice_init(uint8_t [] ) ; 

void dice_blink(uint8_t []) ; 

static void turn_off_between() ;  
static void dice_illuminate(uint8_t []  , uint8_t ) ; 

typedef enum {
    DICE_PATERN_ANIMATION , //0 
    RANDOM_LED_ANIMATION //1 
} ANIMATION_TYPE ; 

namespace DP  {
    void one   (uint8_t& , uint32_t  = MAX_T_SLP) ;   
    void two   (uint8_t [],uint32_t  = MAX_T_SLP) ; 
    void three (uint8_t [],uint32_t  = MAX_T_SLP) ; 
    void four  (uint8_t [],uint32_t  = MAX_T_SLP) ; 
    void five  (uint8_t [],uint32_t  = MAX_T_SLP) ; 
    void zero  (uint8_t []) ;  
}  

void dice_throw( uint8_t& ,uint8_t []) ; 

void leds_animation(uint8_t [], ANIMATION_TYPE& , int& , bool =NO_RAND_REPEAT);  

static void amination_patern(uint8_t&  , uint8_t[] ) ; 

void loader() ; 

void showResult(uint8_t &) ;  

void animation_patern_v2(uint8_t& ,uint8_t[]) ;

int animation_potar_control(int & , int); 
void potar_variation_view(int&) ;  
#endif 
